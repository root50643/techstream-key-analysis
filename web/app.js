import { generateKey, localInputToIssued, toLocalInput, ParameterError } from "./algorithm.js";

const $ = id => document.getElementById(id);
const form = $("key-form");
const fields = { softwareId: $("software-id"), version: $("version"), region: $("region"), days: $("days"), issued: $("issued") };
let result = null;
let hasGenerated = false;
let copyTimer;

function updatePresets() {
  document.querySelectorAll("[data-days]").forEach(button => button.setAttribute("aria-pressed", String(button.dataset.days === fields.days.value)));
}

function clearErrors() {
  $("form-error").hidden = true;
  Object.values(fields).forEach(input => {
    input.removeAttribute("aria-invalid");
    $(`${input.id}-error`).hidden = true;
  });
}

function invalidate() {
  result = null;
  clearTimeout(copyTimer);
  $("copy-label").textContent = "複製金鑰";
  $("new-key").value = "";
  $("copy-key").disabled = true;
  $("download-json").disabled = true;
  $("result-content").hidden = true;
  $("result-empty").hidden = false;
  $("details-values").hidden = true;
  $("details-placeholder").hidden = false;
  $("result-card").dataset.state = hasGenerated ? "stale" : "idle";
  $("result-badge").textContent = hasGenerated ? "待重新產生" : "等待輸入";
  $("empty-title").textContent = hasGenerated ? "參數已更新。" : "準備好，就開始計算。";
  $("empty-description").textContent = hasGenerated ? "再次點選「產生 New Key」，取得對應的新金鑰。" : "填入左側參數，或載入實測範例。";
  $("result-status").textContent = hasGenerated ? "參數已變更，請重新產生金鑰。" : "調整任何參數後，請重新產生金鑰。";
  updatePresets();
}

function render(value) {
  result = value;
  hasGenerated = true;
  $("result-card").dataset.state = "ready";
  $("result-badge").textContent = "已產生 · 46 碼";
  $("result-empty").hidden = true;
  $("result-content").hidden = false;
  $("new-key").value = value.new_key;
  $("copy-key").disabled = false;
  $("download-json").disabled = false;
  $("result-region").textContent = value.region;
  $("result-version").textContent = value.major_version;
  $("result-days").textContent = `${value.days} 天`;
  $("result-issued").textContent = value.issued_field;
  $("details-placeholder").hidden = true;
  $("details-values").hidden = false;
  for (const [id, key] of [["stage1-input", "stage1_input"], ["stage1-hash", "stage1_md5"], ["region-value", "region_value"], ["stage2-input", "stage2_input"], ["stage2-hash", "stage2_md5"]]) $(id).textContent = value[key];
  $("result-status").textContent = "金鑰已在瀏覽器完成計算。可複製金鑰，或展開明細下載結果。";
}

form.addEventListener("submit", event => {
  event.preventDefault();
  clearErrors();
  try {
    const value = generateKey({
      softwareId: fields.softwareId.value, version: fields.version.value,
      region: fields.region.value, days: fields.days.value === "" ? NaN : Number(fields.days.value),
      issued: localInputToIssued(fields.issued.value),
    });
    fields.softwareId.value = value.software_id;
    render(value);
  } catch (error) {
    invalidate();
    $("form-error").textContent = error instanceof ParameterError ? error.message : "計算未完成，請重新檢查輸入參數。";
    $("form-error").hidden = false;
    if (error instanceof ParameterError && fields[error.field]) {
      const input = fields[error.field];
      input.setAttribute("aria-invalid", "true");
      $(`${input.id}-error`).textContent = error.message;
      $(`${input.id}-error`).hidden = false;
      input.focus();
    }
  }
});

form.addEventListener("input", () => { clearErrors(); invalidate(); });
form.addEventListener("change", () => { clearErrors(); invalidate(); });
fields.softwareId.addEventListener("input", () => { fields.softwareId.value = fields.softwareId.value.replace(/\s/g, "").toUpperCase(); });
document.querySelectorAll("[data-days]").forEach(button => button.addEventListener("click", () => { fields.days.value = button.dataset.days; clearErrors(); invalidate(); }));
$("use-now").addEventListener("click", () => { fields.issued.value = toLocalInput(); clearErrors(); invalidate(); });

$("load-example").addEventListener("click", () => {
  fields.softwareId.value = "6919BDAC3B1AF548BB2EA44E2D685305";
  fields.version.value = "18.00.008";
  fields.region.value = "OT";
  fields.days.value = "30";
  fields.issued.value = "2026-11-02T01:15";
  clearErrors();
  invalidate();
  form.requestSubmit();
});

$("copy-key").addEventListener("click", async () => {
  if (!result) return;
  const key = result.new_key;
  try {
    await navigator.clipboard.writeText(key);
    if (result?.new_key !== key) return;
    $("copy-label").textContent = "已複製";
    $("result-status").textContent = "46 碼金鑰已複製至剪貼簿。";
    clearTimeout(copyTimer);
    copyTimer = setTimeout(() => { $("copy-label").textContent = "複製金鑰"; }, 2500);
  } catch {
    if (result?.new_key !== key) return;
    $("new-key").focus();
    $("new-key").select();
    $("result-status").textContent = "無法自動複製，已選取金鑰，請手動複製。";
  }
});

$("download-json").addEventListener("click", () => {
  if (!result) return;
  const url = URL.createObjectURL(new Blob([JSON.stringify(result, null, 2) + "\n"], { type: "application/json;charset=utf-8" }));
  const link = document.createElement("a");
  link.href = url;
  link.download = `techstream-${result.region}-${result.issued_field}.json`;
  document.body.append(link);
  link.click();
  link.remove();
  setTimeout(() => URL.revokeObjectURL(url), 1000);
});

fields.issued.value = toLocalInput();
updatePresets();
