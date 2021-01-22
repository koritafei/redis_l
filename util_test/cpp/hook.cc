/**
 * @file hook.cc
 * @author koritafei (koritafei@gmail.com)
 * @brief hook函数
 * @version 0.1
 * @date 2020-11-16
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void (*hook)(const char *str);

void default_hook(const char *str) {
  printf("default hook:\n %s\n", str);
}

void my_hook(const char *str) {
  printf("my hook:\n %s\n", str);
}

int main() {
  const char *str = "hook test";
  hook            = default_hook;
  hook(str);
  hook = my_hook;
  hook(str);
}
