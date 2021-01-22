#ifndef __SDS_ALLOC_H__
#define __SDS_ALLOC_H__

#include "zmalloc.h"

#define s_malloc  zmalloc
#define s_realloc zrealloc
#define s_free    zfree

#endif  // !__SDS_ALLOC_H__
