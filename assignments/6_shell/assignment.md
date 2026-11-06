---
geometry: margin=1in
---

# Assignment 6: `shell`, Due Wednesday, November 11

In this assignment, you are tasked with implementing a shell.

Your shell should do this following:

1. Print a little prompt (e.g., `$`, `>`, `[user@host]`).
2. Read a line from `stdin`.
3. If `stdin` is exhausted, make an `exit` syscall with status 0.
4. If the line is a well-formatted `cd` command, appropriately invoke the `chdir` syscall, handle any errors, and go back to step 1.
5. If the line is a well-formatted `exit` command, appropriately invoke the `exit` syscall.
6. If the line is a poorly-formatted `cd` or `exit` command, print an error, and go back to step 1.
7. If the line is empty, go back to step 1.
8. Otherwise, make a new process, try to walk the `PATH` if necessary, and try to `execve`.
9. Wait for the child process to terminate, then go back to step 1.

You are permitted to use any and all functions from libc, except the ones that walk the `PATH` for you.
We recommend against using the `strtok` and `strtok_r` functions; they're more trouble than they're worth.
No other external library code is allowed.

**You must be able to explain your code. If you don't understand a library function, don't call it.**

## Walking the `PATH`

Recall that the first argument to `execve` is the path to the program we want to execute.
Unfortunately, users don't always give us the path to each program they want to execute; they just give us the program's name.
You will find the path to the user's requested program using the `PATH` environment variable, which you can access with a call to `getenv(3)`.
The content of `PATH` is a colon-delimited sequence of filesystem paths.
You'll try to `execve` the user's requested program from each one, until one of the `execve`s succeeds, or you reach the end of the list.

For example, suppose that the user types `ls` into your shell, and the `getenv("PATH")` returns `"/abc:/whatever:/bin"`.
Then, your shell's child process will try to issue an `execve` with first argument `"/abc/ls"`.
If that fails, then it will issue an `execve` with first argument `"/whatever/ls"`.
If that fails, then it will issue an `execve` with first argument `"/bin/ls"`.
If that fails, then an error will be printed, and the child process should exit with a nonzero status.

Note that sometimes, the user *does* pass a path directly to the shell.
In that case, you should *not* walk the `PATH`; just try to `execve` whatever the user entered.
As a shortcut, you may assume that a string is a path (so you can just `execve` it) if it contains a `/`.

## Handling Ctrl-C

When the user presses Ctrl-C, the shell should not die, but the running process should receive `SIGINT` (and thus probably die).

e.g., when the user runs `sleep 10` in your shell, then presses Ctrl-C after 1 second, the user should be dropped back into the shell prompt.

Hint \#1: `WIFEXITED` will not be true for a process that is killed by a signal. Instead, you'll want to check `WIFSIGNALED`.
Hint \#2: implementing this section should require no more than 3 lines of code.

## Handling Errors

In general, if the user can cause your shell to crash by typing stuff, that's bad.

It's okay to fatally error when library functions like `malloc` or `fork` fail, because that indicates a lack of system resources.
On the other hand, if an `execve` fails, it's probably because the user entered something invalid, so you should print a useful error and your shell should not crash.

## Simplifying Assumptions

You may assume that

1. A user does not pass an `argv` with more than 255 entries.
2. You don't need to pass environment variables to `execve`.
3. Quoting doesn't matter.
4. Backslash-escape sequences don't matter.
5. A well-formatted `cd` command takes exactly 1 argument.
6. A well-formatted `exit` command takes exactly 0 arguments.
7. The `PATH` won't contain empty segments (i.e., 2 `:`s in a row)

## Example Usage

```
[bkallus@plink ~] ./shell
$ echo hello students!
hello students!
$ cd /fakedirectory
cd failed!
$ fakeprogram with fake arguments
program not found! :(
$ /bin/ls /
afs  boot  etc	 lib	media  opt   root  sbin  sys  usr
bin  dev   home  lib64	mnt    proc  run   srv	 tmp  var
$ ls /
afs  boot  etc	 lib	media  opt   root  sbin  sys  usr
bin  dev   home  lib64	mnt    proc  run   srv	 tmp  var
$ cat /etc/fedora-release
Fedora release 44 (Forty Four)
$ exit
[bkallus@plink ~]
```

## What to Submit

A single file named `shell.c`, that implements your shell when compiled and run.

# Use of External Resources

Feel free to use whatever external sources you want, **so long as every
keystroke in your submission is your own.** That is to say, asking
ChatGPT (or StackOverflow, or friends) for help is fine, but
copy-pasting someone (or something) else's code into your submission is
not.

**You are expected to thoroughly and completely understand all code that
you submit.** Your understanding will be assessed during a live,
in-person interview with the course staff, which will count for a
significant portion of your grade.
