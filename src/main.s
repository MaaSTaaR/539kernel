	.file	"main.c"
	.text
	.globl	main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
#APP
# 12 "main.c" 1
	movl $0x07690748,0xb8000
# 0 "" 2
# 13 "main.c" 1
	1: jmp 1
# 0 "" 2
#NO_APP
	movl	$0, %eax
	popl	%ebp
	ret
	.size	main, .-main
	.globl	p
	.type	p, @function
p:
	pushl	%ebp
	movl	%esp, %ebp
#APP
# 57 "main.c" 1
	mov $0x0E, %ah
# 0 "" 2
# 58 "main.c" 1
	mov $0x43, %al
# 0 "" 2
# 59 "main.c" 1
	int $0x10
# 0 "" 2
# 60 "main.c" 1
	mov $0x0E, %ah
# 0 "" 2
# 61 "main.c" 1
	mov $0x43, %al
# 0 "" 2
# 62 "main.c" 1
	int $0x10
# 0 "" 2
# 63 "main.c" 1
	12: jmp 12
# 0 "" 2
#NO_APP
	nop
	popl	%ebp
	ret
	.size	p, .-p
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
