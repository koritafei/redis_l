/**
 * @file time_test.c
 * @author koritafei (koritafei@gmail.com)
 * @brief test srand time
 * @version 0.1
 * @date 2020-11-13
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char **argv) {
  struct timeval tv;

  printf("pid = %d\n", getpid());
  srand(time(NULL) ^ getpid());
  int r = rand();
  printf("rand number = %d\n", r);
  gettimeofday(&tv, NULL);
  printf("sec = %ld, usec = %ld\n", tv.tv_sec, tv.tv_usec);
  for (size_t i = 0; i < 10; i++) {
    usleep(100);
  }

  gettimeofday(&tv, NULL);
  printf("sec = %ld, usec = %ld\n", tv.tv_sec, tv.tv_usec);
}
