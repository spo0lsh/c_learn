#define SWITCH 16 // number of bridgeports
#define MAC 16 // mac table = SWITCH * MAC
#define HASH_TABLE SWITCH * MAC // mac table = SWITCH * MAC

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
    frame.ach_MACdst[2] = 0x3f;
    frame.ach_MACdst[3] = 0xff;
    frame.ach_MACdst[4] = 0x02;
    frame.ach_MACdst[5] = 0x5f;
	//char dupa[20] = "japierdole";
	
	if(argc < 2) {
		printf("error!\n");
		return(1);
	} else {
		printf("%s\n", argv[1]);
	}
	for(i=0;i<strlen(argv[1]);i++){
		//printf("(7 * %d + %d ) % 32 = %d\n", hash, (int)argv[1][i],(7 * hash + (int)argv[1][i]) % HASH_TABLE);
		hash = (7 * hash + (int)argv[1][i]) % HASH_TABLE;
	}
	printf("final hash: %d\n", hash);
    
	return(0);
}
