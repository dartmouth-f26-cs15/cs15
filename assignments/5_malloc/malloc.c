#define _DEFAULT_SOURCE
#include <pthread.h> // for PTHREAD_MUTEX_INITIALIZER, pthread_mutex_t, pthread_mutex_lock, pthread_mutex_unlock
#include <stddef.h>  // for size_t
#include <stdlib.h>  // for malloc, free, realloc, calloc, reallocarray, aligned_alloc, posix_memalign, valloc, EXIT_FAILURE, free_sized, free_aligned_sized
#include <string.h>  // for memset
#include <unistd.h>  // for write, STDERR_FILENO, _exit
#include <malloc.h>  // for malloc_usable_size, memalign, pvalloc, mallopt, mallinfo, mallinfo2, struct mallinfo, struct mallinfo2, malloc_trim, malloc_stats, malloc_info
#include <stdio.h>   // for FILE

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

void free_sized(void *const p, size_t) {
    free(p);
}

void free_aligned_sized(void *const p, size_t, size_t) {
    free(p);
}

#define UNIMPLEMENTED(s) { \
    static char const msg[] = s " is not implemented. Don't worry about this.\n-CS15 Staff.\n"; \
    write(STDERR_FILENO, msg, sizeof(msg) - 1); \
    _exit(EXIT_FAILURE); \
}

void *aligned_alloc(size_t, size_t) {
    UNIMPLEMENTED("aligned_alloc");
    return nullptr;
}

size_t malloc_usable_size(void *) {
    UNIMPLEMENTED("malloc_usable_size");
    return 0;
}

void *memalign(size_t, size_t) {
    UNIMPLEMENTED("memalign");
    return 0;
}

int posix_memalign(void **, size_t, size_t) {
    UNIMPLEMENTED("posix_memalign");
    return -1;
}

void *valloc(size_t) {
    UNIMPLEMENTED("valloc");
    return nullptr;
}

void *pvalloc(size_t) {
    UNIMPLEMENTED("pvalloc");
    return nullptr;
}

struct mallinfo mallinfo(void) {
    UNIMPLEMENTED("mallinfo");
    return (struct mallinfo){};
}

struct mallinfo2 mallinfo2(void) {
    UNIMPLEMENTED("mallinfo2");
    return (struct mallinfo2){};
}

int mallopt(int, int) {
    UNIMPLEMENTED("mallopt");
    return -1;
}

int malloc_trim(size_t) {
    UNIMPLEMENTED("malloc_trim");
    return -1;
}

void malloc_stats(void) {
    UNIMPLEMENTED("malloc_stats");
}

int malloc_info(int, FILE *) {
    UNIMPLEMENTED("malloc_info");
}
