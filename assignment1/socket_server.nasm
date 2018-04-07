global _start

section .text

_start:

	;creating the socket
	;socket(AF_INET,SOCK_STREAM,0);
	;EAX = syscall number for socket = 102 ( in decimal ) , 66 ( in hex )
	;EBX = AF_INET = 2
	;ECX = SOCK_STREAM = 1
	;EDX = 0

	xor eax,eax
	xor ebx,ebx
	xor ecx,ecx
	xor edx,edx

	mov al,0x66
	mov bl,2
	mov cl,1
	mov dl,1
	dec dl
	int 0x80
	
	;bind socket


	;listen


	;accept


	;close the socket


	;keep the client fd alive and send the output to client 


	;call execl


	;exit shellcode
	xor eax,eax
	xor ebx,ebx
	mov al,1
	mov bl,0
	int 0x80				
