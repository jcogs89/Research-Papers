/* length_ext.c */
#include <stdio.h>
#include <arpa/inet.h>
#include <openssl/sha.h>

int main(int argc, const char *argv[])
{
	int i;
	unsigned char buffer[SHA256_DIGEST_LENGTH];
	SHA256_CTX c;
	SHA256_Init(&c);

	for(i=0; i<64; i++)
		SHA256_Update(&c, "*", 1);
//The MAC of "123456:myname=JamesCogswell&uid=1001&lstcmd=1" is
//3097c2f3 8f714e3d f2533de0 17310961 40e2ea7f 3f1d8753 6b708906 ffe04aa4
//2490213c 22365305 03864a4a fb2d2aa7 844bec83 964cc4e0 bd6b9d4f fb3980f5
	// MAC of the original message M (padded)
	c.h[0] = htole32(0x2490213c);
	c.h[1] = htole32(0x22365305);
	c.h[2] = htole32(0x03864a4a);
	c.h[3] = htole32(0xfb2d2aa7);
	c.h[4] = htole32(0x844bec83);
	c.h[5] = htole32(0x964cc4e0);
	c.h[6] = htole32(0xbd6b9d4f);
	c.h[7] = htole32(0xfb3980f5);

	// Append additional message
	SHA256_Update(&c, "&download=secret.txt", 20);
	SHA256_Final(buffer, &c);
	
	for(i = 0; i < 32; i++) {
		printf("%02x", buffer[i]);
	}
	
	printf("\n");
	
	return 0;
}