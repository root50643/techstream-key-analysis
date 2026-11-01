import unittest
from techstream_keys import generate, verify, inspect_key, decode_rotation

SID = "6919BDAC3B1AF548BB2EA44E2D685305"


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


if __name__ == "__main__":
    unittest.main()
