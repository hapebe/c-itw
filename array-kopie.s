	.file	"array-kopie.c"
	.text
	.section	.rodata
.LC0:
	.string	"%2x "
.LC1:
	.string	"   "
	.text
	.globl	dump
	.type	dump, @function
dump:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	.L2
.L3:
	addq	$1, -8(%rbp)
.L2:
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L3
	movq	-8(%rbp), %rdx
	movq	-40(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	addl	$1, %eax
	movl	%eax, -16(%rbp)
	movl	-16(%rbp), %eax
	leal	15(%rax), %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
	sarl	$4, %eax
	movl	%eax, -28(%rbp)
	movl	-16(%rbp), %eax
	andl	$15, %eax
	testl	%eax, %eax
	je	.L4
	addl	$1, -28(%rbp)
.L4:
	movl	$0, -24(%rbp)
	jmp	.L5
.L14:
	movl	$0, -20(%rbp)
	jmp	.L6
.L9:
	movl	-24(%rbp), %eax
	sall	$4, %eax
	movl	%eax, %edx
	movl	-20(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	cmpl	-16(%rbp), %eax
	jge	.L7
	movl	-12(%rbp), %eax
	movslq	%eax, %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	%eax, %edi
	call	putchar@PLT
	jmp	.L8
.L7:
	movl	$32, %edi
	call	putchar@PLT
.L8:
	addl	$1, -20(%rbp)
.L6:
	cmpl	$15, -20(%rbp)
	jle	.L9
	movl	$9, %edi
	call	putchar@PLT
	movl	$0, -20(%rbp)
	jmp	.L10
.L13:
	movl	-24(%rbp), %eax
	sall	$4, %eax
	movl	%eax, %edx
	movl	-20(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	cmpl	-16(%rbp), %eax
	jge	.L11
	movl	-12(%rbp), %eax
	movslq	%eax, %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movzbl	%al, %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L12
.L11:
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
.L12:
	addl	$1, -20(%rbp)
.L10:
	cmpl	$15, -20(%rbp)
	jle	.L13
	movl	$10, %edi
	call	putchar@PLT
	addl	$1, -24(%rbp)
.L5:
	movl	-24(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L14
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	dump, .-dump
	.section	.rodata
.LC2:
	.string	"\nDump vom kopie:"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$176, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movabsq	$8315165676099821894, %rax
	movabsq	$2318355891342108771, %rdx
	movq	%rax, -160(%rbp)
	movq	%rdx, -152(%rbp)
	movabsq	$7165066617807004257, %rax
	movabsq	$2338608882692005992, %rdx
	movq	%rax, -144(%rbp)
	movq	%rdx, -136(%rbp)
	movabsq	$7123604094587920743, %rax
	movabsq	$7311438299927898476, %rdx
	movq	%rax, -128(%rbp)
	movq	%rdx, -120(%rbp)
	movabsq	$7956001727506117481, %rax
	movabsq	$8391720598993444965, %rdx
	movq	%rax, -112(%rbp)
	movq	%rdx, -104(%rbp)
	movw	$10975, -96(%rbp)
	movb	$0, -94(%rbp)
	movl	$0, -164(%rbp)
	movl	$0, -164(%rbp)
	jmp	.L16
.L17:
	movl	-164(%rbp), %eax
	cltq
	movzbl	-160(%rbp,%rax), %edx
	movl	-164(%rbp), %eax
	cltq
	movb	%dl, -80(%rbp,%rax)
	addl	$1, -164(%rbp)
.L16:
	movl	-164(%rbp), %eax
	cmpl	$66, %eax
	jbe	.L17
	leaq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC2(%rip), %rdi
	call	puts@PLT
	leaq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	dump
	movl	$0, %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L19
	call	__stack_chk_fail@PLT
.L19:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.3.0-16ubuntu3) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
