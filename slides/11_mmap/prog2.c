#include <stdio.h> // for printf, getchar, puts

int i;

int main(void) {
    printf("&i: %p\n", &i);
    puts("About to read the value of i. Press any key...");
    getchar();
    printf("i: %d\n", i);
    puts("Press any key to exit.");
    getchar();
}
