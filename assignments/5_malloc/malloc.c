#define _DEFAULT_SOURCE
#include <malloc.h> // for malloc_usable_size, memalign, pvalloc, mallopt, mallinfo, mallinfo2, struct mallinfo, struct mallinfo2, malloc_trim, malloc_stats, malloc_info
#include <threads.h> // mtx_t, mtx_init, thrd_success, mtx_plain, mtx_lock, mtx_unlock
#include <stddef.h>  // for size_t
#include <stdio.h>   // for FILE
#include <stdlib.h> // for malloc, free, realloc, calloc, reallocarray, aligned_alloc, posix_memalign, valloc, EXIT_FAILURE, free_sized, free_aligned_sized
#include <string.h> // for memset
#include <unistd.h> // for write, STDERR_FILENO, _exit

#include "cs15_malloc.h"

static mtx_t mutex;
[[gnu::constructor]] static void initialize_heap_mutex(void) {
    if (mtx_init(&mutex, mtx_plain) != thrd_success) {
        _exit(EXIT_FAILURE);
    }
}

static void lock(void) {
    if (mtx_lock(&mutex) != thrd_success) {
        _exit(EXIT_FAILURE);
    }
}

static void unlock(void) {
    if (mtx_unlock(&mutex) != thrd_success) {
        _exit(EXIT_FAILURE);
    }
}

void *malloc(size_t const size) {
    lock();
    void *const result = cs15_malloc(size);
    unlock();
    return result;
}

void free(void *const ptr) {
    lock();
    cs15_free(ptr);
    unlock();
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
    lock();
    void *const result = cs15_realloc(ptr, size);
    unlock();
    return result;
}

void free_sized(void *const p, size_t) {
    free(p);
}

void free_aligned_sized(void *const p, size_t, size_t) {
    free(p);
}

[[noreturn]] static void unimplemented(char const *const s) {
    write(STDERR_FILENO, s, strlen(s));
    static char const msg[] =
        " is not implemented. Don't worry about this.\n-CS15 Staff.\n";
    write(STDERR_FILENO, msg, sizeof(msg) - 1);
    _exit(EXIT_FAILURE);
}

void *aligned_alloc(size_t, size_t) {
    unimplemented("aligned_alloc");
    return nullptr;
}

size_t malloc_usable_size(void *) {
    unimplemented("malloc_usable_size");
    return 0;
}

void *memalign(size_t, size_t) {
    unimplemented("memalign");
    return 0;
}

int posix_memalign(void **, size_t, size_t) {
    unimplemented("posix_memalign");
    return -1;
}

void *valloc(size_t) {
    unimplemented("valloc");
    return nullptr;
}

void *pvalloc(size_t) {
    unimplemented("pvalloc");
    return nullptr;
}

struct mallinfo mallinfo(void) {
    unimplemented("mallinfo");
    return (struct mallinfo){};
}

struct mallinfo2 mallinfo2(void) {
    unimplemented("mallinfo2");
    return (struct mallinfo2){};
}

int mallopt(int, int) {
    unimplemented("mallopt");
    return -1;
}

int malloc_trim(size_t) {
    unimplemented("malloc_trim");
    return -1;
}

void malloc_stats(void) {
    unimplemented("malloc_stats");
}

int malloc_info(int, FILE *) {
    unimplemented("malloc_info");
    return -1;
}
