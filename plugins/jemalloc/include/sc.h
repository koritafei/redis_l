#ifndef __SC__H__
#define __SC__H__

#include "jemalloc_macro.h"
#include "quantum.h"

#define SC_LG_TINY_MIN 3
#define SC_LG_NGROUP   2

#define SC_NGROUP                (1ULL << SC_LG_NGROUP)
#define SC_NPSEUDO               SC_NGROUP
#define SC_NTINY                 (LG_QUANTUM - SC_LG_TINY_MIN)
#define SC_LG_FIRST_REGULAR_BASE (LG_QUANTUM + SC_LG_NGROUP)

#define SC_NBINS                                                               \
  (SC_NTINY + SC_NPSEUDO +                                                     \
   SC_NGROUP * (LG_PAGE + SC_LG_NGROUP - SC_LG_FIRST_REGULAR_BASE) - 1)

#endif  //!__SC__H__