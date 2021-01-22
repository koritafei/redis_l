#include "jemalloc.h"

#include "tsd_generic.h"

typedef enum {
  malloc_init_uninitialized  = 3,
  malloc_init_a0_initialized = 2,
  malloc_init_recursiable    = 1,
  malloc_init_initialized    = 0
} malloc_init_t;

static malloc_init_t malloc_init_state = malloc_init_uninitialized;

bool malloc_initialized() {
  return malloc_init_state == malloc_init_initialized;
}

static inline void *je_malloc(size_t size) {
  void *ptr = NULL;

  if (tsd_get_allocates() && unlikely(malloc_initialized())) {
    return malloc_default(size);
  }

  return ptr;
}

static inline void je_free(void *ptr) {
}