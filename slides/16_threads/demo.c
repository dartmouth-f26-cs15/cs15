// Let's write a program to make a thread that repeatedly writes "dave is a cute cat" to stdout,
// while the main thread repeatedly writes "dale is a cute cat"

#include <threads.h> // for literally everything
#include <unistd.h> // for write, STDOUT_FILENO
#include <stdlib.h> // for exit, EXIT_FAILURE

mtx_t mutex;

int my_epic_function(void *name) {
    static char end_of_msg[] = " is a cute cat\n";
    while (true) {
        if (mtx_lock(&mutex) != thrd_success) {
            exit(EXIT_FAILURE);
        }
        write(STDOUT_FILENO, name, 4);
        write(STDOUT_FILENO, end_of_msg, sizeof(end_of_msg) - 1);
        if (mtx_unlock(&mutex) != thrd_success) {
            exit(EXIT_FAILURE);
        }
    }
}

int main(void) {
    mtx_init(&mutex, mtx_plain);
    thrd_t thread;
    if (thrd_create(&thread, my_epic_function, "dave") != thrd_success) {
        exit(EXIT_FAILURE);
    }
    my_epic_function("dale");
}
