#ifndef __DICT__H__
#define __DICT__H__

#include <stdint.h>
#include <stdio.h>

#include "zmalloc.h"

#define DICT_ERR 1
#define DICT_OK  0

#define DICT_NOUSED(V) ((void)V)

typedef struct dictEntry {
  void *key;
  union {
    void *   val;
    uint64_t u64;
    int64_t  s64;
    double   d;
  } v;
  dictEntry *next;
} dictEntry;

typedef struct dictType {
  uint64_t (*hashFunction)(const void *key);
  void *(*keyDup)(const void *privdata, const void *key);
  void *(*valDup)(const void *privdata, const void *key);
  int (*keyCompare)(void *privdata, const void *key1, const void *key2);
  void (*keyDestructor)(void *privdata, void *key);
  void (*valDestructor)(void *privdata, void *val);
} dictType;

typedef struct dictht {
  dictEntry **  table;
  unsigned long used;
  unsigned long sizemask;
  unsigned long size;
} dictht;

typedef struct dict {
  dictType *    type;
  dictht        ht[2];
  void *        privdata;
  long          rehashidx;  //当前rehash到的位置, -1表示没有进行hash
  unsigned long iterator;
} dict;

typedef struct dictIterator {
  dict *     d;
  long       index;
  int        table, safe;
  dictEntry *entry, *nextentry;
  long long  fingerprint;
} dictIterator;

typedef void(dictScanFunction)(void *privdata, const dictEntry *de);
typedef void(dictScanBucketFunction)(void *privdata, dictEntry **bucketref);

#define DICT_HT_INITIAL_SIZE 4

// macros
#define dictFreeVal(d, entry)                                                  \
  if ((d)->type->valDestructor)                                                \
  (d)->type->valDestructor((d)->privdata, (entry)->v.val)

#define dictSetVal(d, entry, _val_)                                            \
  do {                                                                         \
    if ((d)->type->valDup) {                                                   \
      (entry)->v.val = (d)->type->valDup((d)->privdata, _val_);                \
    } else {                                                                   \
      (entry)->v.val = _val_;                                                  \
    }                                                                          \
  } while (0)

#define dictSetSignedInternalVal(entry, _val_)                                 \
  do {                                                                         \
    (entry)->v.s64 = _val_;                                                    \
  } while (0)

#define dictSetUnsignedInternalVal(entry, _val_)                               \
  do {                                                                         \
    (entry)->v.u64 = _val_;                                                    \
  } while (0)

#define dictSetDoubleVal(entry, _val_)                                         \
  do {                                                                         \
    (entry)->v.d = _val_;                                                      \
  } while (0)

#define dictFreeKey(d, entry)                                                  \
  if ((d)->type->keyDestructor)                                                \
  (d)->type->keyDestructor((d)->privdata, (entry)->key)

#define dictSetKey(d, entry, _key_)                                            \
  do {                                                                         \
    if ((d)->type->keyDup)                                                     \
      (entry)->key = (d)->type->keyDup((d)->privdata, _key_);                  \
    else                                                                       \
      (entry)->key = _key_;                                                    \
  } while (0)

#define dictKeyCompare(d, key1, key2)                                          \
  (((d)->type->keyCompare) ? (d)->type->keyCompare((d)->privdata, key1, key2)  \
                           : (key1) == (key2))

#define dictHashKey(d, key)            (d)->type->hashFunction(key)
#define dictGetKey(he)                 ((he)->key)
#define dictGetval(he)                 ((he)->v.val)
#define dictGetSignedInternalVal(he)   ((he)->v.s64)
#define dictGetUnsignedInternalVal(he) ((he)->v.u64)
#define dictGetDoubleVal(he)           ((he)->v.d)
#define dictGetSlots(d)                ((d)->ht[0].size + (d)->ht[1].size)
#define dictGetSize(d)                 ((d)->ht[0].used + (d)->ht[1].used)
#define dictIsRehashing(d)             ((d)->rehashidx != -1)

// api
dict *        dictCreate(dictType *type, void *privDataPtr);
int           dictExpand(dict *d, unsigned long size);
int           dictAdd(dict *d, void *key, void *val);
dictEntry *   dictAddRaw(dict *d, void *key, dictEntry **existing);
dictEntry *   dictAddOrFind(dict *d, void *key);
int           dictReplace(dict *d, void *key, void *val);
int           dictDelete(dict *d, const void *key);
dictEntry *   dictUnlink(dict *ht, const void *key);
void          dictFreeUnlinkEntry(dict *d, dictEntry *he);
void          dictRelease(dict *d);
dictEntry *   dictFind(dict *d, const void *key);
void *        dictFetchValue(dict *d, const void *key);
int           dictResize(dict *d);
dictIterator *dictGetIterator(dict *d);
dictIterator *dictGetSafeIterator(dict *d);
dictEntry *   dictGetNextEntry(dictIterator *iter);
void          dictReleaseIterator(dictIterator *iter);
dictEntry *   dictGetRandomKey(dict *d);
dictEntry *   dictGetFairRandomKey(dict *d);
unsigned int  dictGetSomeKeys(dict *d, dictEntry **des, unsigned int count);
void          dictGetStats(char *buf, size_t bufsize, dict *d);
uint64_t      dictGenHashFunction(const void *key, int len);
uint64_t      dictGenCaseHashFunction(const unsigned char *buf, int len);
void          dictEmpty(dict *d, void(callback)(void *));
void          dictEnableResize(void);
void          dictDisableResize(void);
int           dictRehash(dict *d, int n);
int           dictRehashMillisends(dict *d, int ms);
void          dictSetHashFunctionSeed(uint8_t *seed);
uint8_t *     dictGetHashFunctionSeed(void);
unsigned long dictScan(dict *d, unsigned long v, dictScanFunction *fn,
                       dictScanBucketFunction *bucketfn, void *privdata);
uint64_t      dictGetHash(dict *d, const void *key);
dictEntry **  dictFindEntryRefByPtrAndHash(dict *d, const void *oldptr,
                                           uint64_t ptr);

// hash tables type
extern dictType dictTypeHeapStringCopyKey;
extern dictType dictTypeHeapStrings;
extern dictType dictTypeHeapStringCopyKeyValue;

#endif  // !__DICT__H__
