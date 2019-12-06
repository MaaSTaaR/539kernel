; [MQH] 25 Nov 2019.
; This is an example of a bootstrap that uses BIOS video services "0Eh" which prints a character in TTY mode.
; The register "ah" should be set to service's number "0Eh" while "al" should be loaded with the ASCII code of the character that we would like to print.
; Register: ax (16-bit) = ah (8-bit, high) and al (8-bit, low)

start:
	mov ah, 0Eh
	mov al, 'H' ; Instead of 'H' we can use its ASCII code = 72d
	int 10h
	
	mov ah, 0Eh
	mov al, 'e'
	int 10h
	
	mov ah, 0Eh
	mov al, 'l'
	int 10h
	
	mov ah, 0Eh
	mov al, 'l'
	int 10h
	
	mov ah, 0Eh
	mov al, 'o'
	int 10h

    jmp $

times 510-($-$$) db 0
dw 0xAA55
