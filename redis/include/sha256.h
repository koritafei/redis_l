#ifndef __SHA256__H__
#define __SHA256__H__

#include <stddef.h>
#include <stdint.h>

#define SHA256_BLOCK_SIZE 32

typedef uint8_t  BYTE;
typedef uint32_t WORD;

typedef struct {
  BYTE               data[64];
  WORD               datalen;
  unsigned long long bitlen;
  WORD               state[8];
} SHA256_CTX;

void sha256_init(SHA256_CTX *ctx);
void sha256_update(SHA256_CTX *ctx, const BYTE data[], size_t len);
void sha256_final(SHA256_CTX *ctx, BYTE hash[]);

#endif  //!__SHA256__H__