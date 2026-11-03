#include <unistd.h>
#include <stdio.h>

int main(void) {
    char *argv[] = {"ls", "-l", NULL};
    execve("/usr/bin/ls", argv, NULL);

    puts("Done with ls!");
    return 123;
}
