isr_0:
	push 0
	jmp isr_basic

isr_1:
	push 1
	jmp isr_basic
	
isr_2:
	push 2
	jmp isr_basic
	
isr_3:
	push 3
	jmp isr_basic
	
isr_4:
	push 4
	jmp isr_basic
	
isr_5:
	push 5
	jmp isr_basic
	
isr_6:
	push 6
	jmp isr_basic
	
isr_7:
	push 7
	jmp isr_basic
	
isr_8:
	push 8
	jmp isr_basic
	
isr_9:
	push 9
	jmp isr_basic
	
isr_10:
	push 10
	jmp isr_basic
	
isr_11:
	push 11
	jmp isr_basic
	
isr_12:
	push 12
	jmp isr_basic
	
isr_13:
	push 13
	jmp isr_basic
	
isr_14:
	push 14
	jmp isr_basic
	
isr_15:
	push 15
	jmp isr_basic
	
isr_16:
	push 16
	jmp isr_basic
	
isr_17:
	push 17
	jmp isr_basic
	
isr_18:
	push 18
	jmp isr_basic
	
isr_19:
	push 19
	jmp isr_basic
	
isr_20:
	push 20
	jmp isr_basic
	
isr_21:
	push 21
	jmp isr_basic

isr_22:
	push 22
	jmp isr_basic
	
isr_23:
	push 23
	jmp isr_basic
	
isr_24:
	push 24
	jmp isr_basic
	
isr_25:
	push 25
	jmp isr_basic
	
isr_26:
	push 26
	jmp isr_basic
	
isr_27:
	push 27
	jmp isr_basic
	
isr_28:
	push 28
	jmp isr_basic
	
isr_29:
	push 29
	jmp isr_basic
	
isr_30:
	push 30
	jmp isr_basic
	
isr_31:
	push 31
	jmp isr_basic
	
isr_32:
	push 32
	jmp irq_basic
	
isr_33:
	push 33
	jmp irq_basic
	
isr_34:
	push 34
	jmp irq_basic
	
isr_35:
	push 35
	jmp irq_basic
	
isr_36:
	push 36
	jmp irq_basic
	
isr_37:
	push 37
	jmp irq_basic

isr_38:
	push 38
	jmp irq_basic

isr_39:
	push 39
	jmp irq_basic

isr_40:
	push 40
	jmp irq_basic

isr_41:
	push 41
	jmp irq_basic

isr_42:
	push 42
	jmp irq_basic

isr_43:
	push 43
	jmp irq_basic

isr_44:
	push 44
	jmp irq_basic

isr_45:
	push 45
	jmp irq_basic

isr_46:
	push 46
	jmp irq_basic

isr_47:
	push 47
	jmp irq_basic
	
isr_48:
	push 48
	jmp irq_basic

isr_basic:
	call interrupt_handler
	
	add esp, 4
	iret
	
irq_basic:
	call interrupt_handler
	
	;jmp $
	
	mov al, 0x20
	out 0x20, al
	
	cmp byte [esp], 40d ; Interrupt number
	jnge irq_basic_end
	
	mov al, 0xa0
	out 0x20, al
	
	irq_basic_end:
		add esp, 4
		ret
	
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
	idt_size_in_bytes	: 	dw idtr - idt; ( 2 * 8 ) ;= 28h
	idt_base_address	: 	dd idt
