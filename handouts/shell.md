---
geometry: margin=1in
---

# Commands

## SSH

### `ssh-keygen`
    - Purpose: Generates an SSH keypair.
### `ssh`
    - Purpose: Provides shell access to a remote system.
    - Example: `ssh bkallus@plink.cs.dartmouth.edu`
    - Flags:
        - `-i some_private_key`
            - Uses the specified private key (identity file) instead of the default private key.
### `scp`
    - Purpose: Copies files to and from remote systems.
    - Example: `scp bkallus@plink.cs.dartmouth.edu:cs15/handouts/shell.md .`
        - Copies this file from Plink to my local machine.
        - Note that this must be run from your laptop's shell, not on Plink.

## Filesystem Interaction

### `cd`
    - Purpose: Changes your current working directory.
    - Example: `cd ./slides`
### `ls`
    - Purpose: Lists the files in the current working directory.
    - Flags:
        - `-a`
            - Shows hidden files.
        - `-l`
            - Shows extra information, such as last-modified date, file size, and file permissions.
### `cp`
    - Purpose: Copies files
    - Example: `cp example.txt copy_of_example.txt`
    - Flags:
        - `-r`
            - Needed when copying directories. By default, `cp` only copies plain files, not directories.
### `mv`
    - Purpose: Moves and/or renames files.
    - Example: `mv some_file.txt ../`
        - Moves a `some_file.txt` into the parent directory
    - Example: `mv some_file.txt some_file_with_a_new_name.txt`
        - Renames `some_file.txt` to `some_file_with_a_new_name.txt`
### `pwd`
    - Purpose: Displays your current working directory.
### `rm`
    - Purpose: Deletes files
    - Example: `rm some_file.txt`
### `rmdir`
    - Purpose: Deletes empty directories
    - Example: `rmdir some_empty_directory`

### Git

### `git clone`
    - Purpose: Copies a remote Git repostiory to the current working directory
    - Example: `git clone https://github.com/dartmouth-f26-cs15`
### `git pull`
    - Purpose: Fetches and merges the latest changes to a Git repository from a remote Git server.

## Typesetting

### `pandoc`:
    - Purpose: Compiles Markdown documents to various file formats.
    - Example: `pandoc -i shell.md -o shell.pdf`
    - Flags:
        - `-i some_input_file.md`
            - Specifies the input file
        - `-o some_output_file.pdf`
            - Specifies the output file
### `lualatex`:
    - Purpose: Compiles LaTeX documents to PDF.
    - Example: `lualatex -shell-escape todays_class_slides.tex`
    - Flags:
        - `-shell-escape`
            - Required for use of the `minted` plugin, which I use to syntax highlight the code in the slides.

## C Programming

### `gcc`, `clang`
    - Purpose: Compiles C programs.
    - Example: `gcc test.c`
    - Flags:
        - `-o some_output_file`
            - Specifies the desired file name of the resulting executable. Defaults to `a.out`.
        - `-Wall -Wextra -Wpedantic -Wvla -Wshadow`
            - Enables useful compiler warnings
        - `-fsanitize=address,undefined`
            - Enables AddressSanitizer and UndefinedBehaviorSanitizer
        - `-ggdb`
            - Adds extra debugging information.
        - `-O0`
            - Disables compiler optimizations.
        - `-O1`
            - Enables some compiler optimizations.
        - `-O2`
            - Enables more compiler optimizations.
        - `-O3`
            - Enables even more compiler optimizations.
        - `-c`
            - Instructs the compiler driver to skip linking.
        - `-S`
            - Instructs the compiler driver to skip preprocessing and compilation. (i.e., to only assemble and link)
        - `-E`
            - Instructs the compiler driver to skip compilation, assembly, and linking. (i.e., to only preprocess)
### `clang-format`
    - Purpose: Automatically formats your C source code.
    - Example: `clang-format -i test.c`
    - Flags:
        - `-i`
            - Instructs `clang-format` to format the C files in-place instead of just printing the formatted code.
        - `--style='{IndentWidth: 4, AllowShortFunctionsOnASingleLine: false}'`
            - Instructs `clang-format` to use better styling rules, in my opinion.

## Miscellaneous

### `man`
    - Purpose: Displays manual pages.
    - Example: `man ls`
### `tldr`
    - Purpose: Like `man`, but more concise.
    - Example: `tldr ls`
### `echo`
    - Purpose: Prints its arguments.
