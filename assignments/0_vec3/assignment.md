---
geometry: margin=1in
---

# Mini Assignment 0: `vec3`
## Due Wednesday, September 23 at 11:59:59 PM

Your task in this assignment is to build a simple 3D vector library based on the following struct:
```C
struct vec3 {
    int x;
    int y;
    int z;
};
```

Your library should globally define **only** the following functions (i.e., all other function definitions should be `static`):

- `int vec3_eq(struct vec3 a, struct vec3 b)`
    - Returns 1 iff the two vectors' corresponding fields are all equal. Otherwise, returns 0.
- `struct vec3 vec3_add(struct vec3 a, struct vec3 b)`
    - Returns the componentwise sum of `a` and `b`.
- `int vec3_dot(struct vec3 a, struct vec3 b)`
    - Returns the dot product of `a` and `b`.
- `struct vec3 vec3_scalar_mul(int n, struct vec3 v)`
    - Returns the product of the vector `v` by the scalar `n`.
- `struct vec3 vec3_cross(struct vec3 a, struct vec3 b)`
    - Returns `a` $\times$ `b`, the cross product of `a` and `b`.

You are not permitted to use any external functions in this assignment.
That means your `vec3.h` cannot contain any `#include`s, and your `vec3.c` cannot contain any `#include`s except for `#include "vec3.h"`.

You do not need to handle integer overflow or underflow.

## Submitting

Leave your submission in a directory named `vec3` within your home directory.

Your `vec3` directory should contain the following two files, and no other files:
- `vec3.c`
    - Contains implementations of all of the functions listed above.
- `vec3.h`
    - Contains declarations of all of the functions listed above, as well as the definition of `struct vec3`.

## Testing

We will test your library by first compiling it as follows:
```sh
gcc -fsanitize=address,undefined -ggdb -O0 -Wall -Wextra -Wpedantic -Wvla -c vec3.c -o vec3.o
```

A quick explanation of these flags:

- `-fsanitize=address,undefined`
    - Causes your program to crash when certain error conditions occur, instead of silently misbehaving. This flag should not be used in production, but is useful for debugging.
- `-ggdb`
    - Adds debugging information to the compiler's output, which makes it easier for us to diagnose problems in your code.
- `-O0`
    - Disables compiler optimizations, which can make debugging more difficult.
- `-Wall -Wextra -Wpedantic -Wvla`
    - Enables warnings for common mistakes. We expect your code to compile without warnings.
- `-c`
    - Instructs the compiler to produce an object (`.o`) file instead of attempting to create an executable, which would fail because `vec3.c` does not define a `main`.
- `-o vec3.o`
    - Instructs the compiler to name its output `vec3.o`.

After we compile your code into an object file, we'll combine the object file with a testing harness (`test.c`) to produce an executable.

Our testing harness looks like this:
```C
#include "vec3.h"

int main(void) {
    // A bunch of tests for your library, which
    // we will not show you :)
}
```

We will compile our testing harness (`test.c`) and link it with your object file (`vec3.o`) to produce an executable (`test`) as follows:
```sh
gcc -fsanitize=address,undefined -ggdb -O0 -Wall -Wextra -Wpedantic -Wvla test.c vec3.o -o test
```

We'll then run that executable and use its output to grade your submission.

You might consider writing your own `test.c` and using this same process to test your code.

\pagebreak

# Use of External Resources

Feel free to use whatever external sources you want, including LLMs, forums, Q&A websites, friends, and so on, **so long as every keystroke in your submission is your own.**
That is to say, asking an LLM (or StackOverflow, or friends) for help is fine, but copy-pasting someone (or something) else's code into your submission is not.

**You are expected to thoroughly and completely understand all code that you submit.**
Your understanding will be assessed during a live, in-person interview with the course staff, which will count for a significant portion of your grade.

# Grading

This assignment's grade will come from 3 things:

## 1. Correctness

The correctness grade is determined by the result of our testing harness, which is described in the previous section of this document.
We will not share the tests with you, so make sure to thoroughly test your code before submitting.
If the harness outputs that your code is free of errors, then your submission will receive a 100% correctness grade.

## 2. Style

The style grade is determined by 2 factors:
1. Whether your code has consistent style (which is nearly guaranteed if you use `clang-format`)
2. Whether your code looks good to me. This is ultimately subjective, so this won't count for much, unless you do something truly egregious.

## 3. Interview

After you submit, we'll schedule a 5-10 minute interview.
It should be very easy to receive a 100% interview grade if you wrote your program without external help.
If there parts of your program that you cannot adequately explain, you'll get no more than a 50% for this part of the grade.
If there are significant parts of your program that you cannot adequately explain, you'll receive a 0% for this part of the grade, and may face consequences for violating the academic honor principle.
