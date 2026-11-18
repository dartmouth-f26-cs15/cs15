#include <stdlib.h> // for strtoull, exit, EXIT_SUCCESS
#include <signal.h> // for signal, SIGSEGV

void signal_handler(int) {
    exit(EXIT_SUCCESS);
}

int main(int const argc, char const *const *const argv) {
    signal(SIGSEGV, signal_handler);
    unsigned long long const input = strtoull(argv[1], nullptr, 16);
    *(char *)input = 'a';
    return EXIT_FAILURE;
}
