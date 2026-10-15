#include <stdio.h> // for printf
#include <stdlib.h> // for strtoull
#include "add_2.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <num>\n", argv[0]);
        return -1;
    }
    printf("%ld\n", add_2(strtoull(argv[1], NULL, 10)));
}
