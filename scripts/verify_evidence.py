"""Verify delivered evidence against pinned hashes without accessing native binaries."""
import hashlib
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
manifest_path = ROOT / "evidence/artifact-sha256.json"
manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
failures = []
for name, expected in manifest.items():
    p = ROOT / name
    if not p.is_file() or hashlib.sha256(p.read_bytes()).hexdigest() != expected:
        failures.append(name)
if failures:
    raise SystemExit("Missing or modified artifacts: " + ", ".join(failures))
print(f"Verified {len(manifest)} delivered artifacts.")
