---
geometry: margin=1in
---

# Assignment 03: `xdump`, due Wednesday, October 14 at 11:59:59 PM

In this assignment, your task is to write a Linux x86_64 assembly program named `xdump` (with `_start` as the entry point) that does the following:
1. If an argument is p[assed on `argv`, treat it as a file name and `open` it. If `open` fails, `exit` with status 1.
2. Read this file one byte at a time, and write to stdout the contents of the file, in hex, separated by spaces.
3. Every 16 bytes, write a newline character.
4. If no argument is passed, do the same thing, but read from stdin.

Remember to comment your code! (Comments in GNU `as` are just like in Python; use `#`)

## Example 1.

If `test.txt` contains the bytes `0123456789abcdefg`, then
```
./xdump test.txt
```
should produce
```
30 31 32 33 34 35 36 37 38 39 61 62 63 64 65 66
67
```

## Example 2.

```
echo 'dave and dale are some pretty cool cats :)' | ./xdump
```
should produce
```
64 61 76 65 20 61 6e 64 20 64 61 6c 65 20 61 72
65 20 73 6f 6d 65 20 70 72 65 74 74 79 20 63 6f
6f 6c 20 63 61 74 73 20 3a 29 0a
```
Note the `0a` byte on the end, which `echo` automatically inserts.

## What to Submit

- `xdump.s`

# Testing

We'll test your code using test harnesses similar to those that we used in the previous assignment.
You should do the same.

For a sense of how your decoder should behave, consider using the `hexdump -C` command on Plink, which does a superset of the things you need to do in this assignment.

# Use of External Resources

Feel free to use whatever external sources you want, including LLMs, forums, Q&A websites, friends, and so on, **so long as every keystroke in your submission is your own.**
That is to say, asking for help is fine, but copy-pasting someone (or something) else's code into your submission is not.

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
