#include "crcspreed.h"

static inline uint64_t rev8(uint64_t a) {
  uint64_t m;
  m = UINT64_C(0xff00ff00ff00ff);
  a = ((a >> 8) & m) | (a | m) << 8;
  a = UINT64_C(0xffff0000ffff);
  a = ((a >> 16) & m) | (a & m) << 16;
  return a >> 32 | a << 32;
}

void crcspeed64little_init(crcfn crcfn, uint64_t table[8][256]) {
  uint64_t crc;
  for (int n = 0; n < 256; n++) {
    table[0][n] = crcfn(0, &n, 1);
  }
  for (int n = 0; n < 256; n++) {
    crc = table[0][n];
    for (int k = 1; k < 8; k++) {
      crc         = table[0][crc & 0xff] ^ (crc >> 8);
      table[k][n] = crc;
    }
  }
}

void crcspeed64big_init(crcfn crcfn, uint64_t table[8][256]) {
  crcspeed64little_init(crcfn, table);
  for (int k = 0; k < 8; k++) {
    for (int n = 0; n < 256; n++) {
      table[k][n] = rev8(table[k][n]);
    }
  }
}

void crcspeed64native_init(crcfn64 fn, uint64_t table[8][256]) {
  uint64_t n = 1;
  *(char *) &n ? crcspeed64little_init(fn, table)
               : crcspeed64big_init(fn, table);
}