#ifndef __JEMALLOC__H__
#define __JEMALLOC__H__

#include <iostream>

static inline void *je_malloc(size_t);
static inline void  je_free(void *ptr);

bool  malloc_initialized();
void *malloc_default(size_t);

#endif  //!__JEMALLOC__H__