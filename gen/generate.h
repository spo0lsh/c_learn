#ifndef __generate_H
#define __generate_H

#pragma pack(1)
typedef struct {
	unsigned char ach_MACdst[6];
	unsigned char ach_MACsrc[6];
	int ach_Length;
	char ach_Payload[46]; // minimal
} __attribute__((packed))  SFrameCRC;

typedef struct {
	unsigned char ach_MACdst[6];
	unsigned char ach_MACsrc[6];
	int ach_Length;
	char ach_Payload[46]; // minimal
	unsigned char ach_crc[4]; // 32bit crc
} SFrame;

unsigned fn_reverse(unsigned );
unsigned int fn_crc32(unsigned char * ,int );
unsigned int fn_crc_frame(SFrame *);

typedef struct msgbuf {
	long    mtype;
	SFrame frame;
} message_buf;

#endif /* __generate_H */
