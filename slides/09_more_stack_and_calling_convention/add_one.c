#include <stdint.h> // for uint64_t
#include <unistd.h> // for _exit

uint64_t add_one(uint64_t i) {
    return i + 1;
}

int main(void) {
    uint64_t i = 125;
    return add_one(i);
}
