#include <stdio.h> // for EOF
#include <unistd.h> // for write, STDOUT_FILENO
#include <string.h> // for strlen
#include <stdlib.h> // for malloc, free

int puts(char const *s) {
    size_t const s_len = strlen(s);
    char *s_copy = malloc(s_len + 1);
    for (size_t i = 0; i < s_len; i++) {
        if (s[i] == 's') {
            s_copy[i] = 'z';
        } else if (s[i] == 'e') {
            s_copy[i] = '3';
        } else if (s[i] == 'l') {
            s_copy[i] = '1';
        } else if (s[i] == 't') {
            s_copy[i] = '7';
        } else {
            s_copy[i] = s[i];
        }
    }
    s_copy[s_len] = '\n';
    ssize_t result = write(STDOUT_FILENO, s_copy, s_len + 1);
    free(s_copy);
    return result;
}
