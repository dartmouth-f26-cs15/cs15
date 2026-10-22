#include <stdio.h> // for printf, getchar, puts

int i = 0;

int main(void) {
    printf("&i: %p\n", &i);
    puts("About to set i=10. Press any key...");
    getchar();
    i = 10;
    puts("Just changed i to 10! Press any key to exit.");
    getchar();
}
