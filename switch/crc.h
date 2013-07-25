#ifndef __crc_H
#define __crc_H

#pragma pack(1)
typedef struct {
	unsigned char ach_MACdst[6];
	unsigned char ach_MACsrc[6];
	int ach_Length;
	char ach_Payload[46]; // minimal
} __attribute__((packed))  SFrameCRC;

unsigned fn_reverse(unsigned );
unsigned int fn_crc32(unsigned char * ,int );
int fn_crc_frame(SFrame *);

#endif /* __crc_H */
