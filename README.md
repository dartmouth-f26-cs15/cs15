# cs15

## Please download this repository by running the following command on Plink:
```sh
git clone https://github.com/dartmouth-f26-cs15/cs15
```

This repository stores 3 things: lecture slides, handouts, and assignments.

## Lecture Slides

Lecture slides are distributed as LaTeX source code.
LaTeX is a typesetting language that can be compiled to PDF.
In order to compile the LaTeX source code, `cd` into the appropriate subdirectory of `slides`, then run `lualatex -shell-escape main.tex`.

For example, to compile the slides from the first class,
```bash
cd ./slides/00_compiling_and_integers
lualatex -shell-escape main.tex
```
That should produce a file named `main.pdf` that you can `scp` to your laptop and view.

## Handouts

Handouts are distributed as Markdown files.
Markdown is a simple text formatting language that can be read as plain text.
It can also be compiled to PDF, HTML, or even LaTeX.
If you'd like to compile the Markdown files into another format, use `pandoc`.
For example, to compile the shell commands handout,
```bash
cd ./handouts/shell_commands
pandoc -i shell_commands.md -o shell_commands.pdf
```
That should produce a file named `shell_commands.pdf` that you can `scp` to your laptop and vi
ew.

## Assignments

Assignments, like handouts, are distributed as Markdown, and can be compiled to PDF in exactly
 the same way as handouts.
For example, to compile the first assignment,
```bash
cd ./assignments/00_vec3
pandoc -i assignment.md -o assignment.pdf
```
That should produce a file named `assignment.pdf` that you can `scp` to your laptop and view.
