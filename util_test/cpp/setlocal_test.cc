#include <locale.h>
#include <stdio.h>
#include <time.h>
#include <wchar.h>

// setlocale 设置本地化

int main(void) {
  setlocale(LC_ALL, "en_US.UTF-8");
  setlocale(LC_NUMERIC, "de_DE.UTF-8");
  setlocale(LC_TIME, "cn_CN.UTF-8");

  wchar_t str[100];
  time_t  t = time(NULL);
  wcsftime(str, 100, L"%A %c", localtime(&t));
  wprintf(L"Number: %.2f\nDate:%Ls\n", 3.14, str);
}
