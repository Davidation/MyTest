	.file	"main.c"
	.text
.globl cb
	.type	cb, @function
cb:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	8(%rax), %eax
	testl	%eax, %eax
	je	.L3
	cmpl	$25, %eax
	je	.L4
	jmp	.L8
.L3:
	movq	-8(%rbp), %rax
	movl	$1, 4(%rax)
	movq	-8(%rbp), %rax
	movl	$0, (%rax)
	jmp	.L5
.L6:
	movq	-8(%rbp), %rax
	movl	$25, 8(%rax)
	movq	-8(%rbp), %rax
	movl	4(%rax), %eax
	movl	%eax, %edx
	movl	%edx, %eax
	jmp	.L7
.L4:
	movq	-8(%rbp), %rax
	movl	4(%rax), %eax
	leal	1(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, 4(%rax)
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	leal	1(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, (%rax)
.L5:
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	cmpl	$19, %eax
	jle	.L6
	jmp	.L3
.L8:
.L7:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	cb, .-cb
	.section	.rodata
.LC0:
	.string	"%d "
	.text
.globl main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$0, -8(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L10
.L11:
	leaq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	cb
	movl	%eax, %edx
	movl	$.LC0, %eax
	movl	%edx, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	addl	$1, -4(%rbp)
.L10:
	cmpl	$99, -4(%rbp)
	jle	.L11
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.4.6 20110731 (Red Hat 4.4.6-4)"
	.section	.note.GNU-stack,"",@progbits
