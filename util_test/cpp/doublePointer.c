/**
 * @file doublePointer.c
 * @author koritafei (koritafei@gmail.com)
 * @brief 二级指针测试
 * @version 0.1
 * @date 2020-12-13
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <malloc.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
  char **a;
  a = (char **)malloc(sizeof(char *) * 3);
  for (int i = 0; i < 3; i++) {
    a[i] = (char *)malloc(sizeof(char));
  }

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 10; j++) {
      a[i][j] = 'A' + i;
    }
  }

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%c\t", a[i][j]);
    }
    printf("\n");
  }
  for (int i = 0; i < 3; i++) {
    free(a[i]);
  }
  free(a);
}
