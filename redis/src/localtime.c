#include <time.h>

static int is_leap_year(time_t year) {
  if (year % 4) {
    return 0;
  } else if (year % 100) {
    return 1;
  } else if (year % 400) {
    return 0;
  } else {
    return 1;
  }
}

// 无锁的时间计算，进程安全
void nolocks_localtime(struct tm *tmp, time_t t, time_t tz, int dst) {
  const time_t secs_min  = 60;
  const time_t secs_hour = 3600;
  const time_t secs_day  = 3600 * 24;

  t -= tz;                        // adjust time zone
  t += 3600 * dst;                // adjust daylight time
  time_t days    = t / secs_day;  // day passed since epoch
  time_t seconds = t % secs_day;  // remaining seconds

  tmp->tm_isdst = dst;
  tmp->tm_hour  = seconds / secs_hour;
  tmp->tm_min   = (seconds % secs_hour) / secs_min;
  tmp->tm_sec   = (seconds % secs_hour) % secs_min;

  tmp->tm_wday = (days + 4) % 7;
  tmp->tm_year = 1970;
  // 计算当前年份
  while (1) {
    time_t days_of_year = 365 + is_leap_year(tmp->tm_year);
    if (days_of_year > days) {
      break;
    }
    days -= days_of_year;
    tmp->tm_year++;
  }
  tmp->tm_yday  = days;
  int mdays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  mdays[1] += is_leap_year(tmp->tm_year);
  tmp->tm_mon = 0;
  while (days >= mdays[tmp->tm_mon]) {
    days -= mdays[tmp->tm_mon];
    tmp->tm_mon++;
  }

  tmp->tm_mday = days + 1;
  tmp->tm_year -= 1900;
}

//#define LOCALTIME_TEST_MAIN
#ifdef LOCALTIME_TEST_MAIN
#include <stdio.h>
int main(int argc, char **argv) {
  tzset();
  time_t     t               = time(NULL);
  struct tm *tv              = localtime(&t);
  int        daylight_active = tv->tm_isdst;
  struct tm  tm;
  char       buf[1024];

  nolocks_localtime(&tm, t, timezone, daylight_active);
  strftime(buf, sizeof(buf), "%d %b %Y %H:%M:%S", &tm);
  printf("[timezone: %d, dl: %d] %s\n", (int) timezone, (int) daylight_active,
         buf);
}
#endif
