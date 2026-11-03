#include <unistd.h> // for fork, pid_t
#include <stdio.h> // for printf
#include <string.h> // for strlen

void print_string(char const *const s) {
    write(STDOUT_FILENO, s, strlen(s));
}

int main(void) {
    pid_t pid = fork();
    // Starting here, 2 different processes are executing this code
    if (pid == 0) {
        print_string("I'm the child!\n");
    } else {
        print_string("I'm the parent!\n");
        printf("My child's PID is %d\n", pid);
    }

    print_string("Exiting...\n");
}
