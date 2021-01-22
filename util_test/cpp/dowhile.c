/**
 * @file dowhile.c
 * @author your name (you@domain.com)
 * @brief do while宏替换
 * @version 0.1
 * @date 2020-12-03
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <stdio.h>

#define ADD(a, b, c)                                                           \
  do {                                                                         \
    (c) = (a) + (b);                                                           \
  } while (0)

int main(int argc, char **argv) {
  int a = 1, b = 3, c;
  ADD(a, b, c);
  printf("%d + %d = %d\n", a, b, c);
}
