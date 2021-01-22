/**
 * @file jemalloc_new.cc
 * @author koritafei (koritafei@gmail.com)
 * @brief C++ new delete 重载
 * @version 0.1
 * @date 2020-11-17
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <mutex>
#include <new>

#include "jemalloc.h"

void *operator new(std::size_t size);
void *operator new[](std::size_t size);
void *operator new(std::size_t size, std::nothrow_t &) noexcept;
void *operator new[](std::size_t size, std::nothrow_t &) noexcept;
void  operator delete(void *ptr) noexcept;
void  operator delete[](void *ptr) noexcept;
void  operator delete(void *ptr, std::nothrow_t &) noexcept;
void  operator delete[](void *ptr, std::nothrow_t &) noexcept;

static void *handleOOM(std::size_t size, bool nothrow) {
  void *ptr = nullptr;
  while (ptr == nullptr) {
    std::new_handler handle;
    {
      static std::mutex           mtx;
      std::lock_guard<std::mutex> lk(mtx);
      handle = std::set_new_handler(nullptr);
      std::set_new_handler(handle);
    }

    if (nullptr == handle) {
      break;
    }

    try {
      handle();
    } catch (const std::bad_alloc &) {
      break;
    }

    ptr = je_malloc(size);
  }

  if (nullptr == ptr && !nothrow) {
    std::__throw_bad_alloc();
  }

  return ptr;
}

template <bool IsNoException>
void *newImp(std::size_t size) noexcept(IsNoException) {
  void *ptr = je_malloc(size);
  if (likely(ptr != nullptr)) {
    return ptr;
  }

  return handleOOM(size, IsNoException);
}

void *operator new(std::size_t size) {
  return newImp<false>(size);
}

void *operator new[](std::size_t size) {
  return newImp<false>(size);
}

void *operator new(std::size_t size) noexcept {
  return newImp<true>(size);
}

void operator delete(void *ptr) noexcept {
  je_free(ptr);
}

void operator delete[](void *ptr) noexcept {
  je_free(ptr);
}

void operator delete(void *ptr, std::nothrow_t &) noexcept {
  je_free(ptr);
}
void operator delete[](void *ptr, std::nothrow_t &) noexcept {
  je_free(ptr);
}