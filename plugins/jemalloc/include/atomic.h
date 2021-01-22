#ifndef __ATOMIC__H__
#define __ATOMIC__H__

#include <stdatomic.h>

#define ATOMIC_INIT(...) ATOMIC_VAR_INIT(__VA_ARGS__)

#define atomic_memory_order_t       memory_order
#define atomic_memory_order_relaxed memory_order_relaxed
#define atomic_memory_order_acquire memory_order_acquire
#define atomic_memory_order_release memory_order_release
#define atomic_memory_order_acq_rel memory_order_acq_rel
#define atomic_memory_order_seq_cst memory_order_seq_cst

#define atomic_fence atomic_thread_fence

#endif  //!__ATOMIC__H__