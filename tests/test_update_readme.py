import json
import unittest
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


class UpdateReadmeTests(unittest.TestCase):
    def test_question_metadata_accepts_all_supported_difficulties(self):
        responses = [
            FakeResponse(
                {
                    "data": {
                        "question": {
                            "questionFrontendId": str(question_id),
                            "title": title,
                            "titleSlug": slug,
                            "difficulty": difficulty,
                        }
                    }
                }
            )
            for question_id, title, slug, difficulty in (
                (101, "Easy Problem", "easy-problem", "Easy"),
                (102, "Medium Problem", "medium-problem", "Medium"),
                (103, "Hard Problem", "hard-problem", "Hard"),
            )
        ]
        with patch(
            "scripts.update_readme.urllib.request.urlopen", side_effect=responses
        ):
            self.assertEqual(update_readme.question_metadata(101, "easy-problem"), "Easy")
            self.assertEqual(
                update_readme.question_metadata(102, "medium-problem"), "Medium"
            )
            self.assertEqual(update_readme.question_metadata(103, "hard-problem"), "Hard")

    def test_question_metadata_uses_cached_valid_metadata(self):
        response = FakeResponse(
            {
                "data": {
                    "question": {
                        "questionFrontendId": "104",
                        "title": "Cached Problem",
                        "titleSlug": "cached-problem",
                        "difficulty": "Easy",
                    }
                }
            }
        )
        with patch(
            "scripts.update_readme.urllib.request.urlopen", return_value=response
        ) as urlopen:
            self.assertEqual(
                update_readme.question_metadata(104, "cached-problem"), "Easy"
            )
            self.assertEqual(
                update_readme.question_metadata(104, "cached-problem"), "Easy"
            )
            urlopen.assert_called_once()

    def test_question_metadata_rejects_mismatched_problem(self):
        response = FakeResponse(
            {
                "data": {
                    "question": {
                        "questionFrontendId": "2",
                        "title": "Add Two Numbers",
                        "titleSlug": "add-two-numbers",
                        "difficulty": "Medium",
                    }
                }
            }
        )
        with patch(
            "scripts.update_readme.urllib.request.urlopen", return_value=response
        ):
            self.assertIsNone(update_readme.question_metadata(1, "two-sum"))

    def test_question_metadata_rejects_missing_question(self):
        response = FakeResponse({"data": {"question": None}})
        with patch(
            "scripts.update_readme.urllib.request.urlopen", return_value=response
        ):
            self.assertIsNone(update_readme.question_metadata(1, "missing"))

    def test_question_metadata_rejects_malformed_response(self):
        response = FakeResponse({"data": {"question": {"difficulty": "Easy"}}})
        with patch(
            "scripts.update_readme.urllib.request.urlopen", return_value=response
        ):
            self.assertIsNone(update_readme.question_metadata(105, "malformed"))

    def test_request_retries_rate_limits(self):
        error = HTTPError("https://leetcode.com/graphql", 429, "rate limited", {}, None)
        response = FakeResponse({"data": {}})
        with patch(
            "scripts.update_readme.urllib.request.urlopen",
            side_effect=[error, response],
        ), patch("scripts.update_readme.sleep"):
            self.assertEqual(
                update_readme.request_json(update_readme.GRAPHQL_URL, {}), {"data": {}}
            )

    def test_request_retries_timeouts_with_bounded_timeout(self):
        response = FakeResponse({"data": {}})
        with patch(
            "scripts.update_readme.urllib.request.urlopen",
            side_effect=[TimeoutError(), response],
        ) as urlopen, patch("scripts.update_readme.sleep"):
            self.assertEqual(
                update_readme.request_json(update_readme.GRAPHQL_URL, {}), {"data": {}}
            )
            self.assertEqual(urlopen.call_args_list[0].kwargs["timeout"], 10)

    def test_problem_slugs_resolves_numeric_ids_to_slugs(self):
        response = FakeResponse(
            {
                "stat_status_pairs": [
                    {"stat": {"question_id": 1, "question__title_slug": "two-sum"}},
                    {"stat": {"question_id": 2, "question__title_slug": "add-two-numbers"}},
                ]
            }
        )
        with patch(
            "scripts.update_readme.urllib.request.urlopen", return_value=response
        ):
            self.assertEqual(
                update_readme.problem_slugs(),
                {1: "two-sum", 2: "add-two-numbers"},
            )

    def test_load_metadata_preserves_unknown_when_slug_lookup_times_out(self):
        with patch(
            "scripts.update_readme.request_json",
            side_effect=URLError("timed out"),
        ), patch.object(
            update_readme, "solution_ids", return_value=[1]
        ):
            self.assertEqual(update_readme.load_metadata(), {})


if __name__ == "__main__":
    unittest.main()
