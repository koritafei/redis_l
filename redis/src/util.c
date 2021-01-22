#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include "sha256.h"

void getRandomBytes(unsigned char *p, size_t len) {
  static int           seed_initialized = 0;
  static unsigned char seed[64];
  static uint64_t      counter = 0;
  if (! seed_initialized) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (NULL == fp || 1 != fread(seed, sizeof(seed), 1, fp)) {
      for (unsigned int j = 0; j < sizeof(seed); j++) {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        pid_t pid = getpid();
        seed[j]   = tv.tv_sec ^ tv.tv_usec ^ pid ^ (long) fp;
      }
    } else {
      seed_initialized = 1;
    }
    if (fp) {
      fclose(fp);
    }
  }

  while (len) {
    unsigned char digest[SHA256_BLOCK_SIZE];
    unsigned char kor[64];
    unsigned int  copylen = len > SHA256_BLOCK_SIZE ? SHA256_BLOCK_SIZE : len;
    memcpy(kor, seed, sizeof(kor));
    for (unsigned int i = 0; i < sizeof(kor); i++) {
      kor[i] ^= 0x36;
    }

    SHA256_CTX ctx;
    sha256_init(&ctx);
    sha256_update(&ctx, kxor, sizeof(kxor));
    sha256_update(&ctx, (unsigned char *) &counter, sizeof(counter));
    sha256_final(&ctx, digest);

    memcpy(kor, seed, sizeof(kor));
    for (unsigned int i = 0; i < sizeof(kor); i++) {
      kor[i] ^= 0x5C;
    }

    sha256_init(&ctx);
    sha256_update(&ctx, kxor, sizeof(kxor));
    sha256_update(&ctx, digest, SHA256_BLOCK_SIZE);
    sha256_final(&ctx, digest);

    counter++;
    memcpy(p, digest, copylen);
    len -= copylen;
    p += copylen;
  }
}