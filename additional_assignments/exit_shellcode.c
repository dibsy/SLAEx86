
#include <stdio.h>
#include <string.h>
unsigned char shellcode[]=
"\x66\x98\x40\xcd\x80";
int main()
{
    printf("Shellcode size: %d\n", strlen(shellcode));
    int (*ret)() = (int(*)())shellcode;
    ret();
}
