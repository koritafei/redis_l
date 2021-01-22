/**
 * @file server.h
 * @author koritafei (koritafei@gmail.com)
 * @brief redis server
 * @version 0.1
 * @date 2020-11-06
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef __SERVER__H__
#define __SERVER__H__

#include <locale.h>
#include <stdarg.h>
#include <time.h>
#include <unistd.h>
#include <syslog.h>

#include "zmalloc.h"

// log level
#define LL_DEBUG   0
#define LL_VERBOSE 1
#define LL_NOTICE  2
#define LL_WARNING 3
#define LL_RAW     (1 << 10)  // log without timestamp

#define LOG_MAX_LEN 1024

#define serverPanic(...) _serverPanic(__FILE__, __LINE__, __VA_ARGS__), _exit(1)

struct redisServer {
  pid_t     pid;             // main process id
  pthread_t main_thread_id;  // main thread id
  char*     configpath;      // 配置文件绝对路径
  char*     executable;      // 执行文件绝对路径
  char**    exec_arg;        //执行参数
  int       sentinel_mode;   //静默模式

  // configuration
  int verbosity;  // loglevel in config

  // loging
  char* logfile;         // log file path
  int   syslog_enabled;  // syslog enable?

  // replication
  char* masterhost;  // master hostname

  // time cache
  time_t timezone;
  int    daylight_active;
};

#endif  //!__SERVER__H__
