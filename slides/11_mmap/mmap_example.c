#include <sys/mman.h> // for mmap, munmap, PROT_*, MAP_*
#include <stdlib.h> // for EXIT_FAILURE
#include <unistd.h> // for getpagesize
#include <stdio.h> // for printf, puts, getchar
#include <string.h> // for memcpy

void f(void) {
    puts("I got called!");
}

int main(void) {
    unsigned char *new_mapping = mmap(
        (void *)0x1234000, // addr
        getpagesize(), // len
        PROT_READ | PROT_WRITE | PROT_EXEC, // prot
        MAP_ANONYMOUS | MAP_PRIVATE | MAP_FIXED_NOREPLACE, // flags
        -1, // fd
        0 // offset
    );

    if (new_mapping == MAP_FAILED) {
        return EXIT_FAILURE;
    }

    memcpy(new_mapping, f, getpagesize());

    ((void (*)(void))new_mapping)();

    munmap(new_mapping, getpagesize());
}
