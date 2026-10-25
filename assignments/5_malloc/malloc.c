#define _DEFAULT_SOURCE
#include <pthread.h> // for PTHREAD_MUTEX_INITIALIZER, pthread_mutex_t, pthread_mutex_lock, pthread_mutex_unlock
#include <stddef.h>  // for size_t
#include <stdlib.h>  // for malloc, free, realloc, calloc, reallocarray
#include <string.h>  // for memset

#include "cs15_malloc.h"

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *malloc(size_t const size) {
    pthread_mutex_lock(&mutex);
    void *const result = cs15_malloc(size);
    pthread_mutex_unlock(&mutex);
    return result;
}

void free(void *const ptr) {
    pthread_mutex_lock(&mutex);
    cs15_free(ptr);
    pthread_mutex_unlock(&mutex);
}

void *calloc(size_t const nmemb, size_t const size) {
    size_t allocation_size;
    if (__builtin_mul_overflow(nmemb, size, &allocation_size)) {
        return nullptr;
    }
    void *const result = malloc(allocation_size);
    if (result == nullptr) {
        return nullptr;
    }
    memset(result, 0, allocation_size);
    return result;
}

void *reallocarray(void *const ptr, size_t const nmemb, size_t const size) {
    size_t allocation_size;
    if (__builtin_mul_overflow(nmemb, size, &allocation_size)) {
        return nullptr;
    }
    return realloc(ptr, allocation_size);
}

void *realloc(void *const ptr, size_t const size) {
    pthread_mutex_lock(&mutex);
    void *const result = cs15_realloc(ptr, size);
    pthread_mutex_unlock(&mutex);
    return result;
}
