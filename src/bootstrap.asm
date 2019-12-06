start:
	; [MQH] 3 Sep 2019
	; When a the boot sector is loaded by BIOS. It will be loaded on the location 07C0h in the memory.
	; What we do here is setting the register "ds" to the value "07C0" which is the same of the memory address we are on now.
	; Our variable "hello_string" will be loaded as a part of the bootloader, when we use it in the line "mov si, hello_string"
	; we're actually loading the memory address of the first character, let's assume that this memory address is (1000). Because
	; it is considered as a "data" by the processor. This offset (the memory address of "hello_string") will be added to the data segment
	; selector which resides in the register "ds". According to "Protected Mode Software Architecture", the initial value of "ds" is 0000h,
	; so, if we keep "ds" as it is, the CPU is going to load the data from the memory 00001000, BUT we are actually on 07C0, so the data
	; segment selector should be 07C0h so we can get the correct address of "hello_string" which is 07C01000 and not 00001000.
	; For backward compatibility, when the bootloader starts, the execution environment will be in "Real Mode", 16-bit.
	mov ax, 07C0h
	mov ds, ax
	
	; ... ;
	mov ah, 00h
	mov al, 07h
	int 10h
	
	; ... ;
	
	; == Printing == ;
	
	; [MQH] 3 Sep 2019
	; BIOS provides video services through intrrupt 10h. The value of the register "ah" decides which video service that we are requesting from BIOS.
	; Those BIOS services are only available on Real Mode (https://stackoverflow.com/questions/26448480/bios-interrupts-in-protected-mode)
	;
	; ah = 0Eh means that we wish to print a character in TTY mode.
	; For an example of using service "0Eh" to print "Hello" character by character, please refer to "../examples/bootstrap/1/".
    
	mov si, title_string
	call print_string
	
	mov si, message_string
	call print_string

	
	; ... ;
	
	; === Loading the Kernel === ;
	
	; [MQH] 26 Nov 2019
	; BIOS provides disk services through intrrupt 13h. The value of the register "ah" decides which disk service that we are requesting from BIOS.
	
	mov ax, 1000h
	mov es, ax

	;mov bp, ax
	;mov sp, ax
	;mov ds, ax	
;	mov cs, ax
	
	mov ah, 02h
	mov al, 01h
	mov ch, 0h
	mov cl, 02h
	mov dh, 0h
	mov dl, 80h ; Drive to read from. Load from hard disk
	mov bx, 0h
	int 13h
	
	jc load_error
	
	;mov ax, 10h
	;mov sp, ax
	;mov bp, ax
	;mov cs, ax
	;mov ds, ax
	
	jmp 1000h:0000
	
	; ... ;
	
	jmp $

print_string:
	mov ah, 0Eh

print_char:
    ; [MQH] 26 Nov 2019
	; It's known that a byte = 8 bits. In x86 there are more two units: a "word" = 16 bits and "doubleword" = 32 bits. Some x86 instructions have multiple variants that work
	; with a specific aforementioned unit. "lods" is an example of these instructions, there is "lodsb" which works with a byte, "lodsw" which works with a word and "lodsd" which
	; works with doubleword.
	;
	; The instruction "lods" uses the value which is stored in register "si" (when using lodsb or loadsw) or register "esi" (when using lodsw) and assume that this
	; value as memory location. Then according to the used unit a (b)yte (8-bits), (w)ord (16-bits) or (d)oubleword (32-bit) will be read from the memory location DS:(E)SI
	; and store these bits in al, ax or eax according to the size of read data.
	lodsb
	
	cmp al, 0
	je done
	
	int 10h
	
	jmp print_char

done:
    mov al, 10d ; New Line
    int 10h
    
	ret
	
;;;;------------

load_error:
	;;;;;;;;
	mov bh, ah
	
	mov ah, 0Eh
	mov al, 'a'	
	int 10h
	
	cmp bh, 20h
	je error_01
	
	jmp $
	
	;;;;;;;;;
	
error_01:
	;;;;;;;;
	mov ah, 0Eh
	mov al, '1'	
	int 10h
	;;;;;;;;;
	

title_string db 'The Bootloader of 539kernel.', 0
message_string db 'The kernel is loading...', 0

times 510-($-$$) db 0
dw 0xAA55
