/**
 * @file pthread_getspecific_test.c
 * @author koritafei (koritafei@gmail.com)
 * @brief get pthread info
 * @version 0.1
 * @date 2020-11-08
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

pthread_key_t key;  // 线程的私有存储器

void get_pthread_specific() {
  int *tmp = (int *)pthread_getspecific(key);  //同一个线程内，各函数的共享数据
  printf("%d is running in %s\n", *tmp, __func__);
}

void *pthread_func(void *args) {
  pthread_setspecific(key, args);
  int *tmp = (int *)pthread_getspecific(key);  //获取线程的私有空间
  printf("%d is running in %s\n", *tmp, __func__);
  (*tmp) = (*tmp) * 100;  // 修改私有变量的值
  get_pthread_specific();
  return (void *)0;
}

int main(int argc, char **argv) {
  int       a = 1;
  int       b = 2;
  pthread_t pa, pb;
  pthread_key_create(&key, NULL);
  pthread_create(&pa, NULL, pthread_func, &a);
  pthread_create(&pb, NULL, pthread_func, &b);

  pthread_join(pa, NULL);
  pthread_join(pb, NULL);

  return 0;
}