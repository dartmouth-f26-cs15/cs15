---
geometry: margin=0.5in
---

# Debugging Activity

I have placed an executable file named `mystery` into each of your home directories.

## Question 1

Suppose that `mystery` is run as follows:
```sh
printf '9' | ./mystery
```

What is the value in `rax` just before the first execution of the `cmp` instruction?

# Question 2

Suppose that `mystery` is run as follows:
```sh
printf 'A' | ./mystery
```

What is the value in `rax` just before the fifteenth execution of the `shr` instruction?

## Question 3

Suppose that `mystery` is run as follows:
```sh
printf '\x53' | ./mystery
```

If you add 0x40 to `rax` just before the $100^\text{th}$ execution of the `cmp` instruction, then continue the execution of the program, what is the exit status of the program?
