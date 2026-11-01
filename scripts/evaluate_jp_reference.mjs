// Re-evaluate the inspected, pinned public v14 implementation independently of
// our implementation. The VM exposes only an MD5 adapter and a log collector.
import { createHash } from "node:crypto";
import { writeFile } from "node:fs/promises";
import { runInNewContext } from "node:vm";

const url = "https://raw.githubusercontent.com/LashaMorgoshia/TechStream-Keygen/52f250f70e28a277eee1901ec6ee977f52ea38a1/generateKey.js";
const response = await fetch(url);
if (!response.ok) throw new Error(`Reference download failed: ${response.status}`);
const source = await response.text();
const logs = [];
const context = {
  require(name) {
    if (name !== "md5") throw new Error("The reference may only request MD5");
    return text => createHash("md5").update(text, "ascii").digest("hex");
  },
  console: { log: text => logs.push(text) },
};
runInNewContext(source, context, { timeout: 1000 });
if (logs.length !== 1 || logs[0] !== "JP: " + context.val_jp) throw new Error("Unexpected reference output");
const record = {
  source_url: url,
  source_commit: "52f250f70e28a277eee1901ec6ee977f52ea38a1",
  source_sha256: createHash("sha256").update(source).digest("hex"),
  software_id: context.swid, version: "14.00.000", major_version: context.ver,
  region: "JP", days: Number(context.days), day_field: context.days,
  issued_field: context.date, region_value: context.jp,
  stage1_input: context.days + "Japan" + context.swid, stage1_md5: context.hash_jp,
  stage2_input: context.jp + context.date + context.hash_jp + context.ver,
  stage2_md5: context.hash2_jp.slice(0, 32), unshuffled_key: context.hash2_jp,
  new_key: context.val_jp,
  scope: "Exact output of the pinned public v14 script; not a local v14 GUI test. Full version 14.00.000 supplies the same major version 14.",
};
const output = new URL("../examples/jp-public-reference.json", import.meta.url);
await writeFile(output, JSON.stringify(record, null, 2) + "\n");
console.log(JSON.stringify({ new_key: record.new_key, output: output.pathname }));
