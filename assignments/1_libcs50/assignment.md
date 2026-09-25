---
geometry: margin=1in
---

# Assignment 1: `libcs50`, due Wednesday, September 30 at 11:59:59 PM

Your task in this assignment is to build a library, `libcs50.a`, that implements a few useful functions from libc.

During this task, you are not permitted to use any externally-defined functions except `syscall`, but using types and constants defined in system header files is permitted.

You do not need to properly handle errors that may result from system calls that you make, and you shouldn't worry about correctly setting `errno`.

Your library should globally define **only** the following functions (all other function definitions must be `static`):

- `char *cs50_strcat(char *dst, char const *src)`
    - See `man 3 strcat` for the expected behavior of this function.
- `int cs50_strcmp(char const *s1, char const *s2)`
    - See `man 3 strcmp` for the expected behavior of this function.
- `char *cs50_strcpy(char *dst, char const *src)`
    - See `man 3 strcpy` for the expected behavior of this function.
- `size_t cs50_strlen(char const *s)`
    - See `man 3 strlen` for the expected behavior of this function.
- `char *cs50_strncpy(char *dst, char const *src, size_t dsize)`
    - See `man 3 strncpy` for the expected behavior of this function.
- `int cs50_close(int fd)`
    - See `man 2 close` for the expected behavior of this function.
- `void cs50_exit(int status)`
    - See `man 3 exit` for the expected behavior of this function.
- `int cs50_getchar(void)`
    - See `man 3 getchar` for the expected behavior of this function.
    - Your implementation should properly handle reaching the end of the file.
- `int cs50_open(char const *pathname, int flags, mode_t mode)`
    - See `man 2 open` for the expected behavior of this function.
    - Even though the `open` man page shows the `mode` argument as optional, you should make it required.
- `int cs50_puts(char const *s)`
    - See `man 3 puts` for the expected behavior of this function.
- `ssize_t cs50_read(int fd, void *buf, size_t count)`
    - See `man 2 read` for the expected behavior of this function.
- `ssize_t cs50_write(int fd, void const *buf, size_t count)`
    - See `man 2 write` for the expected behavior of this function.

- `void cs50_print_ulong_dec(unsigned long i)`
    - This function should write the value of `i`, in base 10, to `stdout`.
    - (You may assume that any `write` system calls do not error)
- `void cs50_print_ulong_hex(unsigned long i)`
    - This function should write the value of `i`, in base 16, to `stdout`.
    - (Use the digits 0123456789abcdef)
    - (You may assume that any `write` system calls do not error)
- `void cs50_print_ulong_bin(unsigned long i)`
    - This function should write the value of `i`, in base 2, to `stdout`.
    - (You may assume that any `write` system calls do not error)

You may find these system header files useful:

- `<stddef.h>`
    - Constants: `NULL`
    - Types: `size_t`
- `<sys/types.h>`
    - Types: `mode_t`, `ssize_t`
- `<sys/syscall.h>`
    - Constants: `SYS_close`, `SYS_write`, `SYS_read`, `SYS_exit`, `SYS_open`
- `<unistd.h>`
    - Constants: `STDOUT_FILENO`, `STDIN_FILENO`
    - Functions: `syscall`. However, in order to get `syscall` from this header file, you'll need to `#define` `_GNU_SOURCE` before the first `#include` in your program. This is because making raw system calls using `syscall` is not portable. By `#define`-ing `_GNU_SOURCE`, you are telling the libc that you do not care about portability to non-GNU/Linux systems.

## What to Submit

- `close.c`
    - Contains your implementation of `cs50_close`.
- `exit.c`
    - Contains your implementation of `cs50_exit`.
- `getchar.c`
    - Contains your implementation of `cs50_getchar`.
- `open.c`
    - Contains your implementation of `cs50_open`.
- `puts.c`
    - Contains your implementation of `cs50_puts`.
- `read.c`
    - Contains your implementation of `cs50_read`.
- `strcat.c`
    - Contains your implementation of `cs50_strcat`.
- `strcmp.c`
    - Contains your implementation of `cs50_strcmp`.
- `strcpy.c`
    - Contains your implementation of `cs50_strcpy`.
- `strlen.c`
    - Contains your implementation of `cs50_strlen`.
- `strncpy.c`
    - Contains your implementation of `cs50_strncpy`.
- `print.c`
    - Contains your implementation of `cs50_print_ulong_dec`, `cs50_print_ulong_hex`, and `cs50_print_ulong_bin`.
- `write.c`
    - Contains your implementation of `cs50_write`.
- `libcs50.h`
    - Contains declarations of all of the functions listed above.

## Testing

We will test your library by first building each `.c` file into an object (`.o`) file as follows:
```sh
for c_file in {close,exit,getchar,open,puts,read,strcat,strcmp,strcpy,strlen,strncpy,print,write}.c; do
    gcc -fsanitize=address,undefined -ggdb -O0 -Wall -Wextra -Wpedantic -Wvla -c "$c_file"
done
```

We will then combine those object files into a static library, `libcs50.a` as follows:
```sh
ar -rs libcs50.a {close,exit,getchar,open,puts,read,strcat,strcmp,strcpy,strlen,strncpy,print,write}.o
```

After that, we'll link the static library with a testing harness (`test.c`) to produce an executable.

Our testing harness looks like this:
```C
#include "libcs50.h"

int main(void) {
    // A bunch of tests for your library that
    // check whether your functions' behaviors
    // match the behaviors of their counterparts
    // in glibc.
}
```

We will compile our testing harness (`test.c`) and link it with your static library (`libcs50.a`) to produce an executable (`test`) as follows:
```sh
gcc -fsanitize=address,undefined -ggdb -O0 -Wall -Wextra -Wpedantic -Wvla test.c libcs50.a -o test
```

We'll then run that executable and use its output to grade your submission.

You might consider writing your own `test.c` and using this same process to test your code.

# Use of External Resources

Feel free to use whatever external sources you want, including LLMs, forums, Q&A websites, friends, and so on, **so long as every keystroke in your submission is your own.**
That is to say, asking ChatGPT (or StackOverflow, or friends) for help is fine, but copy-pasting someone (or something) else's code into your submission is not.

**You are expected to thoroughly and completely understand all code that you submit.**
Your understanding will be assessed during a live, in-person interview with the course staff, which will count for a significant portion of your grade.

# Grading

This assignment's grade will come from 3 things:

## 1. Correctness

The correctness grade is determined by the result of our testing harness, which is described in the previous section of this document.
If the harness outputs that your code is free of errors, then your submission will receive a 100% correctness grade.

## 2. Style

The style grade is determined by 2 factors:
1. Whether your code has consistent style (which is nearly guaranteed if you use `clang-format`)
2. Whether your code looks good to me. This is ultimately subjective, so this won't count for much, unless you do something truly egregious.

## 3. Interview

During the X-hour, you will sit down with a member of the course staff for a 5-10 minute interview.
It should be very easy to receive a 100% interview grade if you wrote your program without external help.
If there a few small parts of your program that you cannot adequately explain, you'll get no more than a 50% for this part of the grade.
If there are significant parts of your program that you cannot adequately explain, you'll receive a 0% for this part of the grade, and may face consequences for violating the academic honor principle.
