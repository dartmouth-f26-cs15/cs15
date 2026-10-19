#include <stddef.h> // for size_t
#include <stdio.h> // for printf

size_t double_char(char const c) {
    size_t result = c * 2;
    return result;
}

size_t f(char const * const s, size_t const size) {
    size_t result = 0;
    for (size_t i = 0; i < size; i++) {
        result += double_char(s[i]);
    }
    return result;
}


int main(void) {
    static char const s[] = "hunter2hunter2";
    size_t result = f(s, sizeof(s));

    printf("result = %zu\n", result);
}
