# 重跑分析與驗證

以下命令從此專案根目錄執行。使用者自行提供相同的本機二進位；SHA-256 以 `evidence/static/binary-manifest.json` 為準。

## Python

```powershell
$env:PYTHONPATH = 'src'
python -m techstream_keys 6919BDAC3B1AF548BB2EA44E2D685305 --version 18.00.008 --region OT --days 30 --issued 2611020115
python -m techstream_keys 6919BDAC3B1AF548BB2EA44E2D685305 --version 18.00.008 --region JP --days 30 --issued 2611020115
python -m unittest discover -s tests -v
```

計算器及測試不需要 pip 安裝套件。也可以用 `python -m pip install -e .` 安裝後從任何位置執行模組。

## Ghidra

需要本機 Ghidra 與相容 JDK；本次使用 12.1.4 和 JDK 21。請把下列工具路徑換成本機位置。

```powershell
.\scripts\decompile.ps1 -GhidraHome C:\tools\ghidra_12.1.4_PUBLIC -JavaHome C:\tools\jdk-21 -BinaryDirectory 'C:\Program Files (x86)\Toyota Diagnostics\Techstream\bin'
```

腳本先複製三個分析目標至 `local/samples`，再以 PE loader 分析，執行 `ExportKeyEvidence.java` 匯出選定函式的偽 C 與組合語言。結果位於 `local/reproduced`。腳本使用絕對專案路徑，避免 Ghidra 將 `.` 解讀成不合法的專案名稱；也避免把含 `(x86)` 的安裝路徑直接傳入批次檔。

若已經有 Ghidra 的 `offline` 專案，可使用 `export-existing.ps1` 進行無重新分析的定點匯出。它不重新判斷函式邊界；請以本次固定二進位與位址重跑。

## Windows 原生 DLL 比對

需要 Windows 的 32-bit .NET Framework C# compiler，以及已安裝的 x86 `tiswebapi.dll`。以獨立 x86 process 呼叫 DLL，避免從 x64 Python 直接載入 x86 DLL。

```powershell
.\scripts\native-validate.ps1 -Python python -BinaryDirectory 'C:\Program Files (x86)\Toyota Diagnostics\Techstream\bin'
```

此命令重新編譯 probe，執行 18 組比對，並重寫原生測試結果及固定範例。測試只呼叫已反編譯確認的摘要函式，沒有連車或修改註冊設定檔。

JP 的獨立重跑流程見 [JP 分支補充分析](jp-analysis.md#reproduce)。它另外產生 `evidence/static/JP/analysis.json`、`evidence/runtime/native-jp-results.json` 與 JP 範例，不會覆寫原始 OT GUI 證據。`native_jp_validate.py` 的 11 項檢查包含 1 項原生常數解碼與 10 項摘要／靜態解析器欄位核對；JP GUI 接受測試尚未執行。

## GUI 驗證

本次的 UI 操作由 computer-use 執行，機器結果和截圖保存於 `evidence/runtime/`。重跑時，先記錄 Current Key 與地區、備份 `Env/IT3UserCustom.ini`，再輸入 New Key 並按 OK，檢查期限顯示與 Current Key，最後重新啟動確認。

原生摘要比對不能取代 GUI 的既有授權、日期及覆寫條件；重跑相同 key 也不保證觸發與首次註冊相同的分支。若重新產生，請使用目前本機壁鐘時間，而不是將 Unix timestamp 填入最後 10 碼。

本次成功實測後保留 30 天註冊。`local/backup/IT3UserCustom.ini` 是本機測試前的設定備份，不隨 Git 發布；如需回復，應先完全關閉程式，再由使用者以該備份還原。

## PDF

需要 reportlab、pypdf 及可嵌入的繁體中文字型。報告建置命令：

```powershell
python .\scripts\build_report.py --font C:\fonts\TC.ttf --bold-font C:\fonts\TCBold.ttf
pdftoppm -scale-to 1400 -png .\output\pdf\techstream-key-analysis.zh-TW.pdf .\tmp\pdf-review
```

PDF 從 `docs/report.zh-TW.md` 建置；輸出後須逐頁確認圖表、字型、頁碼與換頁。字型不打包至此倉庫。GitHub Actions 只執行無外部相依的 Python 測試，原生與 GUI 測試需要 Windows 安裝環境。

## 交付檔案完整性

```powershell
python scripts/verify_evidence.py
```

有意修改程式、報告或重跑實測後，使用 `python scripts/pin_artifacts.py` 重新產生雜湊。此命令將文字換行統一成 LF，確保 GitHub 在不同平台檢出後仍能核對；不會納入 Git、local、tmp、建置產物或 Python 快取。
