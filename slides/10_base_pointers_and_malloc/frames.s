	.text
	.intel_syntax noprefix
	.globl	double_char                     
double_char:                            
	push	rbp
	mov	rbp, rsp
	mov	al, dil
	mov	byte ptr [rbp - 1], al
	movsx	eax, byte ptr [rbp - 1]
	shl	eax
	cdqe
	mov	qword ptr [rbp - 16], rax
	mov	rax, qword ptr [rbp - 16]
	pop	rbp
	ret
.Lfunc_end0:
                                        
	.globl	f                               
f:                                      
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	qword ptr [rbp - 8], rdi
	mov	qword ptr [rbp - 16], rsi
	mov	qword ptr [rbp - 24], 0
	mov	qword ptr [rbp - 32], 0
.LBB1_1:                                
	mov	rax, qword ptr [rbp - 32]
	cmp	rax, qword ptr [rbp - 16]
	jae	.LBB1_4
	mov	rax, qword ptr [rbp - 8]
	mov	rcx, qword ptr [rbp - 32]
	movsx	edi, byte ptr [rax + rcx]
	call	double_char
	add	rax, qword ptr [rbp - 24]
	mov	qword ptr [rbp - 24], rax
	mov	rax, qword ptr [rbp - 32]
	add	rax, 1
	mov	qword ptr [rbp - 32], rax
	jmp	.LBB1_1
.LBB1_4:
	mov	rax, qword ptr [rbp - 24]
	add	rsp, 32
	pop	rbp
	ret
.Lfunc_end1:
                                        
	.globl	main                            
main:                                   
	push	rbp
	mov	rbp, rsp
	sub	rsp, 16
	movabs	rdi, offset main.s
	mov	esi, 15
	call	f
	mov	qword ptr [rbp - 8], rax
	mov	rsi, qword ptr [rbp - 8]
	movabs	rdi, offset .L.str
	mov	al, 0
	call	printf
	xor	eax, eax
	add	rsp, 16
	pop	rbp
	ret
.Lfunc_end2:
                                        
	.section	.rodata,"a",@progbits
main.s:
	.asciz	"hunter2hunter2"
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"result = %zu\n"
	.section	".note.GNU-stack","",@progbits
