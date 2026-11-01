"""Compare reconstructed values against the installed 32-bit tiswebapi.dll."""
import argparse
from datetime import datetime, timezone, timedelta
import hashlib
import json
from pathlib import Path
import subprocess

from techstream_keys import generate, verify

ROOT = Path(__file__).resolve().parents[1]
SID = "6919BDAC3B1AF548BB2EA44E2D685305"


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--probe", type=Path, required=True)
    p.add_argument("--bin-directory", type=Path, required=True)
    p.add_argument("--output", type=Path, default=ROOT / "evidence/runtime/native-results.json")
    args = p.parse_args()
    results = []

    def native(a, b):
        proc = subprocess.run([str(args.probe.resolve()), str(args.bin_directory.resolve()), a, b],
                              check=True, capture_output=True, text=True, timeout=15)
        result = json.loads(proc.stdout)
        assert result["status"] == 1
        return result["native_hash"]

    vectors = [("abc", "def"), ("a" * 31, "b" * 24),
               ("a" * 32, "b" * 24), ("a" * 63, "b"),
               ("a" * 64, "b" * 64)]
    for a, b in vectors:
        observed = native(a, b)
        expected = hashlib.md5((a + b).encode("ascii")).hexdigest()
        assert observed == expected
        results.append({"test": "native_md5_boundary", "input1": a, "input2": b,
                        "native": observed, "expected": expected, "pass": True})
    for region in ["OT", "NA", "EU"]:
        for days in [1, 30, 9999]:
            r = generate(SID, "18.00.008", days, "2611020115", region)
            h1 = native(r["software_id"], r["major_version"])
            h2 = native(h1, r["region_value"] + r["day_field"] + r["issued_field"])
            assert (h1, h2) == (r["stage1_md5"], r["stage2_md5"])
            assert verify(r["new_key"], SID, "18.00.008", region)
            results.append({"test": "native_two_stage_digest", "region": region,
                            "days": days, "new_key": r["new_key"], "stage1": h1,
                            "stage2": h2, "pass": True,
                            "scope": "DLL digest only; not UI acceptance or duration support"})
    reference = generate(SID, "18.00.008", 30, "2611020115")
    (ROOT / "examples/reference-vector.json").write_text(
        json.dumps(reference, indent=2) + "\n", encoding="utf-8")
    for label, key, sid, version, region in [
        ("digest_mutation", "0" + reference["new_key"][1:], SID, "18.00.008", "OT"),
        ("different_id", reference["new_key"], "0" * 32, "18.00.008", "OT"),
        ("different_major", reference["new_key"], SID, "17.00.008", "OT"),
        ("different_region", reference["new_key"], SID, "18.00.008", "EU"),
    ]:
        fields = {"digest": key[:32], "days": key[32:36], "issued": key[36:]}
        r = generate(sid, version, int(fields["days"]), fields["issued"], region)
        observed = native(native(r["software_id"], r["major_version"]),
                          r["region_value"] + fields["days"] + fields["issued"])
        assert fields["digest"] != observed
        results.append({"test": label, "submitted_digest": fields["digest"],
                        "native_expected_digest": observed, "pass": True,
                        "scope": "native recomputation and comparison, not GUI rejection"})
    dll = args.bin_directory / "tiswebapi.dll"
    record = {"recorded_at": datetime.now(timezone(timedelta(hours=8))).isoformat(),
              "library": "tiswebapi.dll", "sha256": hashlib.sha256(dll.read_bytes()).hexdigest(),
              "architecture": "x86", "probe": "NativeProbe.cs compiled with /platform:x86",
              "tests_passed": len(results), "results": results,
              "gui_registration_test": "not executed by this script; see gui-results.json for the separately recorded run",
              "vehicle_connected": False}
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(record, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"passed": len(results), "output": str(args.output)}, indent=2))


if __name__ == "__main__":
    main()
