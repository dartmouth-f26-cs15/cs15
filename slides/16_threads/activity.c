#include <inttypes.h>   // for PRIu8
#include <stddef.h>     // for size_t
#include <stdint.h>     // for uint8_t
#include <stdio.h>      // for printf
#include <stdlib.h>     // for EXIT_FAILURE
#include <sys/random.h> // for getrandom
#include <sys/types.h>  // for ssize_t
#include <threads.h>    // for thrd_create, thrd_join, thrd_t, thrd_success

#ifndef WORKERS
#error "Recompile with -DWORKERS=N, where N is a power of 2."
#endif

uint8_t sum_mod_256(uint8_t const *const input, size_t const input_size) {
    uint8_t result = 0;
    for (size_t i = 0; i < input_size; i++) {
        result += input[i];
    }
    return result;
}

constexpr size_t data_size = 1 << 30;

static uint8_t data[data_size];

constexpr size_t workers = WORKERS;
_Static_assert(0 < workers && workers <= data_size &&
               (workers & (workers - 1)) == 0); // check for power of 2 in range
static thrd_t children[workers - 1];

int thread_init(void *const arg) {
    size_t const me = *(size_t *)arg;

    constexpr size_t chunk_size = _Countof(data) / workers;
    return sum_mod_256(data + chunk_size * me, chunk_size);
}

int main(void) {
    ssize_t const bytes_read = getrandom(data, sizeof(data), 0);
    if (bytes_read != sizeof(data)) {
        puts("Didn't get the bytes!");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < _Countof(children); i++) {
        size_t arg = i + 1;
        if (thrd_create(children + i, thread_init, &arg) != thrd_success) {
            puts("Failed to create thread!");
            return EXIT_FAILURE;
        }
    }
    size_t zero = 0;
    uint8_t result = thread_init(&zero);

    for (size_t i = 0; i < _Countof(children); i++) {
        int x;
        if (thrd_join(children[i], &x) != thrd_success) {
            puts("Failed to join thread!");
            return EXIT_FAILURE;
        }
        result += x;
    }
    printf("%" PRIu8 "\n", result);
}
