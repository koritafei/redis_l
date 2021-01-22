/**
 * @file pthread_self.c
 * @author koritafei (koritafei@gmail.com)
 * @brief pthread self id test
 * @version 0.1
 * @date 2020-11-09
 *
 * @copyright Copyright (c) 2020
 *cd
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *calls(void *ptr) {
  printf("In fucntion \n thread id = %ld\n", pthread_self());
  pthread_exit(NULL);
  return NULL;
}

int main(int argc, char **argv) {
  pthread_t pthread;
  pthread_create(&pthread, NULL, calls, NULL);
  printf("In main\n thread id = %ld\n", pthread_self());
  pthread_join(pthread, NULL);

  return 0;
}
