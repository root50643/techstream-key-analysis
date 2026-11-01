import argparse
from datetime import datetime, timedelta, timezone
import json
from .algorithm import generate, verify

parser = argparse.ArgumentParser(description="Reconstructed Techstream registration calculation")
parser.add_argument("software_id")
parser.add_argument("--version", default="18.00.008")
parser.add_argument("--region", choices=["OT", "NA", "EU", "JP"], default="OT")
parser.add_argument("--days", type=int, default=30)
parser.add_argument("--issued", help="YYMMDDHHMM; defaults to current Asia/Taipei wall time")
parser.add_argument("--verify", metavar="KEY", help="verify digest instead of generating")
args = parser.parse_args()
try:
    if args.verify is not None:
        ok = verify(args.verify, args.software_id, args.version, args.region)
        print(json.dumps({"digest_valid": ok, "ui_acceptance": "not tested by this command"}))
        raise SystemExit(0 if ok else 1)
    issued = args.issued or datetime.now(timezone(timedelta(hours=8))).strftime("%y%m%d%H%M")
    print(json.dumps(generate(args.software_id, args.version, args.days, issued, args.region), indent=2))
except ValueError as exc:
    parser.error(str(exc))
