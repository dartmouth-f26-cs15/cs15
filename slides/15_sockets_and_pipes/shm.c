#include <unistd.h> // for fork, sleep
#include <sys/mman.h> // for mmap, MAP_*, PROT_*
#include <stdio.h> // for puts

int main(void) {
    volatile char *const mapping = mmap(
        nullptr,
        1 /* rounded to page */,
        PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANONYMOUS,
        -1,
        0
    );

    pid_t const child_pid = fork();
    if (child_pid) {
        // parent
        while (true) {
            if (*mapping == 0) {
                puts("I'm the parent!");
                sleep(1);
                *mapping = 1;
            }
        }
    } else {
        // child
        while (true) {
            if (*mapping == 1) {
                puts("I'm the child!");
                sleep(1);
                *mapping = 0;
            }
        }
    }
}
