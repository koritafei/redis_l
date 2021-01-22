/**
 * @file tzset_test.cc
 * @author koritafei (koritafei@gmail.com)
 * @brief tzset时区设置
 * @version 0.1
 * @date 2020-11-06
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <locale.h>
#include <stdio.h>
#include <time.h>
#include <wchar.h>

int main(int argc, char **argv) {
  setlocale(LC_COLLATE, "");
  tzset();
  printf("timezone = %ld\n", timezone);
  printf("tzname[0] = %s\ntzname[1] = %s\n", tzname[0], tzname[1]);
  return 0;
}
