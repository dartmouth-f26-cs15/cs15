#include <unistd.h> // for execve, fork, pid_t
#include <stdlib.h> // for exit, EXIT_FAILURE

void exec_or_die(char const *const path, char *const *const argv) {
    execve(path, argv, nullptr /* envp */);
    exit(EXIT_FAILURE);
}

int main(void) {
    pid_t const fork_rc = fork();
    if (fork_rc < 0) {
        return EXIT_FAILURE;
    }

    if (fork_rc) {
        // parent
        char *const argv[] = {"ls", "/", nullptr};
        exec_or_die("/usr/bin/ls", argv);
    } else {
        // child
        exec_or_die("/usr/bin/ls", nullptr);
    }
}
