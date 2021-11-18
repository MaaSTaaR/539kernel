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
	
	; == Printing == ;
	
	mov si, title_string
	call print_string ; "CALL" is used instead of "JMP" because we would like to return to the next instruction after "print_string" finishes.
	
	mov si, message_string
	call print_string
	
	; ... ;
	
	; === Loading the Kernel === ;
	
	call load_kernel_from_disk
	
	; If the loading has been performed correctly. Jump to the kernel's code which resides on 0900h:0000 according
	; to ES:BX values before calling (int 13h).
	;
	; There is a difference between "JMP" and "CALL" inctructions. The first one doesn't store returning information
	; in the stack while the later does. Because we are not going to return from kernel to the bootloader, we don't
	; need to store return information.
	
	jmp 0900h:0000

; ... ;
; ... ;

load_kernel_from_disk:	
	; [MQH] 26 Nov 2019
	; BIOS provides disk services through intrrupt 13h. The value of the register "ah" decides which disk service that we are requesting from BIOS.
	
	; The Disk Service "02h" loads sectors to the memory. The memory location that we would like to load our kernel in should be decided
	; before calling "int 13h". There are two parts of this location. The first part (segment selector) resides in the register "ES" while 
	; the other part (offset) resides in the register "BX".
	;
	; x86 Segment Registers:    CS: for code segment. 
	;                           DS, ES, FS, and GS: for 4 data segments.
	;                           SS: for stack segment.
	; They are 16-bit registers that hold "segment selectors"
	mov ax, [curr_sector_to_load]
	sub ax, 2
	mov bx, 512d
	mul bx
	mov bx, ax
	
	mov ax, 0900h
	mov es, ax
	
	mov ah, 02h     ; Requesting the service of reading disk sectors
	mov al, 1h    	; Number of sectors to read (How many sectors to read?)
	mov ch, 0h      ; Track number
	mov cl, [curr_sector_to_load]     ; Sector number
	mov dh, 0h      ; Head number
	mov dl, 80h     ; Drive to read from. (0 = Floppy. 80h = Drive #0. 81h = Drive #1)
	int 13h         ; BIOS Disk Services
	
	
	; The instruction "jc" jumps to a memory location when CF = 1 (jc = jump if carry).
	; CF (or carry flag) is the first bit of EFLAG register in x86. The BIOS service (13h,02h)
	; clear CF (that is, put 0 in CF) when everything is fine. But if there is some error
	; it's going to set CF (that is, put 1 in CF). Error code will be in "ah".
	;
	; If any error happens in loading our kernel. The bootloader is going to jump to the label "kernel_load_error".
	jc kernel_load_error
	
	sub byte [number_of_sectors_to_load], 1
	add byte [curr_sector_to_load], 1
	cmp byte [number_of_sectors_to_load], 0
	
	jne load_kernel_from_disk
	
	ret

; When the bootloader fails to load the kernel. A nice message is printted for the user.
kernel_load_error:
	mov si, load_error_string
	call print_string
	
	; "$" is a special expression in NASM. It means the starting memory address (or assembly position?) of current instruction, that means
	; the following instruction is going to loop forever. 
	jmp $

; ... ;
; ... ;

; [MQH] 3 Sep 2019
; BIOS provides video services through intrrupt 10h. The value of the register "ah" decides which video service that we are requesting from BIOS.
; Those BIOS services are only available on Real Mode (https://stackoverflow.com/questions/26448480/bios-interrupts-in-protected-mode)
;
; ah = 0Eh means that we wish to print a character in TTY mode.
; For an example of using service "0Eh" to print "Hello" character by character, please refer to "../examples/bootstrap/1/".
	
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
	je printing_finished
	
	int 10h

	jmp print_char

printing_finished:
    mov al, 10d ; Print new line
    int 10h
    
    ; [MQH] NEW 25 June 2021
    ; Move the cursor to the beginning
    mov ah, 03h
	mov bh, 0
	int 10h
	
	mov ah, 02h
	mov dl, 0
	int 10h
    
    ; print_string is a procedure (or function), therefore we should return. It is called by using "CALL" instead of "JMP".
	ret

; ... ;

; [MQH] 9 Dec 2019
; "DB" is one of pseudo-instructions which is provided by NASM. A source line in NASM follows the following format
; label: instruction operands ; comment
; The label is optional and even the colon after the label is optional.
; "DB" is used to declare initialized data. The "B" in "DB" means byte.
; the part ", 0" means that the last byte will be 0. In some way resembles
; nul character in C strings.
;
; Put the string in the output of this assembly file. Byte by byte, and the address of
; this string will be in the label, so we can reach the string inside the assembly source code.
title_string        		db  'The Bootloader of 539kernel.', 0
message_string      		db  'The kernel is loading...', 0
load_error_string   		db  'The kernel cannot be loaded', 0
number_of_sectors_to_load 	db 	15d ; 255 sectors = 127.5KB ; [MQH] NEW 4 July 2021
curr_sector_to_load 		db 	2d

; [MQH] 9 Dec 2019
; "TIMES" is an NASM pseudo-instruction which repeats an instruction a number of specific times.
; The first operand of "TIMES" is the number of repetitions.
; As we mentioned before "$" means the starting address (or assembly position?) of current instruction.
; "$$" is another special expression which means the starting address (or assembly position?) of current section.
; So, we know that the size of bootstrap should be 512 byte. Two bytes are represent the magic code in the last line
; so 510 bytes remains for us. Our code starts from position $$ and we reached position $. Therefore, $ - $$ gives
; us the size of our code. So, 510 - ( $ - $$ ) gives us the remaining size of the 512 bytes and fills it with zeros
; by using "DB".
times 510-($-$$) db 0

; Put the magic code of bootloader in the end of assembly file's output. "W" means word.
dw 0xAA55
