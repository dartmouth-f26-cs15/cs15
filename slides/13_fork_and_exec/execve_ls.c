#include <unistd.h> // for execve
#include <stdio.h> // for puts

int main(void) {
    char *argv[] = {"ls", "-l", nullptr};
    execve("/usr/bin/ls", argv, nullptr);

    puts("Done with ls!");
    return 123;
}
