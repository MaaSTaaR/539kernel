bits 16
extern kernel_main

start:
	mov ax, cs
	mov ds, ax
		
	; --- ;
	
	call load_gdt
	call setup_interrupts
	call init_video_mode
	call enter_protected_mode
	
	; --- ;
	
	call 08h:start_kernel
	
load_gdt:
	cli
	lgdt [gdtr - start]
	
	ret
	
setup_interrupts:
	call remap_pic
	call load_idt
	
	ret
	
init_video_mode:
	;; Set Video Mode
	mov ah, 0h
	mov al, 03h ; 03h For Text Mode. 13h For Graphics Mode.
	int 10h
	
	;; Disable Text Cursor
	mov ah, 01h
	mov cx, 2000h
	int 10h
	
	ret

enter_protected_mode:
	mov eax, cr0
	or eax, 1
	mov cr0, eax
	
	ret
	
remap_pic:
	ret

load_idt:
	ret
	
bits 32
start_kernel:
	mov eax, 10h
	mov ds, eax
	mov ss, eax
	
	mov eax, 0h
	mov es, eax
	mov fs, eax
	mov gs, eax
	
	call kernel_main
	
%include "gdt.asm"
