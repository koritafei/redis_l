/**
 * @file macro_test.c
 * @author koritafei (koritafei@gmail.com)
 * @brief 宏定义测试
 * @version 0.1
 * @date 2020-11-10
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define JEMALLOC_GENRTE_ATOMICS(type, short_type, lg_size)                     \
  static inline type atomic_load_##short_type() {                              \
    printf("%d %s\n", __LINE__, __func__);                                     \
  }

#define JEMALLOC_INT_GENRTE_ATOMICS_ATOMICS(type, short_type, lg_size)         \
  JEMALLOC_GENRTE_ATOMICS(type, short_type, lg_size)                           \
  static inline type atomic_fetch_add_##short_type() {                         \
    printf("%d %s\n", __LINE__, __func__);                                     \
  }

JEMALLOC_INT_GENRTE_ATOMICS_ATOMICS(size_t, zu, 0)
JEMALLOC_INT_GENRTE_ATOMICS_ATOMICS(unsigned, u, 0)

#define TSD_MANGLE(n) cant_access_tsd_items_directly_use_a_getter_or_setter_##n

/*  O(name,			type,			nullable type */
#define TSD_DATA_FAST                                                          \
  O(thread_allocated, uint64_t, uint64_t)                                      \
  O(thread_allocated_next_event_fast, uint64_t, uint64_t)                      \
  O(thread_deallocated, uint64_t, uint64_t)                                    \
  O(thread_deallocated_next_event_fast, uint64_t, uint64_t)                    \
  O(tcache, tcache_t, tcache_t)

#define TSD_DATA_SLOW                                                          \
  O(tcache_enabled, bool, bool)                                                \
  O(arenas_tdata_bypass, bool, bool)                                           \
  O(reentrancy_level, int8_t, int8_t)                                          \
  O(narenas_tdata, uint32_t, uint32_t)                                         \
  O(thread_allocated_last_event, uint64_t, uint64_t)                           \
  O(thread_allocated_next_event, uint64_t, uint64_t)                           \
  O(thread_deallocated_last_event, uint64_t, uint64_t)                         \
  O(thread_deallocated_next_event, uint64_t, uint64_t)                         \
  O(tcache_gc_event_wait, uint64_t, uint64_t)                                  \
  O(tcache_gc_dalloc_event_wait, uint64_t, uint64_t)                           \
  O(prof_sample_event_wait, uint64_t, uint64_t)                                \
  O(prof_sample_last_event, uint64_t, uint64_t)                                \
  O(stats_interval_event_wait, uint64_t, uint64_t)                             \
  O(stats_interval_last_event, uint64_t, uint64_t)                             \
  O(peak_alloc_event_wait, uint64_t, uint64_t)                                 \
  O(peak_dalloc_event_wait, uint64_t, uint64_t)                                \
  O(prof_tdata, prof_tdata_t *, prof_tdata_t *)                                \
  O(prng_state, uint64_t, uint64_t)                                            \
  O(iarena, arena_t *, arena_t *)                                              \
  O(arena, arena_t *, arena_t *)                                               \
  O(arenas_tdata, arena_tdata_t *, arena_tdata_t *)                            \
  O(sec_shard, uint8_t, uint8_t)                                               \
  O(binshards, tsd_binshards_t, tsd_binshards_t)                               \
  O(tsd_link, tsd_link_t, tsd_link_t)                                          \
  O(in_hook, bool, bool)                                                       \
  O(peak, peak_t, peak_t)                                                      \
  O(activity_callback_thunk, activity_callback_thunk_t,                        \
    activity_callback_thunk_t)                                                 \
  O(tcache_slow, tcache_slow_t, tcache_slow_t)                                 \
  O(rtree_ctx, rtree_ctx_t, rtree_ctx_t)

#define TSD_DATA_SLOWER O(witness_tsd, witness_tsd_t, witness_tsdn_t)

struct tsd_s {
#define O(n, t, nt) t TSD_MANGLE(n);
  int state;
  TSD_DATA_FAST
  TSD_DATA_SLOWER
  TSD_DATA_SLOW
#undef O
};

int main(int argc, char **argv) {
  atomic_load_zu();
  atomic_fetch_add_zu();
  atomic_load_u();
  atomic_fetch_add_u();
  struct tsd_s t;
}
