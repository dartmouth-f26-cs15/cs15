.intel_syntax noprefix

.data
buf:
    .byte 0

.text

.globl _start
_start:
    xor eax, eax # SYS_read
    xor edi, edi # STDIN_FILENO
    lea rsi, [buf] # buf
    mov edx, 1 # count
    syscall

    xor ecx, ecx # counter
    xor eax, eax # input
    mov al, BYTE PTR [buf]

.Lloop:
    cmp rax, 1
    jbe .Lfinish

    mov dl, al
    and dl, 1
    test dl, dl
    jne .Lodd

    shr rax, 1
    jmp .Lloop_bottom
.Lodd:
    imul rax, 3
    inc rax
.Lloop_bottom:
    inc rcx # increment counter
    jmp .Lloop

.Lfinish:
    mov eax, 60 # SYS_exit
    mov rdi, rcx # counter
    syscall
