#!/usr/bin/env python3
"""Update the solution statistics section in Readme.md."""

from __future__ import annotations

import json
import os
import re
import urllib.request
from collections import Counter
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
README = ROOT / "Readme.md"
START_MARKER = "<!-- SOLUTION_STATS_START -->"
END_MARKER = "<!-- SOLUTION_STATS_END -->"
METADATA_URL = os.environ.get(
    "LEETCODE_METADATA_URL", "https://leetcode.com/api/problems/all/"
)


def solution_ids() -> list[int]:
    ids = []
    for path in ROOT.iterdir():
        if not path.is_dir():
            continue
        match = re.match(r"^(\d+)\s+", path.name)
        if match:
            ids.append(int(match.group(1)))
    return sorted(set(ids))


def load_metadata() -> dict[int, str]:
    request = urllib.request.Request(
        METADATA_URL,
        headers={"User-Agent": "sankar-raul/LeetCode statistics updater"},
    )
    with urllib.request.urlopen(request, timeout=30) as response:
        payload = json.load(response)

    levels = {1: "Easy", 2: "Medium", 3: "Hard"}
    metadata = {}
    for entry in payload.get("stat_status_pairs", []):
        stat = entry.get("stat", {})
        question_id = stat.get("question_id")
        level = levels.get(entry.get("difficulty", {}).get("level"))
        if question_id is not None and level:
            metadata[int(question_id)] = level
    if not metadata:
        raise RuntimeError("LeetCode metadata response did not contain any problems")
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
