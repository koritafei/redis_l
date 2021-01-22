/**
 * @file struct.c
 * @author koritafei (koritafei@gmail.com)
 * @brief struct测试
 * @version 0.1
 * @date 2020-12-15
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

struct __attribute__((__packed__)) testA {
  uint16_t      alloc;
  uint16_t      len;
  unsigned char flags;
  char          buf[];
} testA;

struct __attribute__((__packed__)) testB {
  uint16_t      alloc;
  uint16_t      len;
  unsigned char flags;
} testB;

struct __attribute__((__packed__)) testC {
  char   a;
  float  b;
  double c;
  char   d;
};

struct testD {
  char   a;
  float  b;
  double c;
  char   d;
};

struct bs {
  int a : 4;
  int b : 5; /*从下一单元开始存放*/
  int c : 4;
};

struct __attribute__((__packed__)) bsa {
  int a : 4;
  int b : 5; /*从下一单元开始存放*/
  int c : 4;
};

typedef struct BB {
  unsigned int b1 : 5;
  unsigned int b2 : 5;
  unsigned int b3 : 5;
  unsigned int b4 : 5;
  unsigned int b5 : 5;
} BB;

typedef struct CC {
  int b1 : 1;
  int : 2;  //无影响
  int   b3 : 3;
  int   b4 : 2;
  int   b5 : 3;
  short b6 : 4;
  int   b7 : 1;

} CC;

int main(int argc, char **argv) {
  struct testA *a = (struct testA *)malloc(sizeof(struct testA));
  printf("%p\n", a);
  printf("%p\n", (struct testA *)((a) - sizeof(struct testA)));
  printf("%c\n", a[-1]);
  printf("%c\n", a[-2]);
  printf("%c\n", a[0]);
  printf("%d\n", sizeof(struct testA));
  printf("%d\n", sizeof(struct testB));
  free(a);
  BB b;
  printf("testC size %d, testD size %d\n", sizeof(struct testC),
         sizeof(struct testD));
  printf("bs size %d, bsa size %d BB size %d, %d %d CC size %d\n",
         sizeof(struct bs), sizeof(struct bsa), sizeof(struct BB), sizeof(int),
         sizeof(unsigned int), sizeof(struct CC));
}
