#include <unistd.h> // for syscall

int main(void) {
    syscall(60, 55);
}
