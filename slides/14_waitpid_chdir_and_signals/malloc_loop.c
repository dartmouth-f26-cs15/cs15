#include <stdlib.h> // for malloc, free
#include <sys/signal.h> // for signal, SIGINT

void signal_handler(int) {
    void *p0 = malloc(1);
    void *p1 = malloc(1);
    free(p0);
    free(p1);
}

int main(void) {
    signal(SIGINT, signal_handler);
    while (true) {
        free(malloc(1));
    }
}
