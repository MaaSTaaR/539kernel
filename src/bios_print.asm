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

