import test from "node:test";
import assert from "node:assert/strict";
import { createHash } from "node:crypto";
import { readFileSync } from "node:fs";
import { md5 } from "../web/md5.js";
import { generateKey, inspectKey, JP_SLICES, localInputToIssued, toLocalInput, ParameterError } from "../web/algorithm.js";

const readJson = path => JSON.parse(readFileSync(new URL(path, import.meta.url), "utf8"));
const reference = readJson("../examples/reference-vector.json");
const native = readJson("../evidence/runtime/native-results.json");
const base = { softwareId: reference.software_id, version: reference.version, region: "OT", days: 30, issued: reference.issued_field };

test("local MD5 matches RFC 1321 vectors and independent Node crypto at block boundaries", () => {
  for (const text of ["", "a", "abc", "message digest", "abcdefghijklmnopqrstuvwxyz", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789", "1234567890".repeat(8), "a".repeat(55), "a".repeat(56), "a".repeat(63), "a".repeat(64), "a".repeat(65), "a".repeat(128), "a".repeat(10000), "瀏覽器本機計算"]) {
    assert.equal(md5(text), createHash("md5").update(text).digest("hex"));
  }
});

test("browser result matches every field of the Python/GUI reference vector", () => {
  assert.deepEqual(generateKey(base), reference);
});

test("all 9 recorded OT/NA/EU native two-stage digest vectors match", () => {
  const vectors = native.results.filter(row => row.test === "native_two_stage_digest");
  assert.equal(vectors.length, 9);
  for (const vector of vectors) {
    const value = generateKey({ ...base, region: vector.region, days: vector.days });
    assert.equal(value.stage1_md5, vector.stage1);
    assert.equal(value.stage2_md5, vector.stage2);
    assert.equal(value.new_key, vector.new_key);
    assert.equal(value.new_key.length, 46);
  }
});

test("every adjustable parameter affects the expected part of the result", () => {
  const key = generateKey(base).new_key;
  for (const change of [{ softwareId: "0".repeat(32) }, { version: "19.00.008" }, { region: "NA" }, { region: "EU" }, { days: 31 }, { issued: "2611020116" }]) {
    assert.notEqual(generateKey({ ...base, ...change }).new_key, key);
  }
  assert.equal(generateKey({ ...base, version: "18.99.999" }).new_key, key);
  assert.equal(generateKey({ ...base, softwareId: base.softwareId.toLowerCase() }).new_key, key);
});

test("invalid IDs, unsupported regions, version formats and day values are rejected", () => {
  for (const [field, values] of Object.entries({ softwareId: ["", "0".repeat(31), "G".repeat(32)], version: ["18", "18.0.008", "18.00.8"], region: ["XX", "toString"], days: [0, -1, 10000, 1.5, NaN, Infinity, "30"] })) {
    for (const value of values) assert.throws(() => generateKey({ ...base, [field]: value }), error => error instanceof ParameterError && error.field === field);
  }
});

test("JP permutation matches every index independently recovered from MainMenu", () => {
  const analysis = readJson("../evidence/static/JP/analysis.json");
  const indices = JP_SLICES.flatMap(([start, end]) => Array.from({ length: end - start }, (_, i) => start + i));
  assert.deepEqual(indices, analysis.permutation_indices);
  assert.deepEqual([...indices].sort((a, b) => a - b), Array.from({ length: 46 }, (_, i) => i));
});

test("all 10 JP vectors match Python, installed DLL digests and native-parser field extraction", () => {
  const jp = readJson("../evidence/runtime/native-jp-results.json");
  assert.equal(jp.results.length, 10);
  for (const { value, native_stage1, native_stage2, parser_recovered } of jp.results) {
    const generated = generateKey({ softwareId: value.software_id, version: value.version, region: "JP", days: value.days, issued: value.issued_field });
    assert.deepEqual(generated, value);
    assert.equal(generated.stage1_md5, native_stage1);
    assert.equal(generated.stage2_md5, native_stage2);
    const decoded = inspectKey(generated.new_key, "JP");
    for (const field of ["digest", "day_field", "issued_field"]) assert.equal(decoded[field], parser_recovered[field]);
  }
});

test("JP v14 reproduces the original public script and v18 uses its own native constant", () => {
  const original = readJson("../examples/jp-public-reference.json");
  const options = { softwareId: original.software_id, version: original.version, region: "JP", days: original.days, issued: original.issued_field };
  const v14 = generateKey(options);
  for (const field of ["new_key", "unshuffled_key", "stage1_input", "stage2_input", "stage1_md5", "stage2_md5", "region_value"]) assert.equal(v14[field], original[field]);
  const v18 = generateKey({ ...options, version: "18.00.008" });
  assert.equal(v14.region_value, "wrNpTrgLvA2A");
  assert.equal(v18.region_value, "SVciaorlleett1118");
  assert.equal(v14.stage1_md5, v18.stage1_md5);
  assert.notEqual(v14.new_key, v18.new_key);
  assert.throws(() => generateKey({ ...options, version: "19.00.000" }), error => error instanceof ParameterError && error.field === "version");
});

test("calendar validation checks leap years, invalid days, time and 2037 bound", () => {
  for (const issued of ["2602290115", "2613310115", "2611320115", "2611022415", "2611020160", "3801010000", "bad"]) assert.throws(() => generateKey({ ...base, issued }), ParameterError);
  assert.equal(generateKey({ ...base, issued: "2402292359" }).issued_local, "2024-02-29T23:59:01");
  assert.equal(generateKey({ ...base, issued: "3712312359" }).issued_local, "2037-12-31T23:59:01");
});

test("datetime-local conversion preserves entered wall time without timezone conversion", () => {
  assert.equal(localInputToIssued("2026-11-02T01:15"), reference.issued_field);
  assert.equal(localInputToIssued("2000-01-01T00:00"), "0001010000");
  for (const value of ["1999-12-31T23:59", "2038-01-01T00:00", "2026-02-29T01:00", "2026-11-02T01:15:00", ""]) assert.throws(() => localInputToIssued(value), ParameterError);
  assert.equal(toLocalInput(new Date(2026, 10, 2, 1, 15, 59)), "2026-11-02T01:15");
});
