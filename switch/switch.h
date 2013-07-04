#ifndef __switch_H
#define __switch_H
#define DEBUG

typedef struct {
	unsigned char ach_MACdst[6];
	unsigned char ach_MACsrc[6];
	int ach_Length;
	char ach_Payload[46]; // minimal
	char ach_crc[4]; // 32bit crc
} SFrame;

typedef int n_hash;

typedef struct {
	unsigned char ach_MACdst[6];
	unsigned char ach_MACsrc[6];
} SMAC;

typedef struct {
	unsigned int n_IFACEdst;
	unsigned int n_IFACEsrc;
} sIFACES;

void fn_pthread_recv(void *arg);
//void *pthread_send(void *arg);

#endif /* __switch_H */
