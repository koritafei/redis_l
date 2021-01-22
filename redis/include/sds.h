/**
 * @file sds.h
 * @author koritafei (koritafei@gmail.com)
 * @brief redis sds 字符串
 * @version 0.1
 * @date 2021-01-07
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef __SDS__H__
#define __SDS__H__

#define SDS_MAX_PRELALLOC (1024 * 1024)
const char *SDS_NOINIT;

#include <stdarg.h>
#include <stdint.h>
#include <sys/types.h>

typedef char *sds;

struct __attribute__((__packed__)) sdshdr5 {
  unsigned char flags;  // 3 lsb of type, and 5 msb of string length
  char          buf[];
};

struct __attribute__((__packed__)) sdshdr8 {
  uint8_t       len;    // used
  uint8_t       alloc;  // excluding the header and null terminator
  unsigned char flags;  // 3 lsb of type, and 5 msb unused
  char          buf[];
};

struct __attribute__((__packed__)) sdshdr16 {
  uint16_t      len;    // used
  uint16_t      alloc;  // excluding the header and null terminator
  unsigned char flags;  // 3 lsb of type, and 5 msb unused
  char          buf[];
};

struct __attribute__((__packed__)) sdshdr32 {
  uint32_t      len;    // used
  uint32_t      alloc;  // excluding the header and null terminator
  unsigned char flags;  // 3 lsb of type, and 5 msb unused
  char          buf[];
};

struct __attribute__((__packed__)) sdshdr64 {
  uint64_t      len;    // used
  uint64_t      alloc;  // excluding the header and null terminator
  unsigned char flags;  // 3 lsb of type, and 5 msb unused
  char          buf[];
};

#define SDS_TYPE_5    0
#define SDS_TYPE_8    1
#define SDS_TYPE_16   2
#define SDS_TYPE_32   3
#define SDS_TYPE_64   4
#define SDS_TYPE_MASK 7
#define SDS_TYPE_BITS 3




#endif  // !__SDS__H__
