	.file	"kernel.c"
	.text
#APP
	.code16gcc
#NO_APP
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x7c,0x6
	subl	$20, %esp
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	movb	$65, -9(%ebp)
	movzbl	-9(%ebp), %edx
#APP
# 23 "kernel.c" 1
	movb $0x0E, %ah
movb %dl, %al
int $0x10

# 0 "" 2
#NO_APP
	subl	$12, %esp
	pushl	$97
	call	print_c
	addl	$16, %esp
.L2:
	jmp	.L2
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.globl	print_c
	.type	print_c, @function
print_c:
.LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$20, %esp
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	movl	8(%ebp), %eax
	movb	%al, -20(%ebp)
	movb	$83, -1(%ebp)
	movzbl	-1(%ebp), %edx
#APP
# 57 "kernel.c" 1
	movb $0x0E, %ah
movb %dl, %al
int $0x10

# 0 "" 2
#NO_APP
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	print_c, .-print_c
	.globl	get_char
	.type	get_char, @function
get_char:
.LFB2:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	movl	$83, %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	get_char, .-get_char
	.section	.text.__x86.get_pc_thunk.ax,"axG",@progbits,__x86.get_pc_thunk.ax,comdat
	.globl	__x86.get_pc_thunk.ax
	.hidden	__x86.get_pc_thunk.ax
	.type	__x86.get_pc_thunk.ax, @function
__x86.get_pc_thunk.ax:
.LFB3:
	.cfi_startproc
	movl	(%esp), %eax
	ret
	.cfi_endproc
.LFE3:
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
