#ifndef __TSD__H__
#define __TSD__H__

#include <atomic>
#include <iostream>

struct tsd_s {
  std::atomic_uint32_t state;
  uint64_t
      cant_access_tsd_items_directly_use_a_getter_or_setter_thread_allocated;
  uint64_t
      cant_access_tsd_items_directly_use_a_getter_or_setter_thread_allocated_next_event_fast;
  uint64_t
      cant_access_tsd_items_directly_use_a_getter_or_setter_thread_deallocated;
  uint64_t
           cant_access_tsd_items_directly_use_a_getter_or_setter_thread_deallocated_next_event_fast;
  tcache_t cant_access_tsd_items_directly_use_a_getter_or_setter_tcache;
  witness_tsd_t
       cant_access_tsd_items_directly_use_a_getter_or_setter_witness_tsd;
  bool cant_access_tsd_items_directly_use_a_getter_or_setter_tcache_enabled;
  bool
      cant_access_tsd_items_directly_use_a_getter_or_setter_arenas_tdata_bypass;
  int8_t cant_access_tsd_items_directly_use_a_getter_or_setter_reentrancy_level;
  uint32_t cant_access_tsd_items_directly_use_a_getter_or_setter_narenas_tdata;
  uint64_t
      cant_access_tsd_items_directly_use_a_getter_or_setter_thread_allocated_last_event;
  uint64_t
      cant_access_tsd_items_directly_use_a_getter_or_setter_thread_allocated_next_event;
  uint64_t
      cant_access_tsd_items_directly_use_a_getter_or_setter_thread_deallocated_last_event;
  uint64_t
      cant_access_tsd_items_directly_use_a_getter_or_setter_thread_deallocated_next_event;
  uint64_t
      cant_access_tsd_items_directly_use_a_getter_or_setter_tcache_gc_event_wait;
  uint64_t
      cant_access_tsd_items_directly_use_a_getter_or_setter_tcache_gc_dalloc_event_wait;
  uint64_t
      cant_access_tsd_items_directly_use_a_getter_or_setter_prof_sample_event_wait;
  uint64_t
      cant_access_tsd_items_directly_use_a_getter_or_setter_prof_sample_last_event;
  uint64_t
      cant_access_tsd_items_directly_use_a_getter_or_setter_stats_interval_event_wait;
  uint64_t
      cant_access_tsd_items_directly_use_a_getter_or_setter_stats_interval_last_event;
  uint64_t
      cant_access_tsd_items_directly_use_a_getter_or_setter_peak_alloc_event_wait;
  uint64_t
      cant_access_tsd_items_directly_use_a_getter_or_setter_peak_dalloc_event_wait;
  prof_tdata_t
      *    cant_access_tsd_items_directly_use_a_getter_or_setter_prof_tdata;
  uint64_t cant_access_tsd_items_directly_use_a_getter_or_setter_prng_state;
  arena_t *cant_access_tsd_items_directly_use_a_getter_or_setter_iarena;
  arena_t *cant_access_tsd_items_directly_use_a_getter_or_setter_arena;
  arena_tdata_t
      *   cant_access_tsd_items_directly_use_a_getter_or_setter_arenas_tdata;
  uint8_t cant_access_tsd_items_directly_use_a_getter_or_setter_sec_shard;
  tsd_binshards_t
             cant_access_tsd_items_directly_use_a_getter_or_setter_binshards;
  tsd_link_t cant_access_tsd_items_directly_use_a_getter_or_setter_tsd_link;
  bool       cant_access_tsd_items_directly_use_a_getter_or_setter_in_hook;
  peak_t     cant_access_tsd_items_directly_use_a_getter_or_setter_peak;
  activity_callback_thunk_t
      cant_access_tsd_items_directly_use_a_getter_or_setter_activity_callback_thunk;
  tcache_slow_t
              cant_access_tsd_items_directly_use_a_getter_or_setter_tcache_slow;
  rtree_ctx_t cant_access_tsd_items_directly_use_a_getter_or_setter_rtree_ctx;
};
}
;

#endif  //!__TSD__H__