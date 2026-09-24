#include <unistd.h> // for syscall
#include <sys/syscall.h> // for SYS_exit

int main(void) {
    syscall(SYS_exit, 55);
}
