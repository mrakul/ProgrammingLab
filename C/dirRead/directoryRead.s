	.file	"directoryRead.c"
	.text
	.def	printf;	.scl	3;	.type	32;	.endef
	.seh_proc	printf
printf:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$56, %rsp
	.seh_stackalloc	56
	leaq	128(%rsp), %rbp
	.seh_setframe	%rbp, 128
	.seh_endprologue
	movq	%rcx, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%r8, -32(%rbp)
	movq	%r9, -24(%rbp)
	leaq	-40(%rbp), %rax
	movq	%rax, -96(%rbp)
	movq	-96(%rbp), %rbx
	movl	$1, %ecx
	movq	__imp___acrt_iob_func(%rip), %rax
	call	*%rax
	movq	%rbx, %r8
	movq	-48(%rbp), %rdx
	movq	%rax, %rcx
	call	__mingw_vfprintf
	movl	%eax, -84(%rbp)
	movl	-84(%rbp), %eax
	addq	$56, %rsp
	popq	%rbx
	popq	%rbp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC0:
	.ascii ".\0"
.LC1:
	.ascii "%s\12\0"
.LC2:
	.ascii "r\0"
.LC3:
	.ascii ".\\C_Code\\TestProgram\\file.txt\0"
.LC4:
	.ascii "Cannot open file.\12\0"
.LC5:
	.ascii "Line1 size is: %d\12\0"
.LC6:
	.ascii "Line2 size is: %d\12\0"
.LC7:
	.ascii "%s\0"
.LC8:
	.ascii "File is closed successfully\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%r15
	.seh_pushreg	%r15
	pushq	%r14
	.seh_pushreg	%r14
	pushq	%r13
	.seh_pushreg	%r13
	pushq	%r12
	.seh_pushreg	%r12
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	addq	$-128, %rsp
	.seh_stackalloc	128
	.seh_endprologue
	movl	%ecx, 64(%rbp)
	movq	%rdx, 72(%rbp)
	call	__main
	leaq	.LC0(%rip), %rcx
	call	opendir
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L4
	jmp	.L5
.L6:
	movq	-16(%rbp), %rax
	addq	$8, %rax
	movq	%rax, %rdx
	leaq	.LC1(%rip), %rcx
	call	printf
.L5:
	movq	-8(%rbp), %rax
	movq	%rax, %rcx
	call	readdir
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L6
	movq	-8(%rbp), %rax
	movq	%rax, %rcx
	call	closedir
.L4:
	leaq	.LC2(%rip), %rdx
	leaq	.LC3(%rip), %rcx
	call	fopen
	movq	%rax, -24(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L7
	leaq	.LC4(%rip), %rcx
	call	printf
	movl	$1, %ecx
	call	exit
.L7:
	movq	$20, -32(%rbp)
	movq	$0, -96(%rbp)
	movq	$0, -88(%rbp)
	movq	$0, -80(%rbp)
	movq	$0, -72(%rbp)
	movq	$0, -64(%rbp)
	movq	-32(%rbp), %rbx
	movq	%rsp, %rax
	movq	%rax, %rsi
	movq	%rbx, %rax
	subq	$1, %rax
	movq	%rax, -40(%rbp)
	movq	%rbx, %r14
	movl	$0, %r15d
	movq	%rbx, %r12
	movl	$0, %r13d
	leaq	0(,%rbx,4), %rax
	addq	$15, %rax
	shrq	$4, %rax
	salq	$4, %rax
	call	___chkstk_ms
	subq	%rax, %rsp
	leaq	32(%rsp), %rax
	addq	$3, %rax
	shrq	$2, %rax
	salq	$2, %rax
	movq	%rax, -48(%rbp)
	movl	$40, %edx
	leaq	.LC5(%rip), %rcx
	call	printf
	leaq	0(,%rbx,4), %rax
	movq	%rax, %rdx
	leaq	.LC6(%rip), %rcx
	call	printf
	jmp	.L8
.L9:
	movq	-24(%rbp), %rdx
	leaq	-96(%rbp), %rax
	movq	%rdx, %r8
	movl	$40, %edx
	movq	%rax, %rcx
	call	fgets
	testq	%rax, %rax
	je	.L8
	leaq	-96(%rbp), %rax
	movq	%rax, %rdx
	leaq	.LC7(%rip), %rcx
	call	printf
.L8:
	movq	-24(%rbp), %rax
	movq	%rax, %rcx
	call	feof
	testl	%eax, %eax
	je	.L9
	movq	-24(%rbp), %rax
	movq	%rax, %rcx
	call	fclose
	testl	%eax, %eax
	jne	.L10
	leaq	.LC8(%rip), %rcx
	call	printf
.L10:
	movl	$0, %eax
	movq	%rsi, %rsp
	movq	%rbp, %rsp
	popq	%rbx
	popq	%rsi
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (MinGW-W64 x86_64-posix-seh, built by Brecht Sanders) 10.2.0"
	.def	__mingw_vfprintf;	.scl	2;	.type	32;	.endef
	.def	opendir;	.scl	2;	.type	32;	.endef
	.def	readdir;	.scl	2;	.type	32;	.endef
	.def	closedir;	.scl	2;	.type	32;	.endef
	.def	fopen;	.scl	2;	.type	32;	.endef
	.def	exit;	.scl	2;	.type	32;	.endef
	.def	fgets;	.scl	2;	.type	32;	.endef
	.def	feof;	.scl	2;	.type	32;	.endef
	.def	fclose;	.scl	2;	.type	32;	.endef
