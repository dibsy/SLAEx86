;http://shell-storm.org/shellcode/files/shellcode-623.php
global _start

_start:
	xor	eax,eax
	mov	al,01
	xor 	ebx,ebx
	int	0x80
