# 證據閱讀方式

`static/binary-manifest.json` 綁定本次安裝程式的 SHA-256。`static/` 的 `.c` 是 Ghidra 偽 C，不是取得的原始碼；`.asm.txt` 是對應組合語言。`MainMenu/date-flow.asm.txt` 只節錄與欄位／時間判讀相關的兩個位址區間。

`runtime/native-results.json` 為 18 組本機 x86 DLL 比對；`unit-tests.txt` 為 6 組 Python 測試。`gui-results.json` 為人工操作步驟經工具執行後整理的結果，請同時檢查下列原始畫面與可存取性文字。

JP 擴充另收錄於 `static/JP/` 與 `runtime/native-jp-results.json`：前者包含重新匯出的 Ghidra 函式索引、反編譯組合語言節錄，以及從本機 PE／解析器獨立抽出的常數與重排；後者記錄 11 項原生解碼／摘要與靜態欄位核對。`examples/jp-public-reference.json` 固定公開 v14 腳本的來源提交、SHA-256 與實際輸出。原始 6 項測試輸出為初版記錄，目前測試命令另涵蓋 JP。JP 沒有註冊畫面接受測試，請勿將 DLL 計算一致解讀為 GUI 已接受。

| 檔案 | 內容 |
| --- | --- |
| user-reference.png | 使用者提供的原始圖片，非本次新截圖 |
| gui-baseline.txt | 本次本機起始註冊畫面文字 |
| gui-invalid-0.jpg、gui-invalid-1.jpg、gui-invalid.txt | 輸入 46 個 0 的畫面；這些是提交前的輸入狀態 |
| gui-invalid-result.jpg、gui-invalid-result.txt | 實際按 OK 後，New Key 清空而 Current Key 仍空白 |
| gui-valid-input.jpg、gui-valid-input.txt | 計算出的金鑰填入 New Key |
| gui-success.jpg、gui-success.txt | 提交後主畫面的 30 天期限 |
| gui-current-key.jpg、gui-current-key.txt | 重新開啟註冊資訊所見的 Current Key |
| gui-restarted-0.jpg、gui-restarted.txt | 新行程啟動後的剩餘期限 |

此舊式 MFC 對話框的可存取性樹會把可輸入的 New Key 標成 Current Key；靜態顯示的 Current Key 也可能掛在 New Key 的文字標籤下。故以實際截圖的欄位位置，配合完整字串、設定檔及期限顯示判定結果，不只依賴可存取性標籤。

`artifact-sha256.json` 綁定交付的報告、程式碼、測試與證據。修改後請重新產生；未修改的交付版本可用 `python scripts/verify_evidence.py` 檢查。
