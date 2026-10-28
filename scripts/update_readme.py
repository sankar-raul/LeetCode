#!/usr/bin/env python3
"""Update the solution statistics section in Readme.md.

The legacy ``/api/problems/all/`` response is used as a bulk source when it
contains a validated ID, slug, and difficulty.  It is an undocumented
endpoint, so incomplete or malformed responses are treated as untrusted and
the GraphQL question query is used for entries that still need verification.
"""

from __future__ import annotations

import json
import os
import re
import urllib.request
from collections import Counter
from dataclasses import asdict, dataclass, field
from pathlib import Path
from time import sleep
from typing import Any
from urllib.error import HTTPError, URLError


ROOT = Path(__file__).resolve().parents[1]
README = ROOT / "Readme.md"
START_MARKER = "<!-- SOLUTION_STATS_START -->"
END_MARKER = "<!-- SOLUTION_STATS_END -->"
METADATA_URL = os.environ.get(
    "LEETCODE_METADATA_URL", "https://leetcode.com/api/problems/all/"
)
GRAPHQL_URL = os.environ.get("LEETCODE_GRAPHQL_URL", "https://leetcode.com/graphql")
CACHE_PATH = Path(
    os.environ.get("LEETCODE_CACHE_PATH", str(ROOT / ".cache/leetcode-metadata.json"))
)
REQUEST_TIMEOUT = 10
MAX_RETRIES = 2
DIFFICULTIES = {"Easy", "Medium", "Hard"}
DIFFICULTY_LEVELS = {1: "Easy", 2: "Medium", 3: "Hard"}
QUESTION_QUERY = """
query question($titleSlug: String!) {
  question(titleSlug: $titleSlug) {
    questionFrontendId
    titleSlug
    difficulty
  }
}
"""
_QUESTION_CACHE: dict[tuple[int, str], str] = {}


@dataclass(frozen=True)
class VerifiedMetadata:
    question_id: int
    slug: str
    difficulty: str


@dataclass
class Diagnostics:
    total_ids: int = 0
    resolved_slugs: int = 0
    verified_easy: int = 0
    verified_medium: int = 0
    verified_hard: int = 0
    missing_slug_mappings: int = 0
    graphql_errors: int = 0
    malformed_responses: int = 0
    id_slug_mismatches: int = 0
    timeouts: int = 0
    http_errors: int = 0
    rate_limit_failures: int = 0
    unresolved: int = 0
    examples: list[str] = field(default_factory=list)

    def example(self, message: str) -> None:
        if len(self.examples) < 3:
            self.examples.append(message)


_DIAGNOSTICS = Diagnostics()


def solution_ids() -> list[int]:
    """Return one numeric ID for each top-level solution directory."""
    ids = []
    for path in ROOT.iterdir():
        if not path.is_dir():
            continue
        match = re.match(r"^(\d+)(?:\s|$)", path.name)
        if match:
            ids.append(int(match.group(1)))
    return sorted(set(ids))


def request_json(url: str, payload: dict[str, Any] | None = None) -> Any:
    headers = {
        "Accept": "application/json",
        "User-Agent": "sankar-raul/LeetCode statistics updater",
    }
    data = None
    if payload is not None:
        headers["Content-Type"] = "application/json"
        data = json.dumps(payload).encode("utf-8")

    for attempt in range(MAX_RETRIES + 1):
        request = urllib.request.Request(url, data=data, headers=headers)
        try:
            with urllib.request.urlopen(request, timeout=REQUEST_TIMEOUT) as response:
                return json.load(response)
        except HTTPError as error:
            retryable = error.code == 429 or error.code in {500, 502, 503, 504}
            if not retryable or attempt == MAX_RETRIES:
                _DIAGNOSTICS.http_errors += 1
                if error.code == 429:
                    _DIAGNOSTICS.rate_limit_failures += 1
                _DIAGNOSTICS.example(f"HTTP {error.code} from {url}")
                raise
            retry_after = error.headers.get("Retry-After") if error.headers else None
            try:
                delay = min(float(retry_after), 30.0) if retry_after else 0.25 * (2**attempt)
            except ValueError:
                delay = 0.25 * (2**attempt)
        except (URLError, TimeoutError):
            if attempt == MAX_RETRIES:
                _DIAGNOSTICS.timeouts += 1
                _DIAGNOSTICS.example(f"timeout or network error from {url}")
                raise
            delay = 0.25 * (2**attempt)
        sleep(delay)

    raise RuntimeError("LeetCode request failed")


def _question_id(value: Any) -> int | None:
    if isinstance(value, bool):
        return None
    if isinstance(value, int):
        result = value
    elif isinstance(value, str) and re.fullmatch(r"\d+", value):
        result = int(value)
    else:
        return None
    return result if result > 0 else None


def _difficulty(value: Any) -> str | None:
    if isinstance(value, dict):
        value = value.get("level")
    if isinstance(value, int) and not isinstance(value, bool):
        return DIFFICULTY_LEVELS.get(value)
    return value if value in DIFFICULTIES else None


def _valid_slug(value: Any) -> bool:
    return isinstance(value, str) and bool(value) and bool(re.fullmatch(r"[a-z0-9-]+", value))


def _bulk_records(payload: Any) -> dict[int, tuple[str, str | None]]:
    """Parse validated ID-to-slug records from the bulk response."""
    if not isinstance(payload, dict) or not isinstance(
        payload.get("stat_status_pairs"), list
    ):
        _DIAGNOSTICS.malformed_responses += 1
        raise ValueError("LeetCode problem response was malformed")

    records: dict[int, tuple[str, str | None]] = {}
    for entry in payload["stat_status_pairs"]:
        if not isinstance(entry, dict) or not isinstance(entry.get("stat"), dict):
            _DIAGNOSTICS.malformed_responses += 1
            continue
        stat = entry["stat"]
        question_id = _question_id(stat.get("question_id"))
        slug = stat.get("question__title_slug")
        if question_id is None or not _valid_slug(slug):
            continue
        records[question_id] = (slug, _difficulty(entry.get("difficulty")))
    if not records:
        raise RuntimeError("LeetCode problem response had no valid ID-to-slug records")
    return records


def bulk_records() -> dict[int, tuple[str, str | None]]:
    """Fetch the undocumented bulk source without trusting incomplete records."""
    return _bulk_records(request_json(METADATA_URL))


def bulk_metadata() -> dict[int, VerifiedMetadata]:
    """Return complete, verified records from LeetCode's bulk response.

    This endpoint is undocumented and can omit newer questions.  Records
    missing any of the three required fields are deliberately excluded.
    """
    metadata = {
        question_id: VerifiedMetadata(question_id, slug, difficulty)
        for question_id, (slug, difficulty) in bulk_records().items()
        if difficulty is not None
    }
    if not metadata:
        raise RuntimeError("LeetCode problem response had no valid metadata")
    return metadata


def problem_slugs() -> dict[int, str]:
    """Return validated numeric ID-to-slug mappings from the bulk source."""
    return {question_id: slug for question_id, (slug, _) in bulk_records().items()}


def question_metadata(question_id: int, slug: str) -> str | None:
    cached = _QUESTION_CACHE.get((question_id, slug))
    if cached is not None:
        return cached

    payload = request_json(
        GRAPHQL_URL,
        {"query": QUESTION_QUERY, "variables": {"titleSlug": slug}},
    )
    if not isinstance(payload, dict):
        _DIAGNOSTICS.malformed_responses += 1
        return None
    if payload.get("errors"):
        _DIAGNOSTICS.graphql_errors += 1
        _DIAGNOSTICS.example(f"GraphQL error for {question_id}/{slug}")
        return None
    data = payload.get("data")
    question = data.get("question") if isinstance(data, dict) else None
    if question is None:
        _DIAGNOSTICS.missing_slug_mappings += 1
        return None
    if not isinstance(question, dict):
        _DIAGNOSTICS.malformed_responses += 1
        return None

    returned_id = _question_id(question.get("questionFrontendId"))
    returned_slug = question.get("titleSlug")
    difficulty = _difficulty(question.get("difficulty"))
    if returned_id != question_id or returned_slug != slug:
        _DIAGNOSTICS.id_slug_mismatches += 1
        _DIAGNOSTICS.example(f"ID/slug mismatch for {question_id}/{slug}")
        return None
    if difficulty is None:
        _DIAGNOSTICS.malformed_responses += 1
        return None
    _QUESTION_CACHE[(question_id, slug)] = difficulty
    return difficulty


def _load_cache() -> dict[int, VerifiedMetadata]:
    try:
        payload = json.loads(CACHE_PATH.read_text(encoding="utf-8"))
    except (FileNotFoundError, OSError, json.JSONDecodeError):
        return {}
    if not isinstance(payload, list):
        return {}
    result = {}
    for entry in payload:
        if not isinstance(entry, dict):
            continue
        question_id = _question_id(entry.get("question_id"))
        slug = entry.get("slug")
        difficulty = _difficulty(entry.get("difficulty"))
        if question_id is not None and _valid_slug(slug) and difficulty is not None:
            result[question_id] = VerifiedMetadata(question_id, slug, difficulty)
    return result


def _save_cache(metadata: dict[int, VerifiedMetadata]) -> None:
    try:
        CACHE_PATH.parent.mkdir(parents=True, exist_ok=True)
        CACHE_PATH.write_text(
            json.dumps([asdict(item) for item in sorted(metadata.values(), key=lambda x: x.question_id)],
                       indent=2) + "\n",
            encoding="utf-8",
        )
    except OSError:
        _DIAGNOSTICS.example(f"could not write cache {CACHE_PATH}")


def load_metadata() -> dict[int, str]:
    global _DIAGNOSTICS
    _DIAGNOSTICS = Diagnostics()
    ids = solution_ids()
    _DIAGNOSTICS.total_ids = len(ids)
    cached = _load_cache()
    resolved: dict[int, VerifiedMetadata] = {
        question_id: cached[question_id] for question_id in ids if question_id in cached
    }
    remaining = set(ids) - set(resolved)

    bulk: dict[int, tuple[str, str | None]] = {}
    if remaining:
        try:
            bulk = bulk_records()
        except (
            HTTPError,
            URLError,
            TimeoutError,
            ValueError,
            RuntimeError,
            json.JSONDecodeError,
        ):
            bulk = {}

    for question_id in remaining:
        record = bulk.get(question_id)
        if record is not None:
            slug, difficulty = record
            _DIAGNOSTICS.resolved_slugs += 1
            if difficulty is not None:
                resolved[question_id] = VerifiedMetadata(question_id, slug, difficulty)
                continue
        else:
            _DIAGNOSTICS.missing_slug_mappings += 1

        slug = record[0] if record is not None else None
        if slug is None:
            continue
        try:
            difficulty = question_metadata(question_id, slug)
        except (HTTPError, URLError, TimeoutError, ValueError, TypeError, json.JSONDecodeError):
            continue
        if difficulty is not None:
            resolved[question_id] = VerifiedMetadata(question_id, slug, difficulty)

    _DIAGNOSTICS.resolved_slugs = len(
        (set(cached) | set(bulk)) & set(ids)
    )
    _DIAGNOSTICS.unresolved = len(ids) - len(resolved)
    counts = Counter(item.difficulty for item in resolved.values())
    _DIAGNOSTICS.verified_easy = counts["Easy"]
    _DIAGNOSTICS.verified_medium = counts["Medium"]
    _DIAGNOSTICS.verified_hard = counts["Hard"]
    _save_cache(resolved)
    return {question_id: item.difficulty for question_id, item in resolved.items()}


def stats_section(counts: Counter[str], total: int) -> str:
    rows = []
    for difficulty in ("Easy", "Medium", "Hard", "Unknown"):
        count = counts[difficulty]
        percentage = count / total * 100 if total else 0
        rows.append(f"| {difficulty} | {count} | {percentage:.1f}% |")

    return "\n".join(
        [
            START_MARKER,
            "## Solution Statistics",
            "",
            f"**Total solved: {total}**",
            "",
            "| Difficulty | Solved | Share |",
            "| --- | ---: | ---: |",
            *rows,
            "",
            "_This section is updated automatically by GitHub Actions._",
            END_MARKER,
        ]
    )


def update_readme(section: str) -> None:
    content = README.read_text(encoding="utf-8") if README.exists() else "# LeetCode Solutions\n\n"
    pattern = re.compile(
        re.escape(START_MARKER) + r".*?" + re.escape(END_MARKER), re.DOTALL
    )
    if pattern.search(content):
        content = pattern.sub(section, content, count=1)
    else:
        content = content.rstrip() + "\n\n" + section + "\n"
    README.write_text(content, encoding="utf-8")


def print_diagnostics() -> None:
    values = asdict(_DIAGNOSTICS)
    examples = values.pop("examples")
    print("Metadata diagnostics: " + ", ".join(f"{key}={value}" for key, value in values.items()))
    for example in examples:
        print(f"Metadata example: {example}")


def main() -> None:
    ids = solution_ids()
    metadata = load_metadata()
    counts = Counter(metadata.get(problem_id, "Unknown") for problem_id in ids)
    update_readme(stats_section(counts, len(ids)))
    print_diagnostics()


if __name__ == "__main__":
    main()
