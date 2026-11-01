import unittest
import json
from pathlib import Path
from techstream_keys import generate, verify, inspect_key, decode_rotation
from techstream_keys.algorithm import JP_SLICES

SID = "6919BDAC3B1AF548BB2EA44E2D685305"
ROOT = Path(__file__).resolve().parents[1]


class AlgorithmTests(unittest.TestCase):
    def test_literal_from_native_dll(self):
        self.assertEqual(decode_rotation("`XRAE"), "SKE48")

    def test_fixed_vector(self):
        r = generate(SID, "18.00.008", 30, "2611020115")
        self.assertEqual(r["stage1_md5"], "ea5463fac8b3ecd5cf627d10562b6efc")
        self.assertEqual(r["stage2_md5"], "e7c69e321e4ab1314a490a16296cdc09")
        self.assertEqual(len(r["new_key"]), 46)
        self.assertEqual(inspect_key(r["new_key"])["issued_field"], "2611020115")

    def test_changes_to_identity_and_major_version_fail(self):
        key = generate(SID, "18.00.008", 30, "2611020115")["new_key"]
        self.assertFalse(verify(key, "0" * 32, "18.00.008"))
        self.assertFalse(verify(key, SID, "17.00.008"))
        self.assertTrue(verify(key, SID, "18.01.999"))

    def test_tamper_every_field(self):
        key = generate(SID, "18.00.008", 30, "2611020115")["new_key"]
        for pos in [0, 31, 35, 45]:
            bad = key[:pos] + ("1" if key[pos] != "1" else "2") + key[pos+1:]
            self.assertFalse(verify(bad, SID, "18.00.008"))

    def test_region_is_part_of_digest(self):
        key = generate(SID, "18.00.008", 30, "2611020115")["new_key"]
        self.assertFalse(verify(key, SID, "18.00.008", "EU"))

    def test_bad_inputs(self):
        for days in [0, -1, 10000, True]:
            with self.assertRaises(ValueError):
                generate(SID, "18.00.008", days, "2611020115")
        for issued in ["1793552997", "2613320115", "2611022560", "3801010000", "123"]:
            with self.assertRaises(ValueError):
                generate(SID, "18.00.008", 30, issued)
        for sid in ["G" * 32, "abc", " " + SID]:
            with self.assertRaises(ValueError):
                generate(sid, "18.00.008", 30, "2611020115")
        self.assertFalse(verify("0" * 46, SID, "18.00.008"))

    def test_jp_native_vectors_and_inverse_layout(self):
        record = json.loads((ROOT / "evidence/runtime/native-jp-results.json").read_text())
        for row in record["results"]:
            value = row["value"]
            result = generate(value["software_id"], value["version"], value["days"], value["issued_field"], "JP")
            self.assertEqual(result, value)
            decoded = inspect_key(result["new_key"], "JP")
            for field in ["digest", "day_field", "issued_field"]:
                self.assertEqual(decoded[field], row["parser_recovered"][field])
            self.assertTrue(verify(result["new_key"], value["software_id"], value["version"], "JP"))

    def test_jp_permutation_matches_static_parser(self):
        record = json.loads((ROOT / "evidence/static/JP/analysis.json").read_text())
        indices = [index for start, end in JP_SLICES for index in range(start, end)]
        self.assertEqual(indices, record["permutation_indices"])
        self.assertEqual(sorted(indices), list(range(46)))
        self.assertEqual(decode_rotation("`cpvn14yyrr66>>>E"), "SVciaorlleett1118")

    def test_jp_public_v14_reference_and_unsupported_versions(self):
        original = json.loads((ROOT / "examples/jp-public-reference.json").read_text())
        result = generate(original["software_id"], original["version"], original["days"], original["issued_field"], "JP")
        self.assertEqual(result["new_key"], original["new_key"])
        self.assertEqual(result["stage1_md5"], original["stage1_md5"])
        self.assertEqual(result["stage2_md5"], original["stage2_md5"])
        with self.assertRaisesRegex(ValueError, "JP supports"):
            generate(SID, "19.00.000", 30, "2611020115", "JP")

    def test_jp_detects_tampering_at_every_key_position(self):
        key = generate(SID, "18.00.008", 30, "2611020115", "JP")["new_key"]
        for pos in range(46):
            bad = key[:pos] + ("1" if key[pos] != "1" else "2") + key[pos + 1:]
            self.assertFalse(verify(bad, SID, "18.00.008", "JP"), pos)
        self.assertFalse(verify(key, SID, "18.00.008", "OT"))
        self.assertFalse(verify(key, "0" * 32, "18.00.008", "JP"))
        self.assertFalse(verify(key, SID, "14.00.000", "JP"))
        self.assertTrue(verify(key, SID, "18.01.999", "JP"))


if __name__ == "__main__":
    unittest.main()
