#ifndef __CONFIG__H__
#define __CONFIG__H__

#ifdef __APPLE__
#include <Availability.h>
#endif

#ifdef __linux__
#include <features.h>
#include <linux/version.h>
#endif

#if defined(__APPLE__) && !defined(MAC_OS_X_VERSION_10_6)
#define redis_fstat fstat64
#define redis_stat  stat64
#else
#define redis_fstat fstat
#define redis_stat  stat
#endif

#ifdef __linux__
#define HAVE_PROC_STAT  1
#define HAVE_PROC_MAPS  2
#define HAVE_PROC_SMAPS 3

#endif

#endif  //!__CONFIG__H__