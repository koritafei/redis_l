#ifndef __TCACHE_STRUCTS__H__
#define __TCACHE_STRUCTS__H__

#include "tcache_types.h"

#define TCACHE_NBINS_MAX                                                       \
  (SC_NBINS + SC_NGROUP * (TCACHE_LG_MAXCLASS_LIMIT - SC_LG_LARGE_MINCLASS) + 1)

struct tcache_s {
  tcache_slow_t *tcache_slow;
  cache_bin_t    bins[TCACHE_NBINS_MAX];
};

#endif  //!__TCACHE_STRUCTS__H__