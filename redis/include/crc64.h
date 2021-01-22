#ifndef __CRC64__H__
#define __CRC64__H__

#include <stdint.h>

void     crc64_init(void);
uint64_t crc64(uint64_t crc, const unsigned char *s, uint64_t l);

#endif  //!__CRC64__H__