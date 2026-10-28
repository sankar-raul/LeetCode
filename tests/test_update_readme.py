import json
import tempfile
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch
from urllib.error import HTTPError, URLError

from scripts import update_readme


class FakeResponse:
    def __init__(self, payload):
        self.payload = payload

    def __enter__(self):
        return self

    def __exit__(self, *_):
        return False

    def read(self):
        return json.dumps(self.payload).encode("utf-8")


def bulk_payload(*entries):
    return {"stat_status_pairs": [{"stat": {"question_id": i, "question__title_slug": slug},
                                   **({"difficulty": difficulty} if difficulty is not None else {})}
                                  for i, slug, difficulty in entries]}


class UpdateReadmeTests(unittest.TestCase):
    def setUp(self):
        update_readme._QUESTION_CACHE.clear()

    def test_solution_ids_discovers_numeric_solution_directories(self):
        root = SimpleNamespace(iterdir=lambda: [
            SimpleNamespace(name="1 Two Sum", is_dir=lambda: True),
            SimpleNamespace(name="2 Add Two Numbers", is_dir=lambda: True),
            SimpleNamespace(name="README.md", is_dir=lambda: False),
            SimpleNamespace(name="12abc", is_dir=lambda: True),
        ])
        with patch.object(update_readme, "ROOT", root):
            self.assertEqual(update_readme.solution_ids(), [1, 2])

    def test_bulk_metadata_accepts_complete_difficulty_values(self):
        response = FakeResponse(
            bulk_payload((1, "two-sum", {"level": 1}), (2, "add-two-numbers", {"level": 2}),
                          (3, "longest-substring-without-repeating-characters", {"level": 3}))
        )
        with patch("scripts.update_readme.urllib.request.urlopen", return_value=response):
            self.assertEqual(
                {key: value.difficulty for key, value in update_readme.bulk_metadata().items()},
                {1: "Easy", 2: "Medium", 3: "Hard"},
            )

    def test_problem_slugs_accepts_incomplete_bulk_difficulty(self):
        response = FakeResponse(bulk_payload((1, "two-sum", None)))
        with patch("scripts.update_readme.urllib.request.urlopen", return_value=response):
            self.assertEqual(update_readme.problem_slugs(), {1: "two-sum"})

    def test_question_metadata_validates_id_slug_and_difficulty(self):
        response = FakeResponse({"data": {"question": {
            "questionFrontendId": "101", "titleSlug": "easy-problem", "difficulty": "Easy"
        }}})
        with patch("scripts.update_readme.urllib.request.urlopen", return_value=response):
            self.assertEqual(update_readme.question_metadata(101, "easy-problem"), "Easy")

        mismatch = FakeResponse({"data": {"question": {
            "questionFrontendId": "2", "titleSlug": "add-two-numbers", "difficulty": "Medium"
        }}})
        with patch("scripts.update_readme.urllib.request.urlopen", return_value=mismatch):
            self.assertIsNone(update_readme.question_metadata(1, "two-sum"))

    def test_graphql_errors_with_http_200_are_not_metadata(self):
        response = FakeResponse({"errors": [{"message": "blocked"}], "data": {"question": None}})
        with patch("scripts.update_readme.urllib.request.urlopen", return_value=response):
            self.assertIsNone(update_readme.question_metadata(1, "two-sum"))
        self.assertEqual(update_readme._DIAGNOSTICS.graphql_errors, 1)

    def test_missing_and_malformed_questions_are_rejected(self):
        for payload in (
            {"data": {"question": None}},
            {"data": {"question": {"difficulty": "Easy"}}},
            {"data": {"question": "not an object"}},
        ):
            with patch("scripts.update_readme.urllib.request.urlopen",
                       return_value=FakeResponse(payload)):
                self.assertIsNone(update_readme.question_metadata(1, "missing"))

    def test_request_retries_rate_limits_and_transient_server_failures(self):
        rate_limit = HTTPError("https://leetcode.com/graphql", 429, "rate limited", {}, None)
        server_error = HTTPError("https://leetcode.com/graphql", 503, "unavailable", {}, None)
        response = FakeResponse({"data": {}})
        with patch("scripts.update_readme.urllib.request.urlopen",
                   side_effect=[rate_limit, server_error, response]), patch("scripts.update_readme.sleep"):
            self.assertEqual(update_readme.request_json(update_readme.GRAPHQL_URL, {}), {"data": {}})

    def test_request_retries_timeouts_and_exhaustion_is_reported(self):
        response = FakeResponse({"data": {}})
        with patch("scripts.update_readme.urllib.request.urlopen",
                   side_effect=[TimeoutError(), response]), patch("scripts.update_readme.sleep") as sleep:
            self.assertEqual(update_readme.request_json(update_readme.GRAPHQL_URL, {}), {"data": {}})
            self.assertEqual(sleep.call_count, 1)

        with patch("scripts.update_readme.urllib.request.urlopen",
                   side_effect=TimeoutError()), patch("scripts.update_readme.sleep"):
            with self.assertRaises(TimeoutError):
                update_readme.request_json(update_readme.GRAPHQL_URL, {})

    def test_load_metadata_uses_bulk_and_graphql_fallback_and_preserves_unknown(self):
        records = {
            1: ("two-sum", {"level": 1}),
            2: ("add-two-numbers", None),
        }
        with tempfile.TemporaryDirectory() as directory, \
             patch.object(update_readme, "CACHE_PATH", Path(directory) / "cache.json"), \
             patch.object(update_readme, "solution_ids", return_value=[1, 2, 3]), \
             patch.object(update_readme, "bulk_records", return_value=records), \
             patch.object(update_readme, "question_metadata", return_value="Medium"):
            # The bulk parser normally converts this level before load_metadata sees it.
            records[1] = ("two-sum", "Easy")
            self.assertEqual(update_readme.load_metadata(), {1: "Easy", 2: "Medium"})

    def test_load_metadata_cache_hit_avoids_external_requests(self):
        with tempfile.TemporaryDirectory() as directory:
            cache = Path(directory) / "cache.json"
            cache.write_text(json.dumps([{
                "question_id": 1, "slug": "two-sum", "difficulty": "Easy"
            }]))
            with patch.object(update_readme, "CACHE_PATH", cache), \
                 patch.object(update_readme, "solution_ids", return_value=[1]), \
                 patch.object(update_readme, "bulk_records") as bulk:
                self.assertEqual(update_readme.load_metadata(), {1: "Easy"})
                bulk.assert_not_called()

    def test_invalid_cache_entries_are_ignored(self):
        with tempfile.TemporaryDirectory() as directory:
            cache = Path(directory) / "cache.json"
            cache.write_text(json.dumps([{
                "question_id": 1, "slug": "bad slug", "difficulty": "Easy"
            }]))
            with patch.object(update_readme, "CACHE_PATH", cache), \
                 patch.object(update_readme, "solution_ids", return_value=[1]), \
                 patch.object(update_readme, "bulk_records", return_value={
                     1: ("two-sum", "Easy")
                 }):
                self.assertEqual(update_readme.load_metadata(), {1: "Easy"})

    def test_stats_and_marker_replacement_are_accurate(self):
        counts = __import__("collections").Counter({"Easy": 1, "Medium": 1, "Hard": 1, "Unknown": 1})
        section = update_readme.stats_section(counts, 4)
        self.assertIn("| Easy | 1 | 25.0% |", section)
        self.assertIn("| Unknown | 1 | 25.0% |", section)
        with tempfile.TemporaryDirectory() as directory:
            readme = Path(directory) / "Readme.md"
            readme.write_text("# Solutions\n\n<!-- SOLUTION_STATS_START -->old<!-- SOLUTION_STATS_END -->\n")
            with patch.object(update_readme, "README", readme):
                update_readme.update_readme(section)
            content = readme.read_text()
            self.assertIn("Total solved: 4", content)
            self.assertNotIn("old", content)


if __name__ == "__main__":
    unittest.main()
