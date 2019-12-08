start:
	mov ax, cs
	mov ds, ax
	
	; --- ;
	
	
	
	; [WRITING NOTE] For 0.0 Phase #2
	; [WRITING NOTE] Excercise: Apply this to the bootstrap.
	; [WRITING NOTE] Excercise: Clear the screen before printing the message of the kernel.
	; Moving the cursor to the beginning
	;mov ah, 02h ; Service number. 02 = Set Cursor Position
	;mov bh, 0 ; Page number (0 for graphics mode (what is graphics mode?))
	;mov dh, 0 ; row
	;mov dl, 0 ; column
	;int 10h ; Interrupt 10h, Video BIOS Services
	
	; --- ;
	
	mov si, hello_string
	call print_string
	
	jmp $

print_string:
	mov ah, 0Eh

print_char:
	lodsb
	
	cmp al, 0
	je done
	
	int 10h
	
	jmp print_char

done:
	ret
	
hello_string db 'Hello World!, From Simple Assembly 539kernel!', 0
