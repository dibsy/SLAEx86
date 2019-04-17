import sys
if len(sys.argv) < 3:
	print "\n\nUsage: python shellcode_template.py any_filename.c shellcode\n\n"
	sys.exit()
str1="""
#include <stdio.h>
#include <string.h>
unsigned char shellcode[]=
"""
shellcode=sys.argv[2]
str2 = "\""+shellcode+"\""+";"
str3 = """
int main()
{
    printf("Shellcode size: %d\\n", strlen(shellcode));
    int (*ret)() = (int(*)())shellcode;
    ret();
}
"""
code = str1+str2+str3
w=open(sys.argv[1],"w")
w.write(code)
w.close()
