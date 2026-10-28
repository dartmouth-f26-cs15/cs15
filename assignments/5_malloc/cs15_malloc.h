#pragma once
#include <stddef.h> // for size_t

void *cs15_malloc(size_t);
void cs15_free(void *);
void *cs15_realloc(void *, size_t);
