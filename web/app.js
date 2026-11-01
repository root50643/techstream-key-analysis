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
  $("copy-label").textContent = "Copy key";
  $("new-key").value = "";
  $("copy-key").disabled = true;
  $("download-json").disabled = true;
  $("result-content").hidden = true;
  $("result-empty").hidden = false;
  $("details-values").hidden = true;
  $("details-placeholder").hidden = false;
  $("result-card").dataset.state = hasGenerated ? "stale" : "idle";
  $("result-badge").textContent = hasGenerated ? "Regenerate" : "Awaiting input";
  $("empty-title").textContent = hasGenerated ? "Parameters updated." : "Ready when you are.";
  $("empty-description").textContent = hasGenerated ? "Select Generate New Key again to update your result." : "Enter your parameters or load the tested example.";
  $("result-status").textContent = hasGenerated ? "Parameters changed. Generate a new key." : "Generate a new key after changing any parameter.";
  updatePresets();
}

function render(value) {
  result = value;
  hasGenerated = true;
  $("result-card").dataset.state = "ready";
  $("result-badge").textContent = "Ready · 46 chars";
  $("result-empty").hidden = true;
  $("result-content").hidden = false;
  $("new-key").value = value.new_key;
  $("copy-key").disabled = false;
  $("download-json").disabled = false;
  $("result-region").textContent = value.region;
  $("result-version").textContent = value.major_version;
  $("result-days").textContent = `${value.days} ${value.days === 1 ? "day" : "days"}`;
  $("result-issued").textContent = value.issued_field;
  $("details-placeholder").hidden = true;
  $("details-values").hidden = false;
  for (const [id, key] of [["stage1-input", "stage1_input"], ["stage1-hash", "stage1_md5"], ["region-value", "region_value"], ["stage2-input", "stage2_input"], ["stage2-hash", "stage2_md5"]]) $(id).textContent = value[key];
  $("result-status").textContent = "Calculated in your browser. Copy the key or open the details to download the result.";
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
    $("form-error").textContent = error instanceof ParameterError ? error.message : "Calculation failed. Please check your parameters and try again.";
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
    $("copy-label").textContent = "Copied";
    $("result-status").textContent = "The 46-character key was copied to your clipboard.";
    clearTimeout(copyTimer);
    copyTimer = setTimeout(() => { $("copy-label").textContent = "Copy key"; }, 2500);
  } catch {
    if (result?.new_key !== key) return;
    $("new-key").focus();
    $("new-key").select();
    $("result-status").textContent = "Automatic copying is unavailable. The key is selected; please copy it manually.";
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
