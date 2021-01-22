#ifndef __ATOMICVAR__H__
#define __ATOMICVAR__H__

#include <pthread.h>

#define atomicIncr(var, count)                                                 \
  __atomic_add_fetch(&var, (count), __ATOMIC_RELAXED)

#define atomicDecr(var, count)                                                 \
  __atomic_sub_fetch(&var, (count), __ATOMIC_RELAXED)

#define atomicGet(var, count)                                                  \
  do {                                                                         \
    __atomic_load_n(&var, __ATOMIC_RELAXED);                                   \
  } while (0)

#endif  //!__ATOMICVAR__H__
