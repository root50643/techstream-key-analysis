# Techstream 18 New Key 演算法分析

以本機 Techstream 18.00.008 的反編譯結果重建 Software ID → New Key 計算流程，附繁體中文報告、Python 實作、原生 DLL 比對及 GUI 實測證據。

**實測結果：**指定 ID 的 30 天金鑰已由本機 Techstream 接受；重新啟動後仍顯示有效期限。

- [完整分析報告](docs/report.zh-TW.md)
- [原始 OT PDF 報告](output/pdf/techstream-key-analysis.zh-TW.pdf)
- [JP 分支分析與驗證（英文）](docs/jp-analysis.md)
- [計算範例與實測金鑰](examples/reference-vector.json)
- [GUI 成功截圖](evidence/runtime/gui-success.jpg)
- [本機 DLL 測試結果](evidence/runtime/native-results.json)
- [網頁版 New Key 產生器](https://root50643.github.io/techstream-key-analysis/)

## 網頁版

[開啟 GitHub Pages 計算器](https://root50643.github.io/techstream-key-analysis/)。英文介面可調整 Software ID、版本、OT／NA／EU／JP 地區、天數及本機產生時間，支援複製金鑰、載入所選地區的測試範例、查看兩階段摘要及下載 JSON。JP 另顯示重排前資料與版本依據。修改參數後會清除舊結果，避免複製到不對應的金鑰。

JP 支援 **主要版本 18**（本機 18.00.008 反編譯與原生函式核對）及 **主要版本 14**（公開腳本輸出重現）。兩者固定常數不同，其他 JP 主要版本會明確回報不支援。[JP 報告](docs/jp-analysis.md)列出完整重排、來源、測試與限制。

網頁位於 `web/`，使用原生 HTML／CSS／JavaScript，無建置步驟、第三方套件或外部字型。MD5 在瀏覽器本機執行，不呼叫後端、不傳送輸入資料、不使用分析追蹤或瀏覽器儲存。時間欄位直接採用輸入的本機時間，沒有 UTC 轉換。

```powershell
python -m http.server 4173 --bind 127.0.0.1 --directory web
# 開啟 http://127.0.0.1:4173
node --test tests/web.test.mjs
```

GitHub Pages 使用 `.github/workflows/pages.yml` 自動部署 `web/`；部署前會比對 Python 參考結果、9 組原有地區向量、10 組 JP 摘要／重排向量及公開 v14 腳本輸出。首次設定需在儲存庫 Pages 設定選擇 **GitHub Actions** 作為來源。

## 快速使用

Python 3.10 以上，計算器無第三方相依套件。從此資料夾執行：

```powershell
$env:PYTHONPATH = 'src'
python -m techstream_keys 6919BDAC3B1AF548BB2EA44E2D685305 --version 18.00.008 --region OT --days 30 --issued 2611020115
python -m techstream_keys 6919BDAC3B1AF548BB2EA44E2D685305 --version 18.00.008 --region JP --days 30 --issued 2611020115
python -m unittest discover -s tests -v
```

省略 `--issued` 時使用目前台北時間，格式為 `YYMMDDHHMM`。CLI 的 `--verify KEY` 驗證格式與雜湊；實際註冊仍包含應用程式的時間、既有狀態及覆寫判斷。

```text
techstream-key-analysis/
├── .github/workflows/       Python／JavaScript CI、GitHub Pages 部署
├── docs/                   原始繁體中文報告、英文 JP 報告、重跑說明
├── evidence/static/        函式位址、反編譯 C、組合語言、SHA-256
├── evidence/runtime/       原生測試 JSON、測試輸出、GUI 截圖與文字
├── examples/               本次 ID 的確定性計算向量
├── output/pdf/             可閱讀的 PDF 報告
├── scripts/                Ghidra 匯出、x86 原生比對、PDF 建置
├── src/techstream_keys/     無第三方相依的 Python 計算器
├── tests/                  固定向量、輸入邊界及竄改測試
├── web/                    純前端 New Key 產生器
└── local/                  本機樣本、工具專案、備份；Git 忽略
```

## 重跑分析

[重跑說明](docs/reproduction.md)列出 Ghidra、Java、Windows x86 DLL 測試及 PDF 建置命令。原廠程式、安裝包、JDK、Ghidra 資料庫與個人設定備份留在 `local/` 或既有工作區，不納入此 Git 倉庫。

GUI 完整測試範圍為 **18.00.008 / OT / 指定 Software ID**。NA、EU 已比對本機 DLL 雜湊。JP v18 已完成原生常數解碼、兩階段摘要與反編譯解析器欄位核對；JP v14 已重現公開腳本結果。JP 尚未進行註冊畫面的接受測試，原廠程式與既有註冊設定未因這次 JP 分析而修改。
