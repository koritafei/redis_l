/**
 * @file sched_getcpu_test.c
 * @author koritafei (koritafei@gmail.com)
 * @brief test sched_getcpu 返回线程当前在哪个cpu核执行
 * @version 0.1
 * @date 2020-11-11
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <sched.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
  for (int i = 0; i < 1000; i++) {
    sleep(2);
    printf("cpus is %d\n", sched_getcpu());
  }
}