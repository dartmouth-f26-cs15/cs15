.intel_syntax noprefix

.global _start
_start:
    mov r10, qword ptr [rsp] # r10 = argc
    mov r12, 1 # r12 will be our argument loop counter
               # (initially 1 to skip argv[0], which is "./a.out")
    lea rbp, [rsp + 8] # rbp = argv

mainloop:
    # if r12 == argc, stop
    cmp r12, r10
    je write_newline_and_exit

    # rsi = argv[r12]
    mov rsi, qword ptr [rbp + r12 * 8]

    # Now we'll take strlen(argv[r12])
    mov rdx, 0 # rdx = 0 (strlen loop counter)
strlen:
    # if argv[r12][rdx] == 0, we've hit the end of the string
    cmp byte ptr [rsi + rdx], 0
    je write_string_and_space
    # otherwise, keep counting
    inc rdx
    jmp strlen

write_string_and_space:
    # print the string!
    mov rax, 1 # SYS_write
    mov rdi, 1 # STDOUT_FILENO
    # rsi already holds the string's address
    # rdx already holds the string's length
    syscall

    # print a space
    mov rax, 1 # SYS_write
    mov rdi, 1 # STDOUT_FILENO
    lea rsi, [space]
    mov rdx, 1
    syscall

    inc r12
    jmp mainloop

write_newline_and_exit:
    # print a newline
    mov rax, 1 # SYS_write
    mov rdi, 1 # STDOUT_FILENO
    lea rsi, [newline]
    mov rdx, 1
    syscall

    mov rax, 60 # SYS_exit
    mov rdi, 0 # exit status 0
    syscall

.data
space:
    .byte ' '
newline:
    .byte '\n'
