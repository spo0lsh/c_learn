#ifndef __switch_H
#define __switch_H
#define DEBUG
#define SWITCH 4 // number of bridgeports
#define MAC 8 // mac table = SWITCH * MAC
#define HASH_TABLE (SWITCH * MAC) // mac table = SWITCH * MAC
#define MSQKEYRECV 1000 // key for MQ recv
#define MSQKEYSEND 1100 // key for MQ send

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

void fn_pthread_bridgeport(void *arg);
void fn_pthread_aging(void *arg);
void fn_generate_interafaces();
void fn_remove_interafaces();
#endif /* __switch_H */
