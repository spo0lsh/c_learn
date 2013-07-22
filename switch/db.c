#define PRIME 3

#include <stdio.h>
#include "db.h"
#include "switch.h"
#include <stdlib.h>
#include "aging.h"
#include <time.h>

sHashTable *fn_create_hash() {
	#ifdef DEBUG
	printf("Creating database\n");
	printf("Size: %d\n", HASH_TABLE);
	#endif
	sHashTable *asHASH = (sHashTable *) malloc(sizeof(sHashTable) * HASH_TABLE);
	//sHashTable sHASH[HASH_TABLE];
	return(asHASH);
}

void fn_destroy_hash(sHashTable * Array) {
	printf("Removing database\n");
	free((void *) Array);
	Array=NULL;
}

int fn_hash(unsigned char ach_MAC[6]) { // HASH
	int i;
	int hash;
	hash=0;
	printf("[HASH] %02x:%02x:%02x:%02x:%02x:%02x\n", ach_MAC[0], ach_MAC[1], ach_MAC[2], ach_MAC[3], ach_MAC[4], ach_MAC[5]);
	for(i=0;i<6;++i) {
		//#ifdef DEBUG
		//printf("(%d * %d + %d ) %% %d = %d\n", PRIME, hash, (int)ach_MACsrc[i],HASH_TABLE,( PRIME * hash + (int)ach_MACsrc[i] ) % HASH_TABLE);
		//#endif
		hash = (PRIME * hash + (int)ach_MAC[i] ) % HASH_TABLE;
	}
	return hash;
}

void fn_remove(unsigned char ach_MACsrc[6]) { // status
	int hash = fn_hash(ach_MACsrc);
	asHASH[hash].ach_MACsrc[0] = 0;
	asHASH[hash].ach_MACsrc[1] = 0;
	asHASH[hash].ach_MACsrc[2] = 0;
	asHASH[hash].ach_MACsrc[3] = 0;
	asHASH[hash].ach_MACsrc[4] = 0;
	asHASH[hash].ach_MACsrc[5] = 0;
	asHASH[hash].n_Port = 0;
	asHASH[hash].n_Age = 0;
	asHASH[hash].n_Filter = 0;
}

void fn_add_srcmac(unsigned char ach_MACsrc[6],int bridgeport) { // status
	time_t now;
	time(&now);
	#ifdef DEBUG
	printf("[DB] add %02x:%02x:%02x:%02x:%02x:%02x into %d port %d AGING %ld now: %ld\n", ach_MACsrc[0], ach_MACsrc[1], ach_MACsrc[2], ach_MACsrc[3], ach_MACsrc[4], ach_MACsrc[5],fn_hash(ach_MACsrc)+1,bridgeport,AGING+now,now);
	#endif
	int hash = fn_hash(ach_MACsrc);
	asHASH[hash].ach_MACsrc[0] = ach_MACsrc[0];
	asHASH[hash].ach_MACsrc[1] = ach_MACsrc[1];
	asHASH[hash].ach_MACsrc[2] = ach_MACsrc[2];
	asHASH[hash].ach_MACsrc[3] = ach_MACsrc[3];
	asHASH[hash].ach_MACsrc[4] = ach_MACsrc[4];
	asHASH[hash].ach_MACsrc[5] = ach_MACsrc[5];
	asHASH[hash].n_Port=bridgeport;
	asHASH[hash].n_Age=AGING+now;
	asHASH[hash].n_Filter=0;
}

void fn_search_rm() { // 
}

void fn_entry() { // single entry
	#ifdef DEBUG
	//printf("[DB] adding %02x:%02x:%02x:%02x:%02x:%02x into %d bridgeport %d AGING %d\n", ach_MACsrc[0], ach_MACsrc[1], ach_MACsrc[2], ach_MACsrc[3], ach_MACsrc[4], ach_MACsrc[5],fn_hash(ach_MACsrc),bridgeport,AGING);
	#endif
}

void fn_readfile() { //
}

void fn_hash_show() {
	int n_i;
	for(n_i=0;n_i<HASH_TABLE;++n_i) {
		printf("[%d]. ",n_i+1);
		printf("%02x:%02x:%02x:%02x:%02x:%02x ", asHASH[n_i].ach_MACsrc[0], asHASH[n_i].ach_MACsrc[1], asHASH[n_i].ach_MACsrc[2], asHASH[n_i].ach_MACsrc[3], asHASH[n_i].ach_MACsrc[4], asHASH[n_i].ach_MACsrc[5]);
		printf("%d, %d, %d\n", asHASH[n_i].n_Port, asHASH[n_i].n_Age, asHASH[n_i].n_Filter);
		
		
	}
}	
/*
	unsigned char ach_MACsrc[6];
	int n_Port;
	int n_Age;
	int n_Filter;
*/
