---
geometry: margin=1in
---

# More C!

Here are some more C concepts that we haven't talked about yet, but are still important to know.

## The `switch` Statement

A `switch` statement is a shorthand syntax for an `if`-`else` chains that repeatedly checks the same value for equality.

For example, the following two C snippets are equivalent:
```c
if (x == 0 || x == 1) {
    c = 'a';
} else if (x == 2) {
    c = 'b';
} else {
    c = 'c';
    puts("got to the else!");
}
```

```c
switch (x) {
    case 0:
    case 1:
        c = 'a';
        break;
    case 2:
        c = 'b';
        break;
    default:
        c = 'c';
        puts("got to the else!");
        break;
}
```

You should think of `switch` `case`s as labels; they will fall through to each other by default.
To get around this, place `break` statements between them.
This is often the cause of bugs, but it can be useful!
Note that we don't need to duplicate that code for the `0` and `1` cases because the `0` case falls through into the `1` case.
The special `default` case always runs if none of the cases before it have.

## The `?:` Operator

The `?:` operator is shorthand syntax for `if` and `else`.

For example, the following two C snippets are equivalent:
```c
int x;
if (y > 5) {
    x = 1;
} else {
    x = 25;
}
```

```c
int x = y > 5 ? 1 : 25;
```
That is, the syntax is `condition ? true_value : false_value`.

## Pre-increment and Post-increment

The `++` operator behaves a little differently depending on whether it's placed before its operand, or after.

For example,
```c
int i = 0;
int j = i++;
// Now i is 1 and j is 0.
```

```c
int i = 0;
int j = ++i;
// Now i is 1 and j is 1.
```

In other words, `i++` increments `i`, but it evaluates to the original value of `i`.
Similarly, `++i` increments `i`, but it evaluates to the new value of `i`.

## Preprocessor Macros

The C preprocessor embeds a language for writing "macros:" functions that manipulate your source code before the compiler runs.
Usually, macros are *not the right tool for the job*.
Avoid them when possible.
However, if you want to call yourself a "C programmer," you should have some exposure to this concept.

There are two kinds of macros: constant macros, and function-like macros.

Constant macros are pretty straightforward.
Here's an example:
```c
#define WHATEVER 5

int main(void) {
    return WHATEVER; // returns 5
}
```

When the preprocessor runs (i.e., before compilation), it will replace the `WHATEVER` in `main` with `5`.
Simple enough.

Function-like macros are more complex.
Here's an example:
```c
#define MIN(a, b) a <= b ? a : b

int main(void) {
    return MIN(1, 2); // returns 1
}
```

Function-like macros are extremely hard to use correctly.
Some people believe that there is a performance benefit to using a function-like macro instead of a short function.
This is not true when compiler optimization is enabled.

For example, here are two ways to get the macro above to misbehave:
```c
int i = 0;
MIN(++i, 1);     // Technically UB. Evaluates to 2 on my machine.
MIN(0 & 0xff, 1) // Evaluates to 1.
```

So, to reiterate, just don't use function-like macros; they're too easy to mess up.
Write regular functions instead.

## `#include` Guards

Recall that the purpose of `#pragma once` is to prevent a header file from being `#include`d twice in the same translation unit.
This is used to prevent repeated definition of data in a header file.
Although `#pragma once` is widely supported, it isn't standardized.

If you want to stick to purely standard C, you would insert the following at the beginning and end of a header file:
```c
#ifndef SOME_UNIQUE_NAME
#define SOME_UNIQUE_NAME

// Your header file stuff goes here

#endif
```

These three directives tell the preprocessor to check if a macro named `SOME_UNIQUE_NAME` is defined.
If it isn't, define it (to the empty string), and emit the header file as-is.
If it is, then this header file has been `#include`d before, so emit nothing.

## Sanitizers

It's easy to make mistakes in C that pass silently at runtime.
For example, a stack buffer overflow or a use-after-free might have no effect, or silently corrupt your program's state.
Sanitizers are compiler passes that add runtime checks to your programs.

For example, if you run the following program on Plink, you probably won't get a crash:
```c
int main(void) {
    char c[1];
    return c[1];
}
```

If you recompile the above code with `clang -fsanitize=address,undefined` and rerun it, you should see an error like this:
```
test.c:3:13: runtime error: index 1 out of bounds for type 'char [1]'
=================================================================
ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7b83062f0021
READ of size 1 at 0x7b83062f0021 thread T0
    #0 0x5593289792a1 in main
    #1 0x7f8308a27780  (/usr/lib/libc.so.6+0x27780)
    #2 0x7f8308a278b8 in __libc_start_main
    #3 0x5593289790e4 in _start

Address 0x7b83062f0021 is located in stack of thread T0 at offset 33 in frame
    #0 0x5593289791c8 in main

  This frame has 1 object(s):
    [32, 33) 'c' (line 2) <== Memory access at offset 33 overflows this variable
```

Sanitizers can catch integer overflow, invalid bitshifts, memory leaks, and a whole lot more stuff.
We highly recommend using them to test your code.

## `volatile`

Compiler optimizations are smart.
For example, look at how `clang` optimizes this program at `-O2`:
```c
#include <stddef.h> // for size_t
int main(void) {
    char a[256];
    for (size_t i = 0; i < 256; i++) {
        a[i] = i;
    }
    return 5;
}
```

```asm
.intel_syntax noprefix

main:
    mov eax, 0x5
    ret
```

Our array (and loop) are gone!
This makes sense, because our loop doesn't really do anything; it writes values into an array, but nothing ever reads those values.

If you want to tell the compiler that accesses to an object must go out to memory, use the `volatile` keyword.
For example,
```c
#include <stddef.h> // for size_t
int main(void) {
    volatile char a[256];
    for (size_t i = 0; i < 256; i++) {
        a[i] = i;
    }
    return 5;
}
```

Now, the `char`s in the array are `volatile`, so the loop won't be optimized out.

## `register`

The `register` keyword allows you to inform the compiler that a variable will never have its address taken.

That is, the following code will not compile:
```
int main(void) {
    register int i;
    &i;
}
```

This is almost never useful.
Notably, this keyword **does not** ensure that the variable is stored in a register.

## `static`

The `static` keyword is basically like `private` in Java or C++.
It's how you inform the compiler not to make a symbol `.global` in the resulting assembly.

## `inline`

This one is complicated.
For now, don't worry about what it means; just know that a function declared `inline` will not always be inlined by the compiler.
(If you want to learn what this means, take compilers.)

## Implicit Concatenation of String Literals

The following are equivalent:
```c
char s[] = "abc";
```

```c
char s[] = "a" "b" "c";
```

Note that is is only true for *string literals*.
The following code does not compile:
```c
char a[] = "a";
char s[] = a "bc"; // Compiler error!! `a` is not a string literal.
```
