// RFC 1321 MD5, implemented locally; no browser API, dependency, or network call.
const shifts = [7, 12, 17, 22, 5, 9, 14, 20, 4, 11, 16, 23, 6, 10, 15, 21];
const constants = Uint32Array.from({ length: 64 }, (_, i) => Math.floor(Math.abs(Math.sin(i + 1)) * 2 ** 32));

export function md5(text) {
  const input = new TextEncoder().encode(text);
  const bytes = new Uint8Array(Math.ceil((input.length + 9) / 64) * 64);
  bytes.set(input);
  bytes[input.length] = 0x80;
  const view = new DataView(bytes.buffer);
  view.setUint32(bytes.length - 8, (input.length * 8) >>> 0, true);
  view.setUint32(bytes.length - 4, Math.floor(input.length / 0x20000000), true);
  const state = [0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476];
  for (let offset = 0; offset < bytes.length; offset += 64) {
    let [a, b, c, d] = state;
    for (let i = 0; i < 64; i++) {
      const round = i >>> 4;
      let f, g;
      if (round === 0) { f = (b & c) | (~b & d); g = i; }
      else if (round === 1) { f = (d & b) | (~d & c); g = (5 * i + 1) % 16; }
      else if (round === 2) { f = b ^ c ^ d; g = (3 * i + 5) % 16; }
      else { f = c ^ (b | ~d); g = (7 * i) % 16; }
      const sum = (a + f + constants[i] + view.getUint32(offset + g * 4, true)) | 0;
      const shift = shifts[round * 4 + i % 4];
      const next = (b + ((sum << shift) | (sum >>> (32 - shift)))) | 0;
      a = d; d = c; c = b; b = next;
    }
    state[0] = (state[0] + a) | 0;
    state[1] = (state[1] + b) | 0;
    state[2] = (state[2] + c) | 0;
    state[3] = (state[3] + d) | 0;
  }
  return state.map(word => [0, 8, 16, 24].map(shift => ((word >>> shift) & 255).toString(16).padStart(2, "0")).join("")).join("");
}
