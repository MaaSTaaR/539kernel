bits 16
extern kernel_main
extern interrupt_handler
extern scheduler
extern run_next_process

start:
	mov ax, cs
	mov ds, ax
		
	call load_gdt
	call init_video_mode
	call enter_protected_mode
    call setup_interrupts
    call load_task_register
	
	call 08h:start_kernel
	
load_gdt:
	cli
	lgdt [gdtr - start]
	
	ret
	
enter_protected_mode:
	mov eax, cr0
	or eax, 1
	mov cr0, eax
	
	ret
	
init_video_mode:
	mov ah, 0h
	mov al, 03h
	int 10h
	
	mov ah, 01h
	mov cx, 2000h
	int 10h
	
	ret
	
setup_interrupts:
	call remap_pic
	call load_idt
	
	ret
	
remap_pic:
	mov al, 11h
	
	send_init_cmd_to_pic_master: 	
		out 0x20, al
		
	send_init_cmd_to_pic_slave: 	
		out 0xa0, al
		
	; ... ;
	
	make_irq_starts_from_intr_32_in_pic_master:		
		mov al, 32d
		out 0x21, al
	
	make_irq_starts_from_intr_40_in_pic_slave:
		mov al, 40d
		out 0xa1, al 
	
	; ... ;
	
	tell_pic_master_where_pic_slave_is_connected:
		mov al, 04h
		out 0x21, al
	
	tell_pic_slave_where_pic_master_is_connected:
		mov al, 02h
		out 0xa1, al
	
	; ... ;
	
	mov al, 01h
	
	tell_pic_master_the_arch_is_x86:
		out 0x21, al
	
	tell_pic_slave_the_arch_is_x86:
		out 0xa1, al
	
	; ... ;
	
	mov al, 0h
	
	make_pic_master_enables_all_irqs:
		out 0x21, al
	
	make_pic_slave_enables_all_irqs:
		out 0xa1, al
	
	; ... ;
	
	ret
	
load_idt:
	lidt [idtr - start]
	ret
	
load_task_register:
    mov ax, 40d
    ltr ax
    
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
	
	sti
	
	call kernel_main
	
%include "gdt.asm"
%include "idt.asm"

tss:
    dd 0
