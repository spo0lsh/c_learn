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


void dupa(int);
void chuj(unsigned char[6] );

int main() {
	SFrame frame;
	
	frame.ach_MACdst[0] = 0x00;
	frame.ach_MACdst[1] = 0x0d;
    frame.ach_MACdst[2] = 0x3f;
    frame.ach_MACdst[3] = 0xff;
    frame.ach_MACdst[4] = 0x02;
    frame.ach_MACdst[5] = 0x5f;
	
	frame.ach_MACsrc[0] = 0x00;
	frame.ach_MACsrc[1] = 0x0d;
	frame.ach_MACsrc[2] = 0x3f;
	frame.ach_MACsrc[3] = 0xff;
	frame.ach_MACsrc[4] = 0xff;
	frame.ach_MACsrc[5] = 0xff;

	frame.ach_Length = 666;
	(void) strcpy(frame.ach_Payload,"DUAP");
	(void) strcpy(frame.ach_crc,"42");
	
	printf("Length %d\n", frame.ach_Length);
	dupa(frame.ach_Length);
	chuj(frame.ach_MACsrc);
	return(0);
}


void dupa(int a) {
	printf("DUPA %d\n", a);
}


void chuj(unsigned char ach_MACsrc[6]) {
	printf("[CHUJ] MACsrc: %02x:%02x:%02x:%02x:%02x:%02x\n", ach_MACsrc[0], ach_MACsrc[1], ach_MACsrc[2], ach_MACsrc[3], ach_MACsrc[4], ach_MACsrc[5]);
}
