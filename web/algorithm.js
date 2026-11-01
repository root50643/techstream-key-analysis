import { md5 } from "./md5.js";

export const REGION_VALUES = Object.freeze({ OT: "SKE48", NA: "JxENR5GakyTw", EU: "MyPr1u5isS1ck85365" });

export class ParameterError extends Error {
  constructor(field, message) { super(message); this.name = "ParameterError"; this.field = field; }
}

function validateIssued(issued) {
  if (!/^\d{10}$/.test(issued)) throw new ParameterError("issued", "請提供完整的產生時間。");
  const year = 2000 + Number(issued.slice(0, 2));
  const month = Number(issued.slice(2, 4));
  const day = Number(issued.slice(4, 6));
  const hour = Number(issued.slice(6, 8));
  const minute = Number(issued.slice(8, 10));
  const date = new Date(Date.UTC(year, month - 1, day, hour, minute));
  if (date.getUTCFullYear() !== year || date.getUTCMonth() !== month - 1 || date.getUTCDate() !== day || date.getUTCHours() !== hour || date.getUTCMinutes() !== minute) {
    throw new ParameterError("issued", "日期或時間無效，請檢查月份、日期與時間。");
  }
  if (year > 2037) throw new ParameterError("issued", "原生日期解析器支援至 2037 年，請選擇 2000–2037 年。");
  return `${year}-${String(month).padStart(2, "0")}-${String(day).padStart(2, "0")}T${String(hour).padStart(2, "0")}:${String(minute).padStart(2, "0")}:01`;
}

export function localInputToIssued(value) {
  if (!/^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}$/.test(value)) throw new ParameterError("issued", "請輸入完整日期與時間（精確至分鐘）。");
  const year = Number(value.slice(0, 4));
  if (year < 2000 || year > 2037) throw new ParameterError("issued", "原生日期解析器支援至 2037 年，請選擇 2000–2037 年。");
  const issued = value.slice(2).replace(/[-T:]/g, "");
  validateIssued(issued);
  return issued;
}

export function toLocalInput(date = new Date()) {
  const pad = value => String(value).padStart(2, "0");
  return `${date.getFullYear()}-${pad(date.getMonth() + 1)}-${pad(date.getDate())}T${pad(date.getHours())}:${pad(date.getMinutes())}`;
}

export function generateKey({ softwareId, version, region, days, issued }) {
  softwareId = String(softwareId ?? "").trim().toUpperCase();
  version = String(version ?? "").trim();
  region = String(region ?? "").toUpperCase();
  if (!/^[0-9A-F]{32}$/.test(softwareId)) throw new ParameterError("softwareId", "Software ID 必須為 32 位十六進位字元（0–9、A–F）。");
  if (!/^\d+\.\d{2}\.\d{3}$/.test(version)) throw new ParameterError("version", "請使用完整版本格式，例如 18.00.008。");
  if (!Object.hasOwn(REGION_VALUES, region)) throw new ParameterError("region", "目前支援 OT、NA、EU；JP 使用不同的計算與排列。");
  if (!Number.isInteger(days) || days < 1 || days > 9999) throw new ParameterError("days", "有效天數必須為 1–9999 的整數。");
  const issuedLocal = validateIssued(issued);
  const majorVersion = version.split(".")[0];
  const dayField = String(days).padStart(4, "0");
  const regionValue = REGION_VALUES[region];
  const stage1Input = softwareId + majorVersion;
  const stage1 = md5(stage1Input);
  const stage2Input = stage1 + regionValue + dayField + issued;
  const stage2 = md5(stage2Input);
  return {
    software_id: softwareId, version, major_version: majorVersion, region, days,
    day_field: dayField, issued_field: issued, issued_local: issuedLocal,
    region_value: regionValue, stage1_input: stage1Input, stage1_md5: stage1,
    stage2_input: stage2Input, stage2_md5: stage2, new_key: stage2 + dayField + issued,
  };
}
