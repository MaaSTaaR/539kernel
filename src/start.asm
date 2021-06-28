bits 16
extern kernel_main
start:
	;jmp $
	mov ax, cs
	mov ds, ax
	
	; --- ;
	
	;mov si, init_message
	;call print_string
	
	; --- ;
	
	;mov ax, [t_val]
	nop ; For Debugging - 0x0001000a
	
	cli
	;mov eax, ds
	;mov eax, gdtr
	;mov ebx, [gdtr]
	;jmp $
	lgdt [gdtr-start] ; 0x00010017
	
	;jmp $
	
	;mov si, gdt_message
	;call print_string
	
	;; Video
	xor eax, eax
	mov ah, 0h
	mov al, 03h
	int 10h
	
	call enter_protected_mode
	
	;mov long [0xb8000], 0x07690748
	
	;jmp $
	
	mov eax, start_kernel
;	add eax, 0x10000
	call 08h:( 0x09000 + ( start_kernel - start ) )
	
	;jmp $

;%include "bios_print.asm"

enter_protected_mode:
	mov eax, cr0
	or al, 1
	mov cr0, eax
	
	ret
	
init_message 	db '    The Starter of 539kernel. Initializing Protected-Mode', 0
gdt_message 	db '    GDT Loaded', 0

;t_val dw 0x539

; The values of the decriptors from Basekernel (kernelcode.S) (https://github.com/dthain/basekernel)

db 'BG'

align 4
gdt:
	null_descriptor				: 	dw 0, 0, 0, 0
	kernel_code_descriptor		: 	dw 0xffff, 0x0000, 9a00h, 0x00cf
	kernel_data_descriptor		: 	dw 0xffff, 0x0000, 0x9200, 0x00cf
	userspace_code_descriptor	: 	dw 0xffff, 0x0000, 0xfa00, 0x00cf
	userspace_data_descriptor	: 	dw 0xffff, 0x0000, 0xf200, 0x00cf

db 'BGR'	

gdtr:
	gdt_size			: 	dw ( 5 * 8 ) ;= 28h
	gdt_base_address	: 	dd 0x09000 + ( gdt - start );0x09000 + gdt ; TODO: I think shifting is more correct way

db 'BeforeStartKernel'
bits 32
start_kernel:
	mov eax, 10h
	mov ds, eax
	mov ss, eax
	mov eax, 0h
	mov es, eax
	mov fs, eax
	mov gs, eax
	;jmp $
	call kernel_main
	;mov eax, 10h
	;mov ds, eax
	;mov ss, eax
	;mov eax, 0h
	;mov es, eax
	;mov fs, eax
	;mov gs, eax
	;mov long [0xb8000], 0x07690748
	;nop
	
t:
	nop
	nop
	nop
