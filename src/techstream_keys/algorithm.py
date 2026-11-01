"""Model reconstructed from the locally installed MainMenu and tiswebapi binaries.

This models the registration digest and field layout. It does not model the
application's persistence, clock checks, replacement policy or online services.
"""
from datetime import datetime
import hashlib
import re

ENCODED_REGION_VALUES = {
    "OT": "`XRAE",
    "NA": "W:R[_BTnx;a9",
    "EU": "Z;]4>7Bv5`>pxEB@CB",
}


def decode_rotation(encoded: str, shift: int = 13) -> str:
    """IT3Versatile.dll!DecryptByRotatShiftVariable, for ASCII input."""
    if not 0 <= shift <= 73:
        shift = 13
    if not encoded.isascii():
        raise ValueError("rotation input must be ASCII")
    values = [ord(c) - shift for c in encoded]
    return "".join(chr((v + 75 if v < 48 else v) & 255) for v in values)


def _inputs(software_id: str, version: str, region: str):
    if not re.fullmatch(r"[0-9A-Fa-f]{32}", software_id):
        raise ValueError("Software ID must contain exactly 32 hex characters")
    if not re.fullmatch(r"[0-9]+\.[0-9]{2}\.[0-9]{3}", version):
        raise ValueError("version must use the form 18.00.008")
    region = region.upper()
    if region not in ENCODED_REGION_VALUES:
        raise ValueError("supported regions: OT, NA, EU; JP has a different layout")
    return software_id.upper(), version.split(".")[0], region


def _md5(text: str) -> str:
    return hashlib.md5(text.encode("ascii")).hexdigest()


def generate(software_id: str, version: str, days: int, issued: str,
             region: str = "OT") -> dict:
    """Generate a deterministic 46-character key with all intermediate values.

    issued is YYMMDDHHMM in the application's local wall-clock convention.
    The original parser constructs 20 + issued + 01 (seconds = 01).
    """
    sid, major, region = _inputs(software_id, version, region)
    if type(days) is not int or not 1 <= days <= 9999:
        raise ValueError("days must be an integer in 1..9999")
    if not re.fullmatch(r"[0-9]{10}", issued):
        raise ValueError("issued must contain 10 digits: YYMMDDHHMM")
    try:
        issued_dt = datetime.strptime("20" + issued + "01", "%Y%m%d%H%M%S")
    except ValueError as exc:
        raise ValueError("issued contains an invalid calendar date") from exc
    if issued_dt.year > 2037:
        raise ValueError("the recovered native date parser supports years through 2037")
    day_field = f"{days:04d}"
    salt = decode_rotation(ENCODED_REGION_VALUES[region])
    first_input = sid + major
    first_hash = _md5(first_input)
    second_input = first_hash + salt + day_field + issued
    digest = _md5(second_input)
    return {
        "software_id": sid, "version": version, "major_version": major,
        "region": region, "days": days, "day_field": day_field,
        "issued_field": issued, "issued_local": issued_dt.isoformat(),
        "region_value": salt, "stage1_input": first_input,
        "stage1_md5": first_hash, "stage2_input": second_input,
        "stage2_md5": digest, "new_key": digest + day_field + issued,
    }


def inspect_key(key: str) -> dict:
    """Decode the non-JP layout; no authenticity or application acceptance claim."""
    if not re.fullmatch(r"[0-9a-f]{32}[0-9]{14}", key):
        raise ValueError("key must be 32 lowercase hex characters + 14 digits")
    return {"digest": key[:32], "day_field": key[32:36],
            "days": int(key[32:36]), "issued_field": key[36:46]}


def verify(key: str, software_id: str, version: str, region: str = "OT") -> bool:
    """Check digest and supported field domain, not the full UI registration policy."""
    try:
        fields = inspect_key(key)
        expected = generate(software_id, version, fields["days"],
                            fields["issued_field"], region)
    except ValueError:
        return False
    return key == expected["new_key"]
