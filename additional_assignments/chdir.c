
#include <stdio.h>
#include <string.h>
unsigned char shellcode[]=
"\x31\xc0\x31\xdb\x50\xb0\x0c\x68\x2f\x65\x74\x63\x68\x2f\x2f\x2f\x2f\x89\xe3\xcd\x80\x31\xc0\x40\xcd\x80";
int main()
{
    printf("Shellcode size: %d\n", strlen(shellcode));
    int (*ret)() = (int(*)())shellcode;
    ret();
}
