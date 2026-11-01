# JP registration key analysis

This extension adds the JP layout to the English browser calculator and the Python CLI. The v18 profile comes from the locally installed **Techstream 18.00.008** binaries. A separate v14 profile reproduces the previously identified public implementation.

## Supported profiles

| Profile | Region constant | Evidence |
| --- | --- | --- |
| JP, major version 18 | `SVciaorlleett1118` | Installed MainMenu constant, native decoder, native MD5 calls and decompiled inverse parser |
| JP, major version 14 | `wrNpTrgLvA2A` | Pinned public script, independently executed with Node's MD5 primitive |

The constants differ. Selecting JP with any other major version produces an explicit error. Other JP releases need their own evidence before a constant can be selected reliably.

The major version comes from the text before the first period. The browser and CLI accept a complete version such as `18.00.008` or `14.00.000`; the public v14 script itself supplies only `14`.

## Sources and local binary provenance

Public reference: [LashaMorgoshia/TechStream-Keygen, generateKey.js](https://github.com/LashaMorgoshia/TechStream-Keygen/blob/52f250f70e28a277eee1901ec6ee977f52ea38a1/generateKey.js), pinned to commit [52f250f](https://github.com/LashaMorgoshia/TechStream-Keygen/commit/52f250f70e28a277eee1901ec6ee977f52ea38a1). The original script's source SHA-256 and evaluated output are recorded in [jp-public-reference.json](../examples/jp-public-reference.json).

Local binary hashes are recorded in [binary-manifest.json](../evidence/static/binary-manifest.json). Ghidra was run again against the existing local MainMenu project for `00420d80`, `004218b0`, `004a9e40` and `00423330`. The four completed decompilations are listed in [decompilation-index.json](../evidence/static/JP/decompilation-index.json). The binary, disassembly-derived field indices and constant bytes are recorded in [JP/analysis.json](../evidence/static/JP/analysis.json), with a focused [assembly excerpt](../evidence/static/JP/jp-flow.asm.txt).

Relevant native functions:

| Location | Role |
| --- | --- |
| `MainMenu!004a9e40` | Supplies the encoded JP constant at `005144d4` |
| `MainMenu!00420d80` | Selects the JP inputs and concatenation order |
| `MainMenu!004218b0` | Extracts day, time and digest fields from the submitted JP key |
| `MainMenu!00423330` | Uses the same dispersed day-field positions for duration handling |
| `IT3Versatile!10001790` | Decodes the region constant, exported as `DecryptByRotatShiftVariable` |
| `tiswebapi!10001160` / `10010480` | Calculates MD5 and returns lowercase hexadecimal text |

Some MFC `CString::Mid` calls have incomplete parameter recovery in the pseudocode. The adjacent assembly supplies the explicit start and length arguments. `analyze_jp_static.py` extracts those arguments and derives the forward permutation independently of the calculator's implementation.

## Calculation

`MD5hex` returns 32 lowercase hexadecimal characters. `+` means ASCII text concatenation with no separator. All slice indices below are zero-based and their end position is exclusive.

```text
S = uppercase 32-character Software ID
V = major version text
D = four-digit day count
T = YYMMDDHHMM, in local wall-clock time
R = JP constant for the selected major version

H1 = MD5hex(D + "Japan" + S)
H2 = MD5hex(R + T + H1 + V)
P  = H2 + D + T
NewKey = permuteJP(P)
```

The second stage uses the hexadecimal **text** of H1. The public script also computes `MD5(swid + ver)` in a variable named `hash1`, but that value does not contribute to its JP output; its `hash_jp` is the H1 used above.

## v18 region constant

The encoded bytes at MainMenu VA `005144d4`, file offset `001144d4`, are:

```text
60 63 70 76 6e 31 34 79 79 72 72 36 36 3e 3e 3e 45
```

For each byte, subtract 13; if the result is below `0x30`, add 75. The result is `SVciaorlleett1118`. The installed x86 `IT3Versatile.dll` was called to verify this exact result. Its `RET 0x10` confirms the four-argument stdcall ABI used by the decoder probe.

## Final JP permutation

| Output positions | Source slice of P |
| --- | --- |
| 0–11 | `P[9:21]` |
| 12–13 | `P[42:44]` |
| 14 | `P[33:34]` |
| 15–16 | `P[38:40]` |
| 17 | `P[44:45]` |
| 18–19 | `P[36:38]` |
| 20–21 | `P[40:42]` |
| 22–23 | `P[34:36]` |
| 24–29 | `P[21:27]` |
| 30 | `P[45:46]` |
| 31 | `P[32:33]` |
| 32–40 | `P[0:9]` |
| 41–45 | `P[27:32]` |

Every source position occurs exactly once. The decompiled v18 parser recovers:

```text
D  = key[31:32] + key[14:15] + key[22:24]
T  = key[18:20] + key[15:17] + key[20:22]
   + key[12:14] + key[17:18] + key[30:31]
H2 = key[32:41] + key[0:12] + key[24:30] + key[41:46]
```

These independently recovered inverse slices produce the same forward permutation as the public v14 script. A JP key cannot be decoded by taking the first 32 characters as its digest and the final 14 characters as its numeric fields.

## Deterministic v18 example

```text
Software ID: 6919BDAC3B1AF548BB2EA44E2D685305
Version:     18.00.008
Region:      JP
Days:        0030
Time:        2611020115
H1:          63427e6830e36c26e9dbade20109e637
H2:          1b611dc48823fb0e9b7e9024a84b5722
New Key:     823fb0e9b7e9010111260230024a84501b611dc48b5722
```

The full intermediate values are in [jp-reference-vector.json](../examples/jp-reference-vector.json). The public v14 sample produces `3d04abad7c6e200114190400ec4010854d0de254937cd8` using its original Software ID, date and 5000-day field.

## Validation and limits

[native-jp-results.json](../evidence/runtime/native-jp-results.json) records 11 checks: one native constant decoding and ten two-stage digest/layout cases. Nine cases use the v18 profile; one reproduces the public v14 example. They cover multiple Software IDs, 1/30/365/5000/9999-day fields, a leap day, and the 2037 date boundary.

The first native MD5 call receives `D + "Japan"` and S. The second receives `R + T` and `H1 + V`. The final output is decoded using field slices independently extracted from MainMenu, and the recovered digest/day/time must match the native results and inputs.

The v14 case uses the installed **v18 MD5 primitive** to cross-check the arithmetic. It does not demonstrate acceptance by a v14 application. JP registration in the actual GUI has not been tested for either profile. The installed binaries and registration settings were left unchanged, and no vehicle was connected. The original OT GUI test remains documented separately in [the original report](report.zh-TW.md).

The 1–9999-day numeric range and a valid digest do not guarantee acceptance of every duration, existing-registration replacement, clock condition, or software release. The original date parser limits the entered year to 2037.

## Reproduce

From the repository root, with Node.js and Python available:

```powershell
node scripts/evaluate_jp_reference.mjs
python scripts/analyze_jp_static.py
& "$env:WINDIR\Microsoft.NET\Framework\v4.0.30319\csc.exe" /nologo /platform:x86 /out:local\NativeProbe.exe scripts\NativeProbe.cs
$env:PYTHONPATH = 'src'
python scripts/native_jp_validate.py --probe local/NativeProbe.exe --bin-directory 'C:\Program Files (x86)\Toyota Diagnostics\Techstream\bin'
python -m unittest discover -s tests -v
node --test tests/web.test.mjs
```

The public-script check downloads only the pinned source and runs it in a context exposing an MD5 adapter and a log collector. CI uses the committed result fixture and does not download or execute the third-party script.

To generate or verify a JP key:

```powershell
python -m techstream_keys 6919BDAC3B1AF548BB2EA44E2D685305 --region JP --version 18.00.008 --days 30 --issued 2611020115
python -m techstream_keys 6919BDAC3B1AF548BB2EA44E2D685305 --region JP --version 18.00.008 --verify 823fb0e9b7e9010111260230024a84501b611dc48b5722
```

Python callers should use `inspect_key(key, region="JP")` when decoding JP keys. The browser's JSON export includes the selected profile and the 46-character value before permutation.
