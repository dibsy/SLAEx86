global _start
section .text
_start:
	cbw
	inc eax
	int 0x80
