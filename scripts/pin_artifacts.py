"""Normalize delivered text to LF and pin the public artifact set."""
import hashlib
import json
import os
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
DEST = ROOT / "evidence/artifact-sha256.json"
SKIP = {".git", "local", "tmp", "__pycache__", ".venv", "build", "dist"}
TEXT = {".md", ".py", ".ps1", ".cs", ".java", ".c", ".txt", ".json", ".toml", ".yml"}
records = {}
for parent, dirs, files in os.walk(ROOT):
    dirs[:] = sorted(d for d in dirs if d not in SKIP and not d.endswith(".egg-info"))
    for name in sorted(files):
        path = Path(parent) / name
        if path == DEST or path.suffix in {".pyc", ".pyo"}:
            continue
        data = path.read_bytes()
        if path.suffix in TEXT or name in {".gitignore", ".gitattributes"}:
            normalized = data.replace(b"\r\n", b"\n")
            if normalized != data:
                path.write_bytes(normalized)
            data = normalized
        records[path.relative_to(ROOT).as_posix()] = hashlib.sha256(data).hexdigest()
DEST.write_text(json.dumps(records, indent=2, sort_keys=True) + "\n", encoding="utf-8", newline="\n")
print(f"Pinned {len(records)} public artifacts.")
