---
geometry: margin=1in
---

# Assignment 04: `rettrace`, Due Wednesday, October 21

Your task in this assignment is to write a function `rettrace` in x86-64 assembly that prints a rettrace to stdout.
That is, your function should print all of the saved return addresses on the stack, separated by newlines, in hex, prefixed with "`0x`", and padded with `0`s to 16 characters in length (18, if you count the "`0x`").

Your function should be callable from C, which means it must follow the rules specified in the "Calling Assembly from C" slide from Thursday's class.

You are not permitted to call any external functions in your assembly program, but you can make any syscalls that you want.

You should assume that register `rbp` is used as described during class (i.e., as a base pointer).

Hints:
- This assignment requires deep understanding of the stack (including key stack-related instructions like `push`, `pop`, `call`, `ret`).
- The core loop of your submission shouldn't be very much code.

## What to Submit

- `rettrace.s`
    - Contains your implementation of `rettrace`.
    - `rettrace` should be the only function declared `.global` in `rettrace.s`.
- `rettrace.h`
    - Contains a declaration of `rettrace` so that it is callable from C.

\newpage

## Example Usage

Suppose that we have the following C program in a file named `test.c`:
```c
#include "rettrace.h"

void f(void) {
    rettrace();
}

int main(void) {
    f();
}
```

When you're done with the assignment, you should be able to compile this program as follows:
```
gcc test.c rettrace.s
```

When you run `./a.out`, you should see a sequence of addresses:
```
0x0000000000402f7e
0x0000000000402f8a
0x00000000004037a1
0x0000000000405def
0x0000000000402e65
```

You can confirm that this is the correct result using GDB:
```
$ gdb ./a.out
...
(gdb) starti
...
(gdb) x/1i 0x0000000000402f7e
   0x402f7e <f+9>:	nop
(gdb) x/1i 0x0000000000402f8a
   0x402f96 <main+9>:	mov    eax,0x0
(gdb) x/1i 0x00000000004037a1
   0x4037c1 <__libc_start_call_main+113>:	mov    edi,eax
(gdb) x/1i 0x0000000000405def
   0x405def <__libc_start_main_impl+751>:	mov    eax,0x7f85
(gdb) x/1i 0x0000000000402e65
   0x402e65 <_start+37>:	hlt
```

In other words, by e**X**amining **1** **I**nstruction from each of these addresses, we can see that they come from the following functions, in order:

- `f`,
- `main`,
- `__libc_start_call_main`,
- `__libc_start_main_impl`,
- `_start`.

That's the right rettrace! `_start` called `__libc_start_main_impl`, which called `__libc_start_call_main`, which called `main`, which called `f` (which called `rettrace`).

# Use of External Resources

Feel free to use whatever external sources you want, **so long as every keystroke in your submission is your own.**
That is to say, asking ChatGPT (or StackOverflow, or friends) for help is fine, but copy-pasting someone (or something) else's code into your submission is not.

**You are expected to completely understand all code that you submit.**
Your understanding will be assessed during a live, in-person interview with the course staff, which will count for a significant portion of your grade.

# Grading

This assignment's grade will come from 3 things:

## 1. Correctness

The correctness grade is determined by the result of our testing harness.
If the harness outputs that your code is free of errors, then your submission will receive a 100% correctness grade.

## 2. Style

The style grade is determined by 2 factors:

1. Whether your code has consistent style (which is nearly guaranteed if you use `clang-format`)
2. Whether your code looks good to me. This is ultimately subjective, so this won't count for much, unless you do something truly egregious.

## 3. Interview

During the X-hour, you will sit down with a member of the course staff for a 5-10 minute interview.
It should be very easy to receive a 100% interview grade if you wrote your program without external help.
If there parts of your program that you cannot adequately explain, you'll get no more than a 50% for this part of the grade.
If there are significant parts of your program that you cannot adequately explain, you'll receive a 0% for this part of the grade, and may face consequences for violating the academic honor principle.
