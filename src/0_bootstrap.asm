start:
	mov ax, 07C0h
	mov ds, ax
	
	; Reset
	mov ax, 0
	mov dl, 0
	int 13h
	
;	jc load_error
	 
	; Load
	mov ax, 1000h
	mov es, ax
	
	mov ah, 02h
	mov al, 01h
	mov ch, 0h
	mov cl, 02h
	mov dh, 0h
	mov dl, 80h ; Drive to read from. Load from hard disk
	mov bx, 0h
	int 13h
	
	jc load_error
			
	jmp 1000h:0000
	
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
	
times 510-($-$$) db 0
dw 0xAA55
