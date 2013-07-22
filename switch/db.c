#define PRIME 3

#include <stdio.h>
#include "db.h"
#include "switch.h"
#include <stdlib.h>

sHashTable *fn_create_hash() {
	#ifdef DEBUG
	printf("Creating database\n");
	printf("Size: %d\n", HASH_TABLE);
	#endif
	sHashTable *asHASH = (sHashTable *) malloc(sizeof(sHashTable) * HASH_TABLE);
	//sHashTable sHASH[HASH_TABLE];
	return(asHASH);
}

void fn_destroy_hash() {
	printf("Removing database\n");
	//free((void *) asHASH);
	//asHASH=NULL;
}

int fn_hash() { // HASH
	int i;
	int hash;
	hash=0;
	for(i=0;i<6;++i) {
		#ifdef DEBUG
		//printf("(%d * %d + %d ) %% %d = %d\n", PRIME, hash, (int)frame.ach_MACsrc[i],HASH_TABLE,( PRIME * hash + (int)frame.ach_MACdst[i] ) % HASH_TABLE);
		#endif
		//hash = (PRIME * hash + (int)frame.ach_MACdst[i] ) % HASH_TABLE;
	}
	return hash;
}

void fn_remove() { // status
}

void fn_add_srcmac() { // status
}

void fn_search_rm() { // 
}

void fn_entry() { // single entry
}

void fn_readfile() { //
}
