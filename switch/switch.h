#ifndef __switch_H
#define __switch_H

typedef struct {
	char ach_MACdst[6];
	char ach_MACsrc[6];
	char ach_Length[2];
	char ach_Payload[46]; // minimal
	char ach_crc[4]; // 32bit crc
} SFrame;

typedef int n_hash;

typedef struct {
	char ach_MACdst[6];
	char ach_MACsrc[6];
} SMAC;

typedef struct {
	int n_IFACEdst;
	int n_IFACEsrc;
} sIFACES;

#endif /* __switch_H */
