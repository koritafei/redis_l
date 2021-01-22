#ifndef __CRCSPREED__H__
#define __CRCSPREED__H__

#include <inttypes.h>
#include <stdio.h>

typedef uint64_t (*crcfn64)(uint64_t, const void *, const uint64_t);
typedef uint16_t (*crcfn16)(uint16_t, const void *, const uint16_t);

// CRC-64
void crcspreed64native_init(crcfn64 fn, uint64_t table[8][256]);
void crcspeed64little_init(crcfn64 fn, uint64_t table[8][256]);
void crcspeed64big_init(crcfn64 fn, uint64_t table[8][256]);

#endif  //!__CRCSPREED__H__