"""Extract JP constants and the inverse layout from the installed PE and Ghidra exports."""
import argparse
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import re
import struct

ROOT = Path(__file__).resolve().parents[1]


def pe_string(data, address):
    pe = struct.unpack_from("<I", data, 0x3c)[0]
    sections = struct.unpack_from("<H", data, pe + 6)[0]
    optional = pe + 24
    base = struct.unpack_from("<I", data, optional + 28)[0]
    table = optional + struct.unpack_from("<H", data, pe + 20)[0]
    rva = address - base
    for i in range(sections):
        section = struct.unpack_from("<8sIIIIIIHHI", data, table + 40 * i)
        if section[2] <= rva < section[2] + max(section[1], section[3]):
            offset = section[4] + rva - section[2]
            return offset, data[offset:data.index(0, offset)]
    raise ValueError(f"Address outside PE sections: {address:x}")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--binary-directory", type=Path, default=Path(r"C:\Program Files (x86)\Toyota Diagnostics\Techstream\bin"))
    parser.add_argument("--decompiled-directory", type=Path, default=ROOT / "evidence/static/MainMenu")
    args = parser.parse_args()
    raw = (args.binary_directory / "MainMenu.exe").read_bytes()
    digest = hashlib.sha256(raw).hexdigest()
    manifest = json.loads((ROOT / "evidence/static/binary-manifest.json").read_text())
    expected = next(row["sha256"] for row in manifest["samples"] if row["name"] == "MainMenu.exe")
    assert digest == expected, "Installed MainMenu.exe differs from the pinned analysis sample"
    offset, encoded = pe_string(raw, 0x5144d4)
    decoded = "".join(chr(c - 13 + (75 if c - 13 < 48 else 0)) for c in encoded)
    parser_path = args.decompiled_directory / "004218b0.asm.txt"
    lines = parser_path.read_text(encoding="utf-8").splitlines()
    calls = []
    for i, line in enumerate(lines):
        address = int(line.split()[0], 16)
        if 0x421c2d <= address <= 0x421e23 and "CALL 0x004bdf9e" in line:
            pushes = [re.search(r"PUSH (\S+)", row).group(1)
                      for row in lines[i-6:i] if "PUSH " in row]
            length, start = pushes[-3:-1]
            start = 0 if start == "EBX" else int(start, 16)
            calls.append({"call": f"{address:08x}", "start": start, "length": int(length, 16)})
    assert len(calls) == 13
    groups = {"day_field": calls[:3], "issued_field": calls[3:9], "digest": calls[9:]}
    assert [sum(c["length"] for c in groups[k]) for k in groups] == [4, 10, 32]
    permutation = [None] * 46
    for name, canonical_start in [("digest", 0), ("day_field", 32), ("issued_field", 36)]:
        cursor = canonical_start
        for call in groups[name]:
            for index in range(call["length"]):
                target = call["start"] + index
                assert permutation[target] is None
                permutation[target] = cursor + index
            cursor += call["length"]
    assert sorted(permutation) == list(range(46))
    segments = []
    for index in permutation:
        if segments and segments[-1][1] == index:
            segments[-1][1] += 1
        else:
            segments.append([index, index + 1])
    output = ROOT / "evidence/static/JP"
    output.mkdir(exist_ok=True)
    index_path = args.decompiled_directory / "index.json"
    if index_path.is_file():
        index = json.loads(index_path.read_text(encoding="utf-8"))
        assert all(row["complete"] for row in index["functions"])
        (output / "decompilation-index.json").write_text(json.dumps(index, indent=2) + "\n", encoding="utf-8")
    record = {"recorded_at": datetime.now(timezone.utc).isoformat(),
              "binary": "MainMenu.exe", "sha256": digest, "version": "18.00.008",
              "constant": {"va": "005144d4", "file_offset": f"{offset:08x}",
                           "encoded_hex": encoded.hex(), "encoded": encoded.decode("ascii"), "decoded": decoded},
              "parser_export_sha256": hashlib.sha256(parser_path.read_bytes().replace(b"\r\n", b"\n")).hexdigest(),
              "inverse_parser_calls": groups, "permutation_indices": permutation,
              "permutation_segments": segments,
              "verification": "Static inverse field extraction; not a GUI registration acceptance test"}
    (output / "analysis.json").write_text(json.dumps(record, indent=2) + "\n", encoding="utf-8")
    selected = []
    for name, low, high in [("00420d80", 0x4212ed, 0x42154a),
                            ("004218b0", 0x421c0a, 0x421ec0)]:
        selected.append(f"# MainMenu.exe!{name}: JP calculation / inverse parsing")
        selected.extend(row for row in (args.decompiled_directory / (name + ".asm.txt")).read_text(encoding="utf-8").splitlines()
                        if low <= int(row.split()[0], 16) <= high)
        selected.append("")
    (output / "jp-flow.asm.txt").write_text("\n".join(selected), encoding="utf-8")
    print(json.dumps({"region_value": decoded, "permutation_segments": segments, "output": str(output)}))


if __name__ == "__main__":
    main()
