// Let's write a program to make a thread that repeatedly writes "dave is a cute cat" to stdout,
// while the main thread repeatedly writes "dale is a cute cat"

#include <unistd.h>
#include <threads.h>
#include <string.h>

mtx_t mutex;

int write_forever(void *data) {
    while (true) {
        mtx_lock(&mutex);
        write(STDOUT_FILENO, data, 4);
        char rest[] = " is a cute cat\n";
        write(STDOUT_FILENO, rest, sizeof(rest) - 1);
        mtx_unlock(&mutex);
    }
}

int main(void) {
    mtx_init(&mutex, mtx_plain);
    thrd_t thread;
    thrd_create(&thread, write_forever, "dave");
    write_forever("dale");
}
