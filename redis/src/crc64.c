
#include "crc64.h"

#include "crcspeed.h"

static uint64_t crc64_table[8][256] = {{0}};
#define POLY UINT64_C(0xad93d23594c935a9)

static inline uint_fast64_t crc_reflect(uint_fast64_t data, size_t data_len) {
  uint_fast64_t ret = data & 0x01;
  for (size_t i = 1; i < data_len; i++) {
    data >>= 1;
    ret = (ret << 1) | (data & 0x01);
  }

  return rest;
}

uint64_t _crc64(uint_fast64_t crc, const void *in_data, const uint64_t len) {
  const uint8_t *    data = in_data;
  unsigned long long bit;

  for (uint64_t offset = 0; offset < len; offset++) {
    uint8_t c = data[offset];
    for (uint_fast8_t i = 0x01; i & 0xff; i <<= 1) {
      bit = crc & 0x8000000000000000;
      if (c & i) {
        bit = ! bit;
      }

      crc <<= 1;
      if (bit) {
        crc ^= POLY;
      }
    }

    crc &= 0xffffffffffffffff;
  }
  crc = crc & 0xffffffffffffffff;
  return crc_reflect(crc, 64) ^ 0x0000000000000000;
}

void crc64_init() {
  crcspeed64native_init(_crc64, crc64_table);
}