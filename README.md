# Techstream 18 New Key 演算法分析

以本機 Techstream 18.00.008 的反編譯結果重建 Software ID → New Key 計算流程，附繁體中文報告、Python 實作、原生 DLL 比對及 GUI 實測證據。

**實測結果：**指定 ID 的 30 天金鑰已由本機 Techstream 接受；重新啟動後仍顯示有效期限。

- [完整分析報告](docs/report.zh-TW.md)
- [PDF 報告](output/pdf/techstream-key-analysis.zh-TW.pdf)
- [計算範例與實測金鑰](examples/reference-vector.json)
- [GUI 成功截圖](evidence/runtime/gui-success.jpg)
- [本機 DLL 測試結果](evidence/runtime/native-results.json)

## 快速使用

Python 3.10 以上，計算器無第三方相依套件。從此資料夾執行：

```powershell
$env:PYTHONPATH = 'src'
python -m techstream_keys 6919BDAC3B1AF548BB2EA44E2D685305 --version 18.00.008 --region OT --days 30 --issued 2611020115
python -m unittest discover -s tests -v
```

省略 `--issued` 時使用目前台北時間，格式為 `YYMMDDHHMM`。CLI 的 `--verify KEY` 驗證格式與雜湊；實際註冊仍包含應用程式的時間、既有狀態及覆寫判斷。

```text
techstream-key-analysis/
├── .github/workflows/       Python CI
├── docs/                   繁體中文分析報告、重跑說明
├── evidence/static/        函式位址、反編譯 C、組合語言、SHA-256
├── evidence/runtime/       原生測試 JSON、測試輸出、GUI 截圖與文字
├── examples/               本次 ID 的確定性計算向量
├── output/pdf/             可閱讀的 PDF 報告
├── scripts/                Ghidra 匯出、x86 原生比對、PDF 建置
├── src/techstream_keys/     無第三方相依的 Python 計算器
├── tests/                  固定向量、輸入邊界及竄改測試
└── local/                  本機樣本、工具專案、備份；Git 忽略
```

## 重跑分析

[重跑說明](docs/reproduction.md)列出 Ghidra、Java、Windows x86 DLL 測試及 PDF 建置命令。原廠程式、安裝包、JDK、Ghidra 資料庫與個人設定備份留在 `local/` 或既有工作區，不納入此 Git 倉庫。

本次 GUI 完整測試範圍為 **18.00.008 / OT / 指定 Software ID**。NA、EU 已比對本機 DLL 雜湊，未切換應用程式地區實測；JP 的欄位排列不同，CLI 不提供 JP。
