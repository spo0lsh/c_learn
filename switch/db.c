#define PRIME 3
#define CONFIGFILE "configfile.txt"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "db.h"
#include "switch.h"
#include "aging.h"

sHashTable *fn_create_hash() {
	#ifdef DEBUG
	printf("Creating database\n");
	printf("Size: %d\n", HASH_TABLE);
	#endif
	sHashTable *pas_HASH = (sHashTable *) malloc(sizeof(sHashTable) * HASH_TABLE);
	//sHashTable sHASH[HASH_TABLE];
	return(pas_HASH);
}

void fn_destroy_hash(sHashTable * pa_HASH) {
	printf("Removing database\n");
	free((void *) pa_HASH);
	pa_HASH=NULL;
}

int fn_hash(unsigned char ach_MAC[6]) { // HASH
	int n_i;
	int n_hash;
	n_hash=0;
	#ifdef DEBUG
	printf("[HASH] %02x:%02x:%02x:%02x:%02x:%02x\n", ach_MAC[0], ach_MAC[1], ach_MAC[2], ach_MAC[3], ach_MAC[4], ach_MAC[5]);
	#endif
	for(n_i=0;n_i<6;++n_i) {
		//#ifdef DEBUG
		//printf("(%d * %d + %d ) %% %d = %d\n", PRIME, n_hash, (int)ach_MACsrc[i],HASH_TABLE,( PRIME * n_hash + (int)ach_MACsrc[i] ) % HASH_TABLE);
		//#endif
		n_hash = (PRIME * n_hash + (int)ach_MAC[n_i] ) % HASH_TABLE;
	}
	return n_hash;
}

void fn_remove(int n_hash) { // status
	#ifdef DEBUG
	printf("[DB] before remove\n");
	printf("%02x:%02x:%02x:%02x:%02x:%02x ", pas_HASH[n_hash].ach_MACsrc[0], pas_HASH[n_hash].ach_MACsrc[1], pas_HASH[n_hash].ach_MACsrc[2], pas_HASH[n_hash].ach_MACsrc[3], pas_HASH[n_hash].ach_MACsrc[4], pas_HASH[n_hash].ach_MACsrc[5]);
	printf("%d, %d, %d\n", pas_HASH[n_hash].n_Port, pas_HASH[n_hash].n_Age, pas_HASH[n_hash].n_Filter);
	#endif
	pas_HASH[n_hash].ach_MACsrc[0] = 0;
	pas_HASH[n_hash].ach_MACsrc[1] = 0;
	pas_HASH[n_hash].ach_MACsrc[2] = 0;
	pas_HASH[n_hash].ach_MACsrc[3] = 0;
	pas_HASH[n_hash].ach_MACsrc[4] = 0;
	pas_HASH[n_hash].ach_MACsrc[5] = 0;
	pas_HASH[n_hash].n_Port = 0;
	pas_HASH[n_hash].n_Age = 0;
	pas_HASH[n_hash].n_Filter = 0;
	#ifdef DEBUG
	printf("[DB] after remove\n");
	printf("%02x:%02x:%02x:%02x:%02x:%02x ", pas_HASH[n_hash].ach_MACsrc[0], pas_HASH[n_hash].ach_MACsrc[1], pas_HASH[n_hash].ach_MACsrc[2], pas_HASH[n_hash].ach_MACsrc[3], pas_HASH[n_hash].ach_MACsrc[4], pas_HASH[n_hash].ach_MACsrc[5]);
	printf("%d, %d, %d\n", pas_HASH[n_hash].n_Port, pas_HASH[n_hash].n_Age, pas_HASH[n_hash].n_Filter);
	#endif
}

void fn_add_srcmac(unsigned char ach_MACsrc[6],int n_bridgeport,int n_filter) { // status
	time_t now;
	time(&now);
	#ifdef DEBUG
	printf("[DB] add %02x:%02x:%02x:%02x:%02x:%02x into %d port %d AGING %ld now: %ld\n", ach_MACsrc[0], ach_MACsrc[1], ach_MACsrc[2], ach_MACsrc[3], ach_MACsrc[4], ach_MACsrc[5],fn_hash(ach_MACsrc)+1,n_bridgeport,n_aging+now,now);
	#endif
	int hash = fn_hash(ach_MACsrc);
	pas_HASH[hash].ach_MACsrc[0] = ach_MACsrc[0];
	pas_HASH[hash].ach_MACsrc[1] = ach_MACsrc[1];
	pas_HASH[hash].ach_MACsrc[2] = ach_MACsrc[2];
	pas_HASH[hash].ach_MACsrc[3] = ach_MACsrc[3];
	pas_HASH[hash].ach_MACsrc[4] = ach_MACsrc[4];
	pas_HASH[hash].ach_MACsrc[5] = ach_MACsrc[5];
	pas_HASH[hash].n_Port=n_bridgeport;
	pas_HASH[hash].n_Age=n_aging+now;
	pas_HASH[hash].n_Filter=n_filter;
}

void fn_search_rm() { // 
	int n_i;
	time_t s_now;
	time(&s_now);
	#ifdef DEBUG
	printf("Now is %ld\n", s_now);
	#endif
	for(n_i=0;n_i<HASH_TABLE;n_i++) {
		if(pas_HASH[n_i].n_Age < s_now && pas_HASH[n_i].n_Age  != 0 && pas_HASH[n_i].n_Filter != 1 ) {
			#ifdef DEBUG
			printf("[DB]Removing hash %d\n",n_i);
			#endif
			fn_remove(n_i);
		}
	}
	#ifdef DEBUG
	printf("Now is %ld\n", s_now);
	#endif
}

void fn_entry() { // single entry
	#ifdef DEBUG
	//printf("[DB] adding %02x:%02x:%02x:%02x:%02x:%02x into %d bridgeport %d AGING %d\n", ach_MACsrc[0], ach_MACsrc[1], ach_MACsrc[2], ach_MACsrc[3], ach_MACsrc[4], ach_MACsrc[5],fn_hash(ach_MACsrc),bridgeport,n_aging);
	#endif
}

void fn_readfile() { //
	#ifdef DEBUG
	printf("[DB] Reading config file\n");
	#endif
	FILE *fp;
	fp=NULL;
	char * pch_line = NULL;
	size_t len = 0;
	ssize_t s_read;
	int n_i;
	n_i=0;
	int ai_tmp[12];
	unsigned char ach_MAC[6];
	n_aging=AGING;
	fp=fopen(CONFIGFILE, "r");
	if (fp == NULL) {
        perror("Fail open configfile.txt");
    } else {
		while ((s_read = getline(&pch_line, &len, fp)) != -1) {
			++n_i;
			#ifdef DEBUG
			printf("Retrieved line %d of length %zu :\n", n_i, s_read);
			#endif
			if(n_i == 1) {
				n_aging=atoi(pch_line);
				printf("[FIRST] %s", pch_line);
			} else {
				printf("%s", pch_line);
				if(pch_line[0] != '\n' ) {
					for(n_i=0;n_i<12;++n_i) {
						if(pch_line[n_i] < 97 ) {
							ai_tmp[n_i] = (pch_line[n_i] - 48 );
						} else {
							ai_tmp[n_i] = (pch_line[n_i] - 87 );
						}
					}
					ach_MAC[0] = (ai_tmp[0] * 16 + ai_tmp[1]) & 0xFF;
					ach_MAC[1] = (ai_tmp[2] * 16 + ai_tmp[3]) & 0xFF;
					ach_MAC[2] = (ai_tmp[4] * 16 + ai_tmp[5]) & 0xFF;
					ach_MAC[3] = (ai_tmp[6] * 16 + ai_tmp[7]) & 0xFF;
					ach_MAC[4] = (ai_tmp[8] * 16 + ai_tmp[9]) & 0xFF;
					ach_MAC[5] = (ai_tmp[10] * 16 + ai_tmp[11]) & 0xFF;
					#ifdef DEBUG
					printf("MAC: %02x:%02x:%02x:%02x:%02x:%02x port %d\n", ach_MAC[0], ach_MAC[1], ach_MAC[2], ach_MAC[3], ach_MAC[4], ach_MAC[5], atoi(&pch_line[13]));
					#endif
					fn_add_srcmac(ach_MAC,atoi(&pch_line[13]),1);
				}
			}
		}
		#ifdef DEBUG
		printf("Aging %d\n", n_aging);
		#endif
		free(pch_line);
		pch_line=NULL;
		fclose(fp);
	}
}

void fn_hash_show() {
	int n_i;
	for(n_i=0;n_i<HASH_TABLE;++n_i) {
		printf("[%d]. ",n_i+1);
		printf("%02x:%02x:%02x:%02x:%02x:%02x ", pas_HASH[n_i].ach_MACsrc[0], pas_HASH[n_i].ach_MACsrc[1], pas_HASH[n_i].ach_MACsrc[2], pas_HASH[n_i].ach_MACsrc[3], pas_HASH[n_i].ach_MACsrc[4], pas_HASH[n_i].ach_MACsrc[5]);
		printf("%d, %d, %d\n", pas_HASH[n_i].n_Port, pas_HASH[n_i].n_Age, pas_HASH[n_i].n_Filter);
	}
}	
/*
	unsigned char ach_MACsrc[6];
	int n_Port;
	int n_Age;
	int n_Filter;
*/
