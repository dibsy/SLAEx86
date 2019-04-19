;code will do a chdir() operation
global _start

section .text

	_start:
		xor eax,eax		;clears out eax
		xor ebx,ebx		;elears out ebx
		push eax		;pushes 0x0 onto the stack
		mov al,0xc		;moves the value 12 to al, 12 is syscall chdir
		push 0x6374652f		;cte/  
		push 0x2f2f2f2f		;////
		mov ebx,esp		;esp points to top top of stack; 
		int 0x80		;initiates interrupt for chdir()
		xor eax,eax		;clear
		inc eax			;stores 1 in eax, 1 is syscall for exit
		int 0x80		;initiates interrupt for exit()
