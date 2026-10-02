---
geometry: margin=1in
---

# Assignment 02: `utf8`, due Wednesday, October 7 at 11:59:59 PM

Your task in this assignment is to build a simple UTF-8 code point decoder.

During this task, you are permitted to use anything you want from libc, though I don't anticipate that you'll need to use very much of libc for this assignment.
No other libraries are permitted.

Your parser should be exposed through a single function:
```C
size_t parse_utf8(uint8_t const *input, size_t input_len, uint32_t *output);
```

Its arguments are as follows:

- `input`: A pointer to some bytes. These bytes are to be decoded into a sequence of UTF-8 code points.
- `input_len`: The length (in bytes) of `input`.
- `output`: The location where the decoded code points should be written. You may assume that this buffer is big enough to store the result.

Your function should return the length of the code point sequence written into `output`.

You may find the table in the "Description" section of [this Wikipedia page](https://en.wikipedia.org/wiki/UTF-8#Description) helpful.

Your decoder should `exit(EXIT_FAILURE)` whenever the input bytes cannot be decoded, or when decoding them would require accessing `input` out of bounds.

## What to Submit

- `utf8.c`
    - Contains the definition of `parse_utf8`.
- `utf8.h`
    - Contains the declaration for `parse_utf8`.

# Testing

We'll test your code using test harnesses similar to those that we used in the previous assignment.
You should do the same.

For a sense of how your decoder should behave, consider using Python's `str.encode` and `bytes.decode` methods, though these functions will catch some errors related to the decoded code point sequence that your decoder should not.

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
