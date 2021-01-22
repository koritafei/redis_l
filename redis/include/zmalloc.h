/**
 * @file zmalloc.h
 * @author koritafei (koritafei@gmail.com)
 * @brief 内存分配处理
 * @version 0.1
 * @date 2020-11-06
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef __ZMALLOC__H__
#define __ZMALLOC__H__

#if defined(__APPLE__)
#include <malloc/malloc.h>
#else
#include <malloc.h>
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "atomicvar.h"

#define PREFIX_SIZE (0)

void zmalloc_set_oom_handler(void (*oom_handler)(size_t));

void * zmalloc(size_t size);
void * zcalloc(size_t size);
void * zrealloc(void *ptr, size_t size);
void   zfree(void *ptr);
char * zstrdup(const char *str);
size_t zmalloc_used_memory(void);
size_t zmalloc_get_rss(void);
int    zmalloc_get_allocator_info(size_t *allocated, size_t *active,
                                  size_t *resident);
void   set_jemalloc_bg_thread(int enabled);
int    jemalloc_purge();
size_t zmalloc_get_private_dirty(long pid);
size_t zmalloc_get_smap_bytes_by_filed(char *filter, long pid);
size_t zmalloc_get_memory_size(void);
void   zlibc_free(void *ptr);

#endif  //!__ZMALLOC__H__
