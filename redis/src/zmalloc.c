#include "zmalloc.h"
#include <pthread.h>

#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define update_zmalloc_state_alloc(__n)               \
  do {                                                \
    size_t _n = (__n);                                \
    if (_n & (sizeof(long) - 1)) {                    \
      _n += sizeof(long) - (_n & (sizeof(long) - 1)); \
      atomicIncr(used_memory, __n);                   \
    }                                                 \
  } while (0)

#define update_zmalloc_state_free(__n)                \
  do {                                                \
    size_t _n = (__n);                                \
    if (_n & (sizeof(long) - 1)) {                    \
      _n += sizeof(long) - (_n & (sizeof(long) - 1)); \
      atomicDecr(used_memory, __n);                   \
    }                                                 \
  } while (0)

static size_t used_memory = 0;
pthread_mutex_t used_memory_mutex = PTHREAD_MUTEX_INITIALIZER;

static void zmalloc_default_oom(size_t size) {
  fprintf(stderr, "zmalloc: out of memeory when try allocate %zu bytes\n",
          size);
  fflush(stderr);
  abort();
}

static void (*zmalloc_oom_handler)(size_t) = zmalloc_default_oom;

void zmalloc_set_oom_handler(void (*oom_handler)(size_t)) {
  zmalloc_oom_handler = oom_handler;
}

void zlibc_free(void *ptr) { free(ptr); }

void *zmalloc(size_t size) {
  void *ptr = malloc(size + PREFIX_SIZE);
  if (!ptr) {
    zmalloc_oom_handler(size);
  }
  *((size_t *)ptr) = size;
  update_zmalloc_state_alloc(size + PREFIX_SIZE);
  return (char *)ptr + PREFIX_SIZE;
}

void *zcalloc(size_t size) {
  void *ptr = calloc(1, size + PREFIX_SIZE);
  if (!ptr) {
    zmalloc_oom_handler(size);
  }
  *((size_t *)ptr) = size;
  return (char *)ptr + PREFIX_SIZE;
}

void *zrealloc(void *ptr, size_t size) {
  if (!size && ptr) {
    zfree(ptr);
    return NULL;
  }
  if (!ptr) {
    return zmalloc(size);
  }
  void *realptr = (char *)ptr - PREFIX_SIZE;
  size_t oldsize = (*(size_t *)ptr);
  void *newptr = realloc(realptr, size);
  if (!newptr) {
    zmalloc_oom_handler(size);
  }
  update_zmalloc_state_free(oldsize + PREFIX_SIZE);
  update_zmalloc_state_alloc(size + PREFIX_SIZE);
}

void zfree(void *ptr) {
  if (!ptr) {
    return;
  }
  void *realptr = (char *)ptr - PREFIX_SIZE;
  size_t oldsize = *(size_t *)ptr;
  update_zmalloc_state_free(oldsize);
  free(realptr);
}

char *ztrdup(const char *s) {
  size_t l = strlen(s) + 1;
  char *p = (char *)zmalloc(l);
  memcpy(p, s, l);
  return p;
}

size_t zmalloc_used_memory() {
  size_t um;
  atomicGet(used_memory, &um);
  return um;
}

// 获取进程的总内存，rss字段
size_t zmalloc_get_rss() {
  int page = sysconf(_SC_PAGESIZE);
  size_t rss;
  char buf[4096];
  char filename[256];
  int fd, count;
  char *p, *x;

  snprintf(filename, 256, "/proc/%d/stat", getpid());
  if (-1 == (fd = open(filename, O_RDONLY))) {
    return 0;
  }
  if (0 >= read(fd, buf, 4096)) {
    close(fd);
    return 0;
  }
  close(fd);

  p = buf;
  count = 23;  // rss 字段在第24位
  while (p && count--) {
    p = strchr(p, ' ');
    if (p) {
      p++;
    }
  }

  if (!p) {
    return 0;
  }

  x = strchr(p, ' ');
  if (!x) {
    return 0;
  }
  *x = '\0';

  rss = strtoll(p, NULL, 10);
  rss *= page;

  return rss;
}

int zmalloc_get_allocator_info(size_t *allocated, size_t *active,
                               size_t *resident) {
  *allocated = *active = *resident = 0;
  return 1;
}

void set_jemalloc_bg_thread(int enable) { ((void)(enable)); }

int jemalloc_purge() { return 0; }

size_t zmalloc_get_smap_bytes_by_field(char *field, long pid) {
  char line[1024];
  size_t bytes = 0;
  int flen = strlen(field);
  FILE *fp;

  if (-1 == pid) {
    fp = fopen("/proc/self/maps", "r");
  } else {
    char filename[256];
    snprintf(filename, sizeof(filename), "/proc/%ld/smaps", pid);
    fp = fopen(filename, "r");
  }

  if (!fp) {
    return 0;
  }

  while (NULL == (fgets(line, sizeof(line), fp))) {
    if (0 == strncmp(line, field, flen)) {
      char *p = strchr(line, 'k');
      if (p) {
        *p = '\0';
        bytes += strtol(line + flen, NULL, 10) * 1024;
      }
    }
  }
  fclose(fp);
  return bytes;
}

size_t zmalloc_get_private_dirty(long pid) {
  return zmalloc_get_smap_bytes_by_field("Private_Dirty:", pid);
}

// 获取系统的内存大小，bytes返回
size_t zmalloc_get_memory_size() {
  return (size_t)sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGESIZE);
}
