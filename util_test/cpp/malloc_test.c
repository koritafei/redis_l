/**
 * @file malloc_test.cc
 * @author koritafei (koritafei@gmail.com)
 * @brief malloc 测试
 * @version 0.1
 * @date 2020-11-20
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define PREFIX_SIZE (0)

int main(int argc, char **argv) {
  size_t size = 10;
  void * ptr  = malloc(size + PREFIX_SIZE);
  printf("ptr = %p\n", ptr);
  (*(size_t *)ptr) = size;
  printf("ptr = %p\n", (char *)ptr + PREFIX_SIZE);
  size_t sz = *(size_t *)ptr;
  printf("size = %zu\n", sz);
}
