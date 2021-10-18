isr_0:
	cli
	push 0
	jmp isr_basic

isr_1:
	cli
	push 1
	jmp isr_basic
	
isr_2:
	cli
	push 2
	jmp isr_basic
	
isr_3:
	cli
	push 3
	jmp isr_basic
	
isr_4:
	cli
	push 4
	jmp isr_basic
	
isr_5:
	cli
	push 5
	jmp isr_basic
	
isr_6:
	cli
	push 6
	jmp isr_basic
	
isr_7:
	cli
	push 7
	jmp isr_basic
	
isr_8:
	cli
	push 8
	jmp isr_basic
	
isr_9:
	cli
	push 9
	jmp isr_basic
	
isr_10:
	cli
	push 10
	jmp isr_basic
	
isr_11:
	cli
	push 11
	jmp isr_basic
	
isr_12:
	cli
	push 12
	jmp isr_basic
	
isr_13:
	cli
	push 13
	jmp isr_basic
	
isr_14:
	cli
	push 14
	jmp isr_basic
	
isr_15:
	cli
	push 15
	jmp isr_basic
	
isr_16:
	cli
	push 16
	jmp isr_basic
	
isr_17:
	cli
	push 17
	jmp isr_basic
	
isr_18:
	cli
	push 18
	jmp isr_basic
	
isr_19:
	cli
	push 19
	jmp isr_basic
	
isr_20:
	cli
	push 20
	jmp isr_basic
	
isr_21:
	cli
	push 21
	jmp isr_basic

isr_22:
	cli
	push 22
	jmp isr_basic
	
isr_23:
	cli
	push 23
	jmp isr_basic
	
isr_24:
	cli
	push 24
	jmp isr_basic
	
isr_25:
	cli
	push 25
	jmp isr_basic
	
isr_26:
	cli
	push 26
	jmp isr_basic
	
isr_27:
	cli
	push 27
	jmp isr_basic
	
isr_28:
	cli
	push 28
	jmp isr_basic
	
isr_29:
	cli
	push 29
	jmp isr_basic
	
isr_30:
	cli
	push 30
	jmp isr_basic
	
isr_31:
	cli
	push 31
	jmp isr_basic
	
; System Timer
isr_32:
	
	cli
	
	pusha ; Store the context of current process
	
	mov eax, [esp + 32] ; EIP before interrupt. Could be the EIP of the current process
	push eax  
	
	call scheduler
	
	mov al, 0x20
	out 0x20, al
	
	add esp, 40d ; Remove return address from stack, EIP and all general purpose registers of previous process.
	push run_next_process

	iret
	
isr_33:
	cli
	push 33
	jmp irq_basic
	
isr_34:
	cli
	push 34
	jmp irq_basic
	
isr_35:
	cli
	push 35
	jmp irq_basic
	
isr_36:
	cli
	push 36
	jmp irq_basic
	
isr_37:
	cli
	push 37
	jmp irq_basic

isr_38:
	cli
	push 38
	jmp irq_basic

isr_39:
	cli
	push 39
	jmp irq_basic

isr_40:
	cli
	push 40
	jmp irq_basic

isr_41:
	cli
	push 41
	jmp irq_basic

isr_42:
	cli
	push 42
	jmp irq_basic

isr_43:
	cli
	push 43
	jmp irq_basic

isr_44:
	cli
	push 44
	jmp irq_basic

isr_45:
	cli
	push 45
	jmp irq_basic

isr_46:
	cli
	push 46
	jmp irq_basic

isr_47:
	cli
	push 47
	jmp irq_basic
	
isr_48:
	cli
	push 48
	jmp irq_basic

isr_basic:
;	cli
	call interrupt_handler
	
	pop eax
	sti
	iret
	
irq_basic:
;	cli
	call interrupt_handler
	
	mov al, 0x20
	out 0x20, al
	
	cmp byte [esp], 40d ; Interrupt number
	jnge irq_basic_end
	
	mov al, 0xa0
	out 0x20, al
	
	irq_basic_end:
		pop eax
		sti
		iret
	
; The value of the flags from Basekernel (kernelcode.S) (https://github.com/dthain/basekernel)
idt:
	dw isr_0, 8, 0x8e00, 0x0000
	dw isr_1, 8, 0x8e00, 0x0000
	dw isr_2, 8, 0x8e00, 0x0000
	dw isr_3, 8, 0x8e00, 0x0000
	dw isr_4, 8, 0x8e00, 0x0000
	dw isr_5, 8, 0x8e00, 0x0000
	dw isr_6, 8, 0x8e00, 0x0000
	dw isr_7, 8, 0x8e00, 0x0000
	dw isr_8, 8, 0x8e00, 0x0000
	dw isr_9, 8, 0x8e00, 0x0000
	dw isr_10, 8, 0x8e00, 0x0000
	dw isr_11, 8, 0x8e00, 0x0000
	dw isr_12, 8, 0x8e00, 0x0000
	dw isr_13, 8, 0x8e00, 0x0000
	dw isr_14, 8, 0x8e00, 0x0000
	dw isr_15, 8, 0x8e00, 0x0000
	dw isr_16, 8, 0x8e00, 0x0000
	dw isr_17, 8, 0x8e00, 0x0000
	dw isr_18, 8, 0x8e00, 0x0000
	dw isr_19, 8, 0x8e00, 0x0000
	dw isr_20, 8, 0x8e00, 0x0000
	dw isr_21, 8, 0x8e00, 0x0000
	dw isr_22, 8, 0x8e00, 0x0000
	dw isr_23, 8, 0x8e00, 0x0000
	dw isr_24, 8, 0x8e00, 0x0000
	dw isr_25, 8, 0x8e00, 0x0000
	dw isr_26, 8, 0x8e00, 0x0000
	dw isr_27, 8, 0x8e00, 0x0000
	dw isr_28, 8, 0x8e00, 0x0000
	dw isr_29, 8, 0x8e00, 0x0000
	dw isr_30, 8, 0x8e00, 0x0000
	dw isr_31, 8, 0x8e00, 0x0000
	dw isr_32, 8, 0x8e00, 0x0000
	dw isr_33, 8, 0x8e00, 0x0000
	dw isr_34, 8, 0x8e00, 0x0000
	dw isr_35, 8, 0x8e00, 0x0000
	dw isr_36, 8, 0x8e00, 0x0000
	dw isr_37, 8, 0x8e00, 0x0000
	dw isr_38, 8, 0x8e00, 0x0000
	dw isr_39, 8, 0x8e00, 0x0000
	dw isr_40, 8, 0x8e00, 0x0000
	dw isr_41, 8, 0x8e00, 0x0000
	dw isr_42, 8, 0x8e00, 0x0000
	dw isr_43, 8, 0x8e00, 0x0000
	dw isr_44, 8, 0x8e00, 0x0000
	dw isr_45, 8, 0x8e00, 0x0000
	dw isr_46, 8, 0x8e00, 0x0000
	dw isr_47, 8, 0x8e00, 0x0000
	dw isr_48, 8, 0x8e00, 0x0000
	
idtr:
	idt_size_in_bytes	: 	dw idtr - idt
	idt_base_address	: 	dd idt
