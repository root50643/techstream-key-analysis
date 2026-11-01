import { md5 } from "./md5.js";

export const REGION_VALUES = Object.freeze({ OT: "SKE48", NA: "JxENR5GakyTw", EU: "MyPr1u5isS1ck85365", JP: "SVciaorlleett1118" });
export const JP_SLICES = Object.freeze([[9, 21], [42, 44], [33, 34], [38, 40], [44, 45], [36, 38], [40, 42], [34, 36], [21, 27], [45, 46], [32, 33], [0, 9], [27, 32]].map(range => Object.freeze(range)));
const JP_PUBLIC_V14_VALUE = "wrNpTrgLvA2A";

export class ParameterError extends Error {
  constructor(field, message) { super(message); this.name = "ParameterError"; this.field = field; }
}

function validateIssued(issued) {
  if (!/^\d{10}$/.test(issued)) throw new ParameterError("issued", "Enter a complete generation date and time.");
  const year = 2000 + Number(issued.slice(0, 2));
  const month = Number(issued.slice(2, 4));
  const day = Number(issued.slice(4, 6));
  const hour = Number(issued.slice(6, 8));
  const minute = Number(issued.slice(8, 10));
  const date = new Date(Date.UTC(year, month - 1, day, hour, minute));
  if (date.getUTCFullYear() !== year || date.getUTCMonth() !== month - 1 || date.getUTCDate() !== day || date.getUTCHours() !== hour || date.getUTCMinutes() !== minute) {
    throw new ParameterError("issued", "Invalid date or time. Check the month, day, hour and minute.");
  }
  if (year > 2037) throw new ParameterError("issued", "Choose a year between 2000 and 2037.");
  return `${year}-${String(month).padStart(2, "0")}-${String(day).padStart(2, "0")}T${String(hour).padStart(2, "0")}:${String(minute).padStart(2, "0")}:01`;
}

export function localInputToIssued(value) {
  if (!/^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}$/.test(value)) throw new ParameterError("issued", "Enter a complete date and time, to the minute.");
  const year = Number(value.slice(0, 4));
  if (year < 2000 || year > 2037) throw new ParameterError("issued", "Choose a year between 2000 and 2037.");
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
  if (!/^[0-9A-F]{32}$/.test(softwareId)) throw new ParameterError("softwareId", "Software ID must be exactly 32 hexadecimal characters (0-9, A-F).");
  if (!/^\d+\.\d{2}\.\d{3}$/.test(version)) throw new ParameterError("version", "Enter a full version number, such as 18.00.008.");
  if (!Object.hasOwn(REGION_VALUES, region)) throw new ParameterError("region", "Supported regions are OT, NA, EU and JP.");
  const majorVersion = version.split(".")[0];
  if (region === "JP" && !["14", "18"].includes(majorVersion)) throw new ParameterError("version", "JP supports major versions 14 (public source) and 18 (local analysis).");
  if (!Number.isInteger(days) || days < 1 || days > 9999) throw new ParameterError("days", "Validity must be a whole number from 1 to 9999 days.");
  const issuedLocal = validateIssued(issued);
  const dayField = String(days).padStart(4, "0");
  const regionValue = region === "JP" && majorVersion === "14" ? JP_PUBLIC_V14_VALUE : REGION_VALUES[region];
  const stage1Input = region === "JP" ? dayField + "Japan" + softwareId : softwareId + majorVersion;
  const stage1 = md5(stage1Input);
  const stage2Input = region === "JP" ? regionValue + issued + stage1 + majorVersion : stage1 + regionValue + dayField + issued;
  const stage2 = md5(stage2Input);
  const canonical = stage2 + dayField + issued;
  const result = {
    software_id: softwareId, version, major_version: majorVersion, region, days,
    day_field: dayField, issued_field: issued, issued_local: issuedLocal,
    region_value: regionValue, stage1_input: stage1Input, stage1_md5: stage1,
    stage2_input: stage2Input, stage2_md5: stage2, new_key: canonical,
  };
  if (region === "JP") Object.assign(result, {
    layout: "JP-permuted", unshuffled_key: canonical,
    profile: majorVersion === "18" ? "JP18-native" : "JP14-public-source",
    new_key: JP_SLICES.map(([start, end]) => canonical.slice(start, end)).join(""),
  });
  return result;
}

export function inspectKey(key, region = "OT") {
  region = String(region).toUpperCase();
  if (!Object.hasOwn(REGION_VALUES, region)) throw new ParameterError("region", "Unsupported region.");
  if (typeof key !== "string" || key.length !== 46) throw new ParameterError("key", "The key must contain 46 characters.");
  if (region === "JP") {
    const canonical = Array(46);
    let cursor = 0;
    for (const [start, end] of JP_SLICES) for (let index = start; index < end; index++) canonical[index] = key[cursor++];
    key = canonical.join("");
  }
  if (!/^[0-9a-f]{32}[0-9]{14}$/.test(key)) throw new ParameterError("key", "The key fields have an invalid format.");
  return { digest: key.slice(0, 32), day_field: key.slice(32, 36), days: Number(key.slice(32, 36)), issued_field: key.slice(36) };
}
