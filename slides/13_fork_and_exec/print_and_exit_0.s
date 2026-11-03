.intel_syntax noprefix

.global _start
_start:
    mov eax, 1 # SYS_write
    mov edi, 1 # STDOUT_FILENO
    lea rsi, [msg]
    mov edx, 18
    syscall

    mov eax, 60 # SYS_exit
    xor edi, edi
    syscall

msg:
    .ascii "totally bngular!!\n"
