"""Package the selected exports from this analysis; original binaries stay local."""
from datetime import datetime, timezone, timedelta
import hashlib
import json
from pathlib import Path
import shutil

ROOT = Path(__file__).resolve().parents[1]


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    bins = Path(r"C:\Program Files (x86)\Toyota Diagnostics\Techstream\bin")
    original = ROOT.parent / "analysis/extracted/payload/Techstream_Bin"
    manifest = {"recorded_at": datetime.now(timezone(timedelta(hours=8))).isoformat(),
                "samples": [], "toolchain": {"ghidra": "12.1.4", "java": "21",
                                              "architecture": "x86:LE:32"}}
    for name in ["MainMenu.exe", "tiswebapi.dll", "IT3Versatile.dll"]:
        p = bins / name
        sample = ROOT / "local/samples" / name
        assert sha(p) == sha(sample), f"Installed binary changed: {name}"
        record = {"name": name, "size": p.stat().st_size, "sha256": sha(p),
                  "copied_sample_equal": True}
        if (original / name).is_file():
            record["matches_existing_installer_extraction"] = sha(p) == sha(original/name)
        manifest["samples"].append(record)
    (ROOT / "evidence/static/binary-manifest.json").write_text(
        json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    for source, target, entries in [
        ("core", "MainMenu", ["004218b0", "00420d80", "004a9e40", "00425100", "00423330", "004b6110"]),
        ("tis-core", "tiswebapi", ["10001160", "10010480", "10003860", "10003890", "10003990", "10003a50"]),
    ]:
        dest = ROOT / "evidence/static" / target
        dest.mkdir(parents=True, exist_ok=True)
        for entry in entries:
            for ext in [".c", ".asm.txt"]:
                shutil.copyfile(ROOT / "local" / source / (entry + ext), dest / (entry + ext))
    asm = (ROOT / "local/core/0041d500.asm.txt").read_text(encoding="utf-8").splitlines()
    spans = [("0041de30", "0041dec3"), ("0041e21b", "0041e3e0")]
    excerpt = ["# MainMenu.exe!0041d500: selected date/field/digest call-site ranges"]
    for start, end in spans:
        excerpt.extend(s for s in asm if start <= s[:8] <= end)
        excerpt.append("")
    (ROOT / "evidence/static/MainMenu/date-flow.asm.txt").write_text(
        "\n".join(excerpt), encoding="utf-8")
    runtime = ROOT / "evidence/runtime"
    key = json.loads((ROOT / "examples/reference-vector.json").read_text(encoding="utf-8"))["new_key"]
    assert "30d 00h 00m" in (runtime / "gui-success.txt").read_text(encoding="utf-8")
    assert key in (runtime / "gui-current-key.txt").read_text(encoding="utf-8")
    assert "29d 23h 58m" in (runtime / "gui-restarted.txt").read_text(encoding="utf-8")
    config = bins.parent / "Env/IT3UserCustom.ini"
    assert ("MhbdordJdx=" + key) in config.read_text(encoding="cp1252")
    gui = {"recorded_at": datetime.now(timezone(timedelta(hours=8))).isoformat(),
           "software_id": "6919BDAC3B1AF548BB2EA44E2D685305", "version": "18.00.008",
           "region": "OT", "key": key, "days": 30,
           "invalid_46_zeros": {"submitted": True, "accepted": False,
                                "observed": "dialog rebuilt, New Key cleared, Current Key empty",
                                "standalone_error_dialog_observed": False},
           "generated_key": {"submitted": True, "accepted": True,
                             "initial_expiration_display": "30d 00h 00m",
                             "current_key_equal": True, "config_key_equal": True},
           "restart": {"verified": True, "expiration_display": "29d 23h 58m",
                       "new_window_id": 7606734,
                       "note": "Closed window; ended remaining windowless MainMenu process; launched a new process."},
           "environment_events": ["Desktop input denied until user restored access",
                                  "Local Error Report dialog dismissed using Don't send"],
           "installed_binary_modified": False, "vehicle_connected": False,
           "registration_state_left_in_place": True,
           "pretest_config_backup": "local/backup/IT3UserCustom.ini (gitignored)"}
    (runtime / "gui-results.json").write_text(json.dumps(gui, indent=2) + "\n", encoding="utf-8")
    native_path = runtime / "native-results.json"
    native = json.loads(native_path.read_text(encoding="utf-8"))
    native["gui_registration_test"] = "passed separately; see gui-results.json"
    native_path.write_text(json.dumps(native, indent=2) + "\n", encoding="utf-8")
    print("Packaged static evidence, binary hashes and GUI results.")


if __name__ == "__main__":
    main()
