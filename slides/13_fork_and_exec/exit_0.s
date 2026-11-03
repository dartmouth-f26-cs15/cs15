.intel_syntax noprefix

.global _start
_start:
    mov eax, 60
    xor edi, edi
    syscall
