#define SWITCH 16 // number of bridgeports
#define MAC 16 // mac table = SWITCH * MAC
#define HASH_TABLE (SWITCH * MAC) // mac table = (SWITCH * MAC)
#define PRIME 3 // 661

#include <stdio.h>
#include <string.h>

typedef struct {
	unsigned char ach_MACdst[6];
	unsigned char ach_MACsrc[6];
	int ach_Length;
	char ach_Payload[46]; // minimal
	char ach_crc[4]; // 32bit crc
} SFrame;

int main(int argc, char *argv[]){
	int hash=0;
	int i=0;
	
	SFrame frame;
	frame.ach_MACdst[0] = 0x00;
	frame.ach_MACdst[1] = 0x0d;
    frame.ach_MACdst[2] = 0x1f;
    frame.ach_MACdst[3] = 0x2f;
    frame.ach_MACdst[4] = 0x00;
    frame.ach_MACdst[5] = 0xff;

	for(i=0;i<6;i++) {
		printf("(%d * %d + %d ) %% %d = %d\n", PRIME, hash, (int)frame.ach_MACdst[i],HASH_TABLE,( PRIME * hash + (int)frame.ach_MACdst[i] ) % HASH_TABLE);
		hash = (PRIME * hash + (int)frame.ach_MACdst[i] ) % HASH_TABLE;
	}
	printf("final hash: %d\n", hash);

	return(0);
}
