#include <unistd.h> // for sleep, write, STDOUT_FILENO
#include <signal.h> // for signal, SIGUSR1, SIGUSR2
#include <stdio.h> // for puts, getchar
#include <stdlib.h> // for EXIT_FAILURE
#include <string.h> // for strlen

void handler(int const signum) {
    static char const msg[] = "Got a signal: ";
    write(STDOUT_FILENO, msg, strlen(msg));
    char const signum_str[] = {'0' + signum / 10, '0' + signum % 10, '\n'};
    write(STDOUT_FILENO, signum_str, sizeof(signum_str));
}

int main(void) {
    signal(SIGUSR1, handler);
    signal(SIGINT, handler);
    signal(SIGKILL, handler);
    puts("Waiting for a signal!");
    while (true) {}
}
