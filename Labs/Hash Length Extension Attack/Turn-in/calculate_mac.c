/* calculate_mac.c */
#include <stdio.h>
#include <openssl/sha.h>
int main(int argc, const char *argv[])
{
SHA256_CTX c;
unsigned char buffer[SHA256_DIGEST_LENGTH];
int i;
SHA256_Init(&c);
// The length of "123456:myname=JamesCogswell&uid=1001&lstcmd=1" is 45
// 45*3 = 360   --> 360 in Hex is 0x168
SHA256_Update(&c,
"123456:myname=JamesCogswell&uid=1001&lstcmd=1"
"\x80"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x01\x68"
"&download=secret.txt",
64+20);
SHA256_Final(buffer, &c);
for(i = 0; i < 32; i++) {
printf("%02x", buffer[i]);
}
printf("\n");
return 0;
}


