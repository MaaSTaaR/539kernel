start:
	mov ax, cs
	mov ds, ax
	
	; --- ;
	
	mov si, init_message
	call print_string
	
	; --- ;
	
	;mov ax, [t_val]
	nop ; For Debugging - 0x0001000a
	
	cli
	;mov eax, ds
	add eax, gdtr
	mov ebx, [gdtr]
	mov ecx, [end_gdtr]
	lgdt [gdtr-end_gdtr]
	
	;jmp $
	
	mov si, gdt_message
	call print_string
	
	;; Video
	;mov ah, 0h
	;mov al, 03h
	;int 10h
	
	call enter_protected_mode
	
	;mov long [0xb8000], 0x07690748
	
	;jmp $
	
	call 08h:start_kernel
	
	jmp $

%include "bios_print.asm"

enter_protected_mode:
	mov eax, cr0
	or al, 1
	mov cr0, eax
	
	ret
	
init_message 	db '    The Starter of 539kernel. Initializing Protected-Mode', 0
gdt_message 	db '    GDT Loaded', 0

;t_val dw 0x539

; The values of the decriptors from Basekernel (kernelcode.S) (https://github.com/dthain/basekernel)

gdt:
	null_descriptor				: 	dw 0, 0, 0, 0
	kernel_code_descriptor		: 	dw 0xffff, 0x0000, 9a00h, 0x00cf
	kernel_data_descriptor		: 	dw 0xffff, 0x0000, 0x9200, 0x00cf
	userspace_code_descriptor	: 	dw 0xffff, 0x0000, 0xfa00, 0x00cf
	userspace_data_descriptor	: 	dw 0xffff, 0x0000, 0xf200, 0x00cf

db 'BGR'	
align 4
gdtr:
	gdt_size			: 	dw 40d ;( 5 * 8 ) = 28h
	gdt_base_address	: 	dd gdt
end_gdtr:

start_kernel:
	mov eax, 10h
	mov ds, eax
	mov ss, eax
	mov eax, 0h
	mov es, eax
	mov fs, eax
	mov gs, eax
	;mov eax, 10h
	;mov ds, eax
	;mov ss, eax
	;mov eax, 0h
	;mov es, eax
	;mov fs, eax
	;mov gs, eax
	;mov long [0xb8000], 0x07690748
	;nop
