#include <unistd.h> // for execve, fork, pid_t
#include <stdlib.h> // for exit, EXIT_FAILURE
#include <sys/wait.h> // for waitpid, WIFEXITED, WEXITSTATUS

void exec_or_die(char const *const path, char *const *const argv) {
    execve(path, argv, nullptr /* envp */);
    // execve failed
    exit(EXIT_FAILURE);
}

int wait_for_exit(pid_t const pid) {
    while (true) {
        int wstatus;
        if (waitpid(pid, &wstatus, 0) < 0) {
            // waitpid failed
            exit(EXIT_FAILURE);
        }
        if (WIFEXITED(wstatus)) {
            // child exited
            // return its exit status
            return WEXITSTATUS(wstatus);
        }
    }
}

int main(void) {
    pid_t const fork_rc = fork();
    if (fork_rc < 0) {
        // fork failed
        return EXIT_FAILURE;
    }

    if (fork_rc) {
        // parent
        wait_for_exit(fork_rc);
        // now, child has exited
        char *const argv[] = {"ls", "/", nullptr};
        exec_or_die("/usr/bin/ls", argv);
    } else {
        // child
        exec_or_die("/usr/bin/ls", nullptr);
    }
}
