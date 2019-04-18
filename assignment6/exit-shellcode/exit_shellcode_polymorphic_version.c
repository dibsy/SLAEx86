/*

08048060 <_start>:
 8048060:	31 c0                	xor    eax,eax
 8048062:	40                   	inc    eax
 8048063:	cd 80                	int    0x80

*/
#include <stdio.h>
#include <string.h>
unsigned char shellcode[]=
"\x31\xc0\x40\xcd\x80";
int main()
{
    printf("Shellcode size: %d\n", strlen(shellcode));
    int (*ret)() = (int(*)())shellcode;
    ret();
}
