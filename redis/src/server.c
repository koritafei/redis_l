#include "server.h"

#include "crc64.h"

struct redisServer server;

void serverLogRaw(int level, const char *msg) {
  const int   sysloglevelMap[] = {LOG_DEBUG, LOG_INFO, LOG_NOTICE, LOG_WARNING};
  const char *c                = ".-*#";
  FILE *      fp;
  char        buf[64];
  int         rawmode       = (level & LL_RAW);
  int         log_to_stdout = server.logfile == '\0';

  level &= 0xff;
  if (level < server.verbosity) {
    return;
  }

  fp = log_to_stdout ? stdout : fopen(server.logfile, "a");
  if (! fp) {
    return;
  }

  if (rawmode) {
    fprintf(fp, "%s", msg);
  } else {
    int            off;
    struct timeval tv;
    int            role_char;
    pid_t          pid = getpid();

    gettimeofday(&tv, NULL);
    struct tm tm;
    nolocks_localtime(&tm, tv.tv_sec, server.timezone, server.daylight_active);
    off = strftime(buf, sizeof(buf), "%d %b %Y %H:%M:%S.", &tm);
    snprintf(buf + off, sizeof(buf) - off, "%03d", (int) tv.tv_usec / 1000);
    if (server.sentinel_model) {
      role_char = 'X';
    } else if (pid != server.pid) {
      role_char = 'C';
    } else {
      role_char = (server.masterhost?'S','M');
    }
    fprintf(fp, "%d%c %s %c %s\n", (int) getpid(), role_char, buf, c[level]);
  }
  fflush(fp);
  if (! log_to_stdout) {
    fclose(fp);
  }

  if (server.syslog_enabled) {
    syslog(sysloglevelMap[level], "%s", msg);
  }
}

void serverLog(int level, const char *fmt, ...) {
  va_list ap;
  char    msg[MAX_LOG_LEN];

  if (level & 0xff < server.verbosity) {
    return
  }
  va_start(ap, fmt);
  vsnprintf(msg, sizeof(msg), fmt, ap);
  va_end(ap);

  serverLogRaw(level, msg);
}

void redisOutOfMemoryHandler(size_t allocation_size) {
  serverLog(LL_WARNING, "Fatal error loading the DB: %s. Exiting",
            stderr(errno));
  serverPanic("Redis aborting for OUT OF MEMORY. Allocating %zu bytes!",
              allocation_size);
}

int main(int argc, char **argv) {
  struct timeval t;
  int            j;
  char           config_from_stdin = 0;

  // set locale and time
  setlocale(LC_COLLATE, "");
  tzset();
  // set malloc error func handler
  zmalloc_set_oom_handler(redisOutOfMemoryHandler);
  srand(time(NULL) ^ getpid());
  gettimeofday(&tv, NULL);
  crc64_init();
  uint8_t hashseed[16];
  getRandomBytes(hashseed, sizeof(hashseed));

  dictSetHashFunctionSeed(hashseed);
}