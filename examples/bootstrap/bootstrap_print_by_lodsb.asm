start:
	mov ax, 07C0h
	mov ds, ax
		
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

hello_string db 'Hello Bootstrap World! - LODSB Version', 0

times 510-($-$$) db 0
dw 0xAA55
