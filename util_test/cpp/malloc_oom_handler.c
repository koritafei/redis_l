/**
 * @file malloc_oom_handler.c
 * @author koritafei (koritafei@gmail.com)
 * @brief test malloc, __malloc_hook, oom_handler
 * @version 0.1
 * @date 2020-11-06
 *
 * @copyright Copyright (c) 2020
 *
 */
#if defined(__APPLE__)
#include <malloc/malloc.h>
#else
#include <malloc.h>
#endif

#include <stdio.h>
#include <stdlib.h>

static void default_oom_handler(size_t size) {
  fprintf(stderr, "Out of memory allocate %zu bytes\n", size);
  fflush(stderr);
  abort();
}

static void (*d_oom_handler)(size_t) = default_oom_handler;

void my_oom_handler(size_t size) {
  fprintf(stderr, "My function out of memory allocate %zu bytes\n", size);
  fflush(stderr);
  abort();
}

void set_oom_handler(void (*oom_handler)(size_t)) {
  d_oom_handler = oom_handler;
}

void *d_malloc(size_t size) {
  void *ptr = malloc(size);
  // void *ptr = NULL;  // test oom handler
  if (NULL == ptr) {
    d_oom_handler(size);
  }

  return ptr;
}

void d_free(void *ptr) {
  if (NULL != ptr) {
    free(ptr);
  }
  return;
}

int main(int argc, char **argv) {
  // define oom handler
  set_oom_handler(my_oom_handler);  // default oom handler
  char *p = (char *)d_malloc(sizeof(char) * 20);
  d_free(p);
}