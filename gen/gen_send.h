#ifndef __gen_send_H
#define __gen_send_H

typedef struct {
	unsigned char ach_MACdst[6];
	unsigned char ach_MACsrc[6];
	int ach_Length;
	char ach_Payload[46]; // minimal
	char ach_crc[4]; // 32bit crc
} SFrame;

typedef struct msgbuf {
	long    mtype;
	SFrame frame;
} message_buf;

#endif /* __gen_send_H */
