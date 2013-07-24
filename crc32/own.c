#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <math.h>

unsigned reverse(unsigned x) {
   x = ((x & 0x55555555) <<  1) | ((x >>  1) & 0x55555555);
   x = ((x & 0x33333333) <<  2) | ((x >>  2) & 0x33333333);
   x = ((x & 0x0F0F0F0F) <<  4) | ((x >>  4) & 0x0F0F0F0F);
   x = (x << 24) | ((x & 0xFF00) << 8) | ((x >> 8) & 0xFF00) | (x >> 24);
   return x;
}

unsigned int crc32(unsigned char *message,int size) {
   int i, j;
   unsigned int byte, crc;

   i = 0;
   crc = 0xFFFFFFFF;
   for(i=0;i<size;++i) {
      byte = message[i];            // Get next byte.
      byte = reverse(byte);         // 32-bit reversal.
      for (j = 0; j <= 7; j++) {    // Do eight times.
         if ((int)(crc ^ byte) < 0)
              crc = (crc << 1) ^ 0x04C11DB7;
         else crc = crc << 1;
         byte = byte << 1;          // Ready next msg bit.
      }
      i = i + 1;
   }
   printf("cal: %08x %d\n",reverse(~crc),reverse(~crc));
   return reverse(~crc);
}

typedef struct {
	unsigned char ach_MACdst[6];
	unsigned char ach_MACsrc[6];
	int ach_Length;
	char ach_Payload[46]; // minimal
	unsigned char ach_crc[4]; // 32bit crc
} SFrame;

#pragma pack(1)
typedef struct {
	unsigned char ach_MACdst[6];
	unsigned char ach_MACsrc[6];
	int ach_Length;
	char ach_Payload[46]; // minimal
} __attribute__((packed))  SFrameCRC;


int main() {
	/* tworzenie frame */
	
	SFrame frame;
	frame.ach_MACsrc[0] = 0x00;
	frame.ach_MACsrc[1] = 0x0d;
	frame.ach_MACsrc[2] = 0x3f;
	frame.ach_MACsrc[3] = 0xff;
	frame.ach_MACsrc[4] = 0x12;
	frame.ach_MACsrc[5] = 0x5f;

	frame.ach_MACdst[0] = 0x00;
	frame.ach_MACdst[1] = 0x0d;
	frame.ach_MACdst[2] = 0x3f;
	frame.ach_MACdst[3] = 0xff;
	frame.ach_MACdst[4] = 0xff;
	frame.ach_MACdst[5] = 0xff;

	frame.ach_Length = 666;
	int du;
	for(du=0;du<46;++du) {
		frame.ach_Payload[du] = 0x00;
	}
	for(du=0;du<4;++du) {
		frame.ach_crc[du] = 0x00;
	}
	(void) strcpy(frame.ach_Payload,"DUAP");
	//(void) strcpy(frame.ach_crc,"42");
	
	printf("MACdst: %02x:%02x:%02x:%02x:%02x:%02x\n", frame.ach_MACdst[0], frame.ach_MACdst[1], frame.ach_MACdst[2], frame.ach_MACdst[3], frame.ach_MACdst[4], frame.ach_MACdst[5]);
	printf("MACsrc: %02x:%02x:%02x:%02x:%02x:%02x\n", frame.ach_MACsrc[0], frame.ach_MACsrc[1], frame.ach_MACsrc[2], frame.ach_MACsrc[3], frame.ach_MACsrc[4], frame.ach_MACsrc[5]);
	printf("Length: %d\n", frame.ach_Length);
	printf("Payload: %s\n", frame.ach_Payload);
	printf("CRC: %s\n", frame.ach_crc);

	SFrameCRC framecrc;
	for(du=0;du<46;++du) {
		framecrc.ach_Payload[du] = 0x00;
	}
	/* przepisywanie */
	
	int i;
	for(i=0;i<6;++i) {
		framecrc.ach_MACdst[i] = frame.ach_MACdst[i];
		framecrc.ach_MACsrc[i] = frame.ach_MACsrc[i];
	}

	framecrc.ach_Length  = frame.ach_Length;

	strcpy(framecrc.ach_Payload, frame.ach_Payload);

	printf("MACdst: %02x:%02x:%02x:%02x:%02x:%02x\n", framecrc.ach_MACdst[0], framecrc.ach_MACdst[1], framecrc.ach_MACdst[2], framecrc.ach_MACdst[3], framecrc.ach_MACdst[4], framecrc.ach_MACdst[5]);
	printf("MACsrc: %02x:%02x:%02x:%02x:%02x:%02x\n", framecrc.ach_MACsrc[0], framecrc.ach_MACsrc[1], framecrc.ach_MACsrc[2], framecrc.ach_MACsrc[3], framecrc.ach_MACsrc[4], framecrc.ach_MACsrc[5]);
	printf("Length: %d\n", framecrc.ach_Length);
	printf("Payload: %s\n", framecrc.ach_Payload);
	printf("================\n");
	unsigned char *text = (unsigned char*)&framecrc;
	//unsigned char *text;
	//text = "12345678";
	/*
	for(i=0;i<sizeof(framecrc);++i) {
		//printf("\"%03d\"",text[i]);
		printf("%02X ",text[i]);
	}
  	printf("\n");
	*/
	for(i=0;i<sizeof(framecrc);++i) {
		printf("%02d ", i);
	}
	printf("\n");
	printf("================\n");
	printf("CRC32 of frame 3e5a60d0\n");
	printf("CRC32 of frame %08x\n",crc32(text,sizeof(framecrc)));
	unsigned int checksum;
	checksum = crc32(text,sizeof(framecrc));
	printf("CRC32 of frame %08x\n",checksum);
	printf("================\n");
	printf("MACdst: %02x:%02x:%02x:%02x:%02x:%02x\n", frame.ach_MACdst[0], frame.ach_MACdst[1], frame.ach_MACdst[2], frame.ach_MACdst[3], frame.ach_MACdst[4], frame.ach_MACdst[5]);
	printf("MACsrc: %02x:%02x:%02x:%02x:%02x:%02x\n", frame.ach_MACsrc[0], frame.ach_MACsrc[1], frame.ach_MACsrc[2], frame.ach_MACsrc[3], frame.ach_MACsrc[4], frame.ach_MACsrc[5]);
	printf("Length: %d\n", frame.ach_Length);
	printf("Payload: %s\n", frame.ach_Payload);
	printf("CRC: %s\n", frame.ach_crc);
	printf("================\n");
	unsigned int x = 1046110416;//well, it should be just 1234.
	unsigned char* pChars;
	pChars = (unsigned char*) &x;
	printf("%02x %02x %02x %02x\n", pChars[3],pChars[2],pChars[1],pChars[0]);
	/*
	for(i=0;i<4;++i)
	{
		frame.ach_crc[i]=pChars[3-i];
		printf("%02x %02x %02x %02x ", pChars[3],pChars[2],pChars[1],pChars[0]);
		printf("%02x %02x %02x %02x\n", frame.ach_crc[0],frame.ach_crc[1],frame.ach_crc[2],frame.ach_crc[3]);
	}*/
	frame.ach_crc[0]=pChars[3];
	frame.ach_crc[1]=pChars[2];
	frame.ach_crc[2]=pChars[1];
	frame.ach_crc[3]=pChars[0];

	printf("MACdst: %02x:%02x:%02x:%02x:%02x:%02x\n", frame.ach_MACdst[0], frame.ach_MACdst[1], frame.ach_MACdst[2], frame.ach_MACdst[3], frame.ach_MACdst[4], frame.ach_MACdst[5]);
	printf("MACsrc: %02x:%02x:%02x:%02x:%02x:%02x\n", frame.ach_MACsrc[0], frame.ach_MACsrc[1], frame.ach_MACsrc[2], frame.ach_MACsrc[3], frame.ach_MACsrc[4], frame.ach_MACsrc[5]);
	printf("Length: %d\n", frame.ach_Length);
	printf("Payload: %s\n", frame.ach_Payload);
	printf("CRC: %02x%02x%02x%02x\n", frame.ach_crc[0],frame.ach_crc[1],frame.ach_crc[2],frame.ach_crc[3]);
	return(0);
	
}
