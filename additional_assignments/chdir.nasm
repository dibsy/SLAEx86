global _start
section .text
_start:
	xor eax,eax
	xor ebx,ebx
	push eax
	mov al,0xc
	push 0x6374652f
	push 0x2f2f2f2f
	mov ebx,esp
	int 0x80
	xor eax,eax
	inc eax
	int 0x80	
