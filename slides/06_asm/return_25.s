# Instructs the assembler to use Intel syntax instead of AT&T syntax.
.intel_syntax noprefix

# Instructs the assembler to make main accessible to the outside world.
.global main

main:           # The main label
    mov rax, 25 # rax = 25
    ret         # return rax
