#define PRIME 3

#include <stdio.h>
#include "db.h"
#include "switch.h"
#include <stdlib.h>
#include "aging.h"

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

int fn_hash(unsigned char ach_MACsrc[6]) { // HASH
	int i;
	int hash;
	hash=0;
	for(i=0;i<6;++i) {
		//#ifdef DEBUG
		//printf("(%d * %d + %d ) %% %d = %d\n", PRIME, hash, (int)ach_MACsrc[i],HASH_TABLE,( PRIME * hash + (int)ach_MACsrc[i] ) % HASH_TABLE);
		//#endif
		hash = (PRIME * hash + (int)ach_MACsrc[i] ) % HASH_TABLE;
	}
	return hash;
}

void fn_remove() { // status
}

void fn_add_srcmac(unsigned char ach_MACsrc[6],int bridgeport) { // status
	#ifdef DEBUG
	printf("[DB] adding %02x:%02x:%02x:%02x:%02x:%02x into %d bridgeport %d AGING %d\n", ach_MACsrc[0], ach_MACsrc[1], ach_MACsrc[2], ach_MACsrc[3], ach_MACsrc[4], ach_MACsrc[5],fn_hash(ach_MACsrc),bridgeport,AGING);
	//fn_hash(frame->ach_MACsrc)
	#endif
	//asHASH->n_Port=bridgeport;
}

void fn_search_rm() { // 
}

void fn_entry() { // single entry
}

void fn_readfile() { //
}

void fn_hash_show(sHashTable *Array) {
//void fn_hash_show() {
	int n_i;
	for(n_i=0;n_i<HASH_TABLE;++n_i) {
		printf("[%d]. ",n_i+1);
		printf("%02x:%02x:%02x:%02x:%02x:%02x ", Array->ach_MACsrc[0], Array->ach_MACsrc[1], Array->ach_MACsrc[2], Array->ach_MACsrc[3], Array->ach_MACsrc[4], Array->ach_MACsrc[5]);
		printf("%d, %d, %d\n", Array->n_Port, Array->n_Age, Array->n_Filter);
	}
}

/*
	unsigned char ach_MACsrc[6];
	int n_Port;
	int n_Age;
	int n_Filter;
*/
