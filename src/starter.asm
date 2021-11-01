bits 16
extern kernel_main
extern interrupt_handler
extern scheduler
extern run_next_process
extern page_directory

global load_page_directory
global enable_paging

global dev_write
global dev_read

global test_ata
global still_going
extern ata_buffer
global ata_finished_read

start:
	mov ax, cs
	mov ds, ax
		
	; --- ;
	
	call load_gdt
	call init_video_mode
	call enter_protected_mode
	call setup_interrupts
	call load_task_register
	
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
load_page_directory:
	mov eax, [page_directory]
	mov cr3, eax
	
	ret
	
enable_paging:
	mov eax, cr0
	or eax, 80000000h
	mov cr0, eax
	
	ret
	
; --- ;

; dev_out( int port, int cmd );
dev_write:
	push edx
	push eax
	
	xor edx, edx
	xor eax, eax
	
	mov dx, [esp + 12]
	mov al, [esp + 16]
	
	;jmp $
	
	out dx, al 
	
	pop eax
	pop edx
	
	ret

; dev_in( int port );
dev_read:
	push edx
	
	xor eax, eax
	
	mov dx, [esp + 8]
;	jmp $
	in al, dx
	
	pop edx
	
	;jmp $
	
	ret

ata_finished_read:
	mov     dx,1f7h
	in      al,dx
	jz      ata_finished_read
	
	ret
	
; Source: https://forum.osdev.org/viewtopic.php?t=12268
test_ata:
	mov eax, 10h
	mov es, eax
	
   mov     dx,1f6h         ;Drive and head port
   mov     al,0a0h         ;Drive 0, head 0
   out     dx,al

   mov     dx,1f2h         ;Sector count port
   mov     al,1            ;Read one sector
   out     dx,al

   mov     dx,1f3h         ;Sector number port
   mov     al,1            ;Read sector one
   out     dx,al

   mov     dx,1f4h         ;Cylinder low port
   mov     al,0            ;Cylinder 0
   out     dx,al

   mov     dx,1f5h         ;Cylinder high port
   mov     al,0            ;The rest of the cylinder 0
   out     dx,al

   mov     dx,1f7h         ;Command port
   mov     al,20h          ;Read with retry.
   out     dx,al
still_going:
   in      al,dx
   ;jmp $
   test    al,8            ;This means the sector buffer requires
            ;servicing.
   jz      still_going     ;Don't continue until the sector buffer
            ;is ready.

   mov     cx,512/2        ;One sector /2
   mov     edi,[ata_buffer]
   mov     dx,1f0h         ;Data port - data comes in and out of here.
   jmp $
   rep     insw

   ret

start_kernel:
	mov eax, 10h
	mov ds, eax
	mov ss, eax
	mov es, eax
	
	mov eax, 0h
	mov fs, eax
	mov gs, eax
	
	;sti
	
	call kernel_main
	
%include "gdt.asm"
%include "idt.asm"

tss:
	dd 0
