#ifndef __FMACROS__H__
#define __FMACROS__H__

#define _BSD_SOURCE

#if defined(__linux__)
#define _GNU_SOURCE
#define _DEFAULT_SOURCE
#endif

#if defined(__linux__) || defined(__OpenBSD__)
#define _XOPEN_SOURCE 700
#endif

#define _LARGEFILE_SOURCE
#define _FILE_OFFSET_BITS 46

#endif  // !__FMACROS__H__