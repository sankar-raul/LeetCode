#!/usr/bin/env python3
"""Update the solution statistics section in Readme.md."""

from __future__ import annotations

import json
import os
import re
import urllib.request
from urllib.error import HTTPError, URLError
from collections import Counter
from pathlib import Path
from time import sleep
from typing import Any


ROOT = Path(__file__).resolve().parents[1]
README = ROOT / "Readme.md"
START_MARKER = "<!-- SOLUTION_STATS_START -->"
END_MARKER = "<!-- SOLUTION_STATS_END -->"
METADATA_URL = os.environ.get(
    "LEETCODE_METADATA_URL", "https://leetcode.com/api/problems/all/"
)
GRAPHQL_URL = os.environ.get("LEETCODE_GRAPHQL_URL", "https://leetcode.com/graphql")
REQUEST_TIMEOUT = 10
MAX_RETRIES = 2
DIFFICULTIES = {"Easy", "Medium", "Hard"}
QUESTION_QUERY = """
query question($titleSlug: String!) {
  question(titleSlug: $titleSlug) {
    questionFrontendId
    title
    titleSlug
    difficulty
  }
}
"""
_QUESTION_CACHE: dict[tuple[int, str], str] = {}


def solution_ids() -> list[int]:
    ids = []
    for path in ROOT.iterdir():
        if not path.is_dir():
            continue
        match = re.match(r"^(\d+)\s+", path.name)
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
            if error.code not in {429, 500, 502, 503, 504} or attempt == MAX_RETRIES:
                raise
        except (URLError, TimeoutError):
            if attempt == MAX_RETRIES:
                raise
        sleep(0.25 * (attempt + 1))

    raise RuntimeError("LeetCode request failed")


def problem_slugs() -> dict[int, str]:
    payload = request_json(METADATA_URL)
    if not isinstance(payload, dict):
        raise ValueError("LeetCode problem response was not an object")
    slugs = {}
    for entry in payload.get("stat_status_pairs", []):
        stat = entry.get("stat", {})
        question_id = stat.get("question_id")
        slug = stat.get("question__title_slug")
        if question_id is None or not isinstance(slug, str) or not slug:
            continue
        try:
            slugs[int(question_id)] = slug
        except (TypeError, ValueError):
            continue
    if not slugs:
        raise RuntimeError("LeetCode problem response did not contain question slugs")
    return slugs


def question_metadata(question_id: int, slug: str) -> str | None:
    cached = _QUESTION_CACHE.get((question_id, slug))
    if cached is not None:
        return cached

    payload = request_json(
        GRAPHQL_URL,
        {"query": QUESTION_QUERY, "variables": {"titleSlug": slug}},
    )
    if not isinstance(payload, dict):
        return None
    data = payload.get("data")
    if not isinstance(data, dict):
        return None
    question = data.get("question")
    if not isinstance(question, dict):
        return None

    returned_id = question.get("questionFrontendId")
    returned_slug = question.get("titleSlug")
    difficulty = question.get("difficulty")
    if str(returned_id) != str(question_id) or returned_slug != slug:
        return None
    if difficulty not in DIFFICULTIES:
        return None
    _QUESTION_CACHE[(question_id, slug)] = difficulty
    return difficulty


def load_metadata() -> dict[int, str]:
    try:
        slugs = problem_slugs()
    except (
        HTTPError,
        URLError,
        TimeoutError,
        ValueError,
        RuntimeError,
        json.JSONDecodeError,
    ):
        return {}
    metadata = {}
    for problem_id in solution_ids():
        slug = slugs.get(problem_id)
        if slug is None:
            continue
        try:
            difficulty = question_metadata(problem_id, slug)
        except (
            HTTPError,
            URLError,
            TimeoutError,
            TypeError,
            ValueError,
            AttributeError,
            json.JSONDecodeError,
        ):
            continue
        if difficulty is not None:
            metadata[problem_id] = difficulty
    return metadata


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
    if README.exists():
        content = README.read_text(encoding="utf-8")
    else:
        content = "# LeetCode Solutions\n\n"

    pattern = re.compile(
        re.escape(START_MARKER) + r".*?" + re.escape(END_MARKER),
        re.DOTALL,
    )
    if pattern.search(content):
        content = pattern.sub(section, content, count=1)
    else:
        content = content.rstrip() + "\n\n" + section + "\n"

    README.write_text(content, encoding="utf-8")


def main() -> None:
    ids = solution_ids()
    metadata = load_metadata()
    counts = Counter(metadata.get(problem_id, "Unknown") for problem_id in ids)
    update_readme(stats_section(counts, len(ids)))


if __name__ == "__main__":
    main()
