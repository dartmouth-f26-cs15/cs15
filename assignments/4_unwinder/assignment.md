---
geometry: margin=1in
---

# Assignment 04: `unwind`, Due Wednesday, Oct 21st

Your task in this assignment is to write an *ABI-compliant* function `unwind` in x86-64 assembly that prints a *backtrace* to stdout.
- A backtrace shows a sequence of function calls that lead to the current function. It is called a backtrace because it traces back all function calls, going back up the "call stack".

Your function should print all of the saved return addresses on the stack, separated by newlines, in hex, prefixed with "`0x`", and padded with `0`s to 16 characters in length (18, if you count the "`0x`").

You are not permitted to call any external functions in your assembly program, but you can make any syscalls that you want.

Hints:
- Think about the stack layout and what happens when a series of functions is called.
- Pay attention to ABI rules and to the calling convention.

## What to Submit

- `unwind.s`
    - Contains your implementation of `unwind`.
    - `unwind` should be the only function declared `.globl` in `unwind.s`.
- `unwind.h`
    - Contains a declaration of `unwind` so that it is callable from C.

## Testing

We will test your unwinder by first building `unwind.s` into an object (`.o`) file as follows:
```sh
gcc -c unwind.s -o unwind.o
```

Then, we'll link the object file with a testing harness (`test.c`) to produce an executable.

Our testing harness looks like this:
```C
#include "unwind.h"

int main(void) {
    // A bunch of tests for your unwinder, which
    // we will not show you :)
}
```

We will compile our testing harness (`test.c`) and link it with your object file to produce an executable (`test`) as follows:
```sh
gcc -fsanitize=address,undefined -Wall -Wextra -Wpedantic -Wvla -Wshadow test.c unwind.o -o test
```

We'll then run that executable and use its output to grade your submission.

You might consider writing your own `test.c` and using this same process to test your code.

\pagebreak

# Use of External Resources

Feel free to use whatever external sources you want, **so long as every keystroke in your submission is your own.**
That is to say, asking ChatGPT (or StackOverflow, or friends) for help is fine, but copy-pasting someone (or something) else's code into your submission is not.

**You are expected to thoroughly and completely understand all code that you submit.**
Your understanding will be assessed during a live, in-person interview with the course staff, which will count for a significant portion of your grade.

# Grading

This assignment's grade will come from 3 things:

## 1. Correctness

The correctness grade is determined by the result of our testing harness, which is described in the previous section of this document.
You can run the testing harness at any time by executing `TODO`.
If the harness outputs that your code is free of errors, then your submission will receive a 100% correctness grade.

## 2. Style

The style grade is determined by the output of the linter, which you can run at any time by executing `TODO`.
If this command outputs that your code is free of stylistic errors, then your submission will receive a 100% style grade.

## 3. Interview

During the X-hour, you will sit down with a member of the course staff for a 5-10 minute interview.
It should be very easy to receive a 100% interview grade if you wrote your program without external help.
If there a few small parts of your program that you cannot adequately explain, you'll get no more than a 50% for this part of the grade.
If there are significant parts of your program that you cannot adequately explain, you'll receive a 0% for this part of the grade, and may face consequences for violating the academic honor principle.
