global _start

section .bss
port: RESW 1;

section .text
_start:
	pop ecx
	pop ecx
	mov port,ecx

	mov al,0x4
	mov bl,0x1
	mov ecx,port
	mov edx,1
	
	mov al,1
	mov bl,1
	int 0x80

