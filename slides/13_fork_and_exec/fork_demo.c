#include <unistd.h> // for fork, pid_t
#include <stdio.h> // for puts, printf

int main(void) {
    pid_t pid = fork();
    // Starting here, 2 different processes are executing this code
    if (pid == 0) {
        puts("I'm the child!");
    } else {
        puts("I'm the parent!");
        printf("My child's PID is %d\n", pid);
    }

    puts("Exiting...");
}
