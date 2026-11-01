"""Validate JP digests with installed x86 DLLs and the independently extracted MainMenu parser."""
import argparse
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import subprocess

from techstream_keys import generate, verify

ROOT = Path(__file__).resolve().parents[1]
SID = "6919BDAC3B1AF548BB2EA44E2D685305"


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--probe", type=Path, required=True)
    parser.add_argument("--bin-directory", type=Path, required=True)
    args = parser.parse_args()
    binaries = {name: hashlib.sha256((args.bin_directory / name).read_bytes()).hexdigest()
                for name in ["MainMenu.exe", "tiswebapi.dll", "IT3Versatile.dll"]}
    manifest = json.loads((ROOT / "evidence/static/binary-manifest.json").read_text())
    for entry in manifest["samples"]:
        assert binaries[entry["name"]] == entry["sha256"], f"Installed binary differs from pinned sample: {entry['name']}"
    static = json.loads((ROOT / "evidence/static/JP/analysis.json").read_text())
    reference = json.loads((ROOT / "examples/jp-public-reference.json").read_text())

    def call(a, b):
        process = subprocess.run([str(args.probe.resolve()), str(args.bin_directory.resolve()), a, b],
                                 check=True, capture_output=True, text=True, timeout=15)
        return json.loads(process.stdout)

    decoded = call("--decode-region", static["constant"]["encoded"])["decoded_value"]
    assert decoded == static["constant"]["decoded"] == "SVciaorlleett1118"
    vectors = [(SID, "18.00.008", days, "2611020115") for days in [1, 30, 365, 9999]]
    vectors += [("0" * 32, "18.00.008", days, "2611020116") for days in [1, 30]]
    vectors += [(reference["software_id"], "18.00.008", 5000, reference["issued_field"]),
                (SID, "18.00.008", 30, "3712312359"), (SID, "18.00.008", 30, "2402292359"),
                (reference["software_id"], reference["version"], reference["days"], reference["issued_field"])]
    results = []
    for sid, version, days, issued in vectors:
        value = generate(sid, version, days, issued, "JP")
        h1 = call(value["day_field"] + "Japan", value["software_id"])["native_hash"]
        h2 = call(value["region_value"] + issued, h1 + value["major_version"])["native_hash"]
        assert (h1, h2) == (value["stage1_md5"], value["stage2_md5"])
        recovered = {field: "".join(value["new_key"][entry["start"]:entry["start"] + entry["length"]]
                                     for entry in entries)
                     for field, entries in static["inverse_parser_calls"].items()}
        assert (recovered["digest"], recovered["day_field"], recovered["issued_field"]) == (h2, value["day_field"], issued)
        assert verify(value["new_key"], sid, version, "JP")
        if value["major_version"] == "14":
            assert value["new_key"] == reference["new_key"]
        results.append({"test": "native_jp_two_stage_digest", "pass": True,
                        "value": value, "native_stage1": h1, "native_stage2": h2,
                        "parser_recovered": recovered,
                        "scope": "Installed v18 MD5 calls plus static MainMenu inverse-layout check; no GUI acceptance claim"})
    record = {"recorded_at": datetime.now(timezone.utc).isoformat(), "architecture": "x86",
              "binary_sha256": binaries,
              "native_rotation": {"encoded": static["constant"]["encoded"], "decoded": decoded, "pass": True},
              "tests_passed": len(results) + 1, "results": results,
              "gui_registration_test": "not performed for JP", "vehicle_connected": False,
              "installed_binary_modified": False, "registration_settings_modified": False}
    path = ROOT / "evidence/runtime/native-jp-results.json"
    path.write_text(json.dumps(record, indent=2) + "\n", encoding="utf-8")
    sample = next(row["value"] for row in results if row["value"]["software_id"] == SID
                  and row["value"]["days"] == 30 and row["value"]["issued_field"] == "2611020115")
    (ROOT / "examples/jp-reference-vector.json").write_text(json.dumps(sample, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"passed": record["tests_passed"], "output": str(path), "jp18_key": sample["new_key"]}))


if __name__ == "__main__":
    main()
