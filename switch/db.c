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

void fn_remove(int hash) { // status
	//int hash = fn_hash(ach_MACsrc);
	#ifdef DEBUG
	printf("[DB] before remove\n");
	printf("%02x:%02x:%02x:%02x:%02x:%02x ", asHASH[hash].ach_MACsrc[0], asHASH[hash].ach_MACsrc[1], asHASH[hash].ach_MACsrc[2], asHASH[hash].ach_MACsrc[3], asHASH[hash].ach_MACsrc[4], asHASH[hash].ach_MACsrc[5]);
	printf("%d, %d, %d\n", asHASH[hash].n_Port, asHASH[hash].n_Age, asHASH[hash].n_Filter);
	#endif
	asHASH[hash].ach_MACsrc[0] = 0;
	asHASH[hash].ach_MACsrc[1] = 0;
	asHASH[hash].ach_MACsrc[2] = 0;
	asHASH[hash].ach_MACsrc[3] = 0;
	asHASH[hash].ach_MACsrc[4] = 0;
	asHASH[hash].ach_MACsrc[5] = 0;
	asHASH[hash].n_Port = 0;
	asHASH[hash].n_Age = 0;
	asHASH[hash].n_Filter = 0;
	#ifdef DEBUG
	printf("[DB] after remove\n");
	printf("%02x:%02x:%02x:%02x:%02x:%02x ", asHASH[hash].ach_MACsrc[0], asHASH[hash].ach_MACsrc[1], asHASH[hash].ach_MACsrc[2], asHASH[hash].ach_MACsrc[3], asHASH[hash].ach_MACsrc[4], asHASH[hash].ach_MACsrc[5]);
	printf("%d, %d, %d\n", asHASH[hash].n_Port, asHASH[hash].n_Age, asHASH[hash].n_Filter);
	#endif
}

void fn_add_srcmac(unsigned char ach_MACsrc[6],int bridgeport,int filter) { // status
	time_t now;
	time(&now);
	#ifdef DEBUG
	printf("[DB] add %02x:%02x:%02x:%02x:%02x:%02x into %d port %d AGING %ld now: %ld\n", ach_MACsrc[0], ach_MACsrc[1], ach_MACsrc[2], ach_MACsrc[3], ach_MACsrc[4], ach_MACsrc[5],fn_hash(ach_MACsrc)+1,bridgeport,aging+now,now);
	#endif
	int hash = fn_hash(ach_MACsrc);
	asHASH[hash].ach_MACsrc[0] = ach_MACsrc[0];
	asHASH[hash].ach_MACsrc[1] = ach_MACsrc[1];
	asHASH[hash].ach_MACsrc[2] = ach_MACsrc[2];
	asHASH[hash].ach_MACsrc[3] = ach_MACsrc[3];
	asHASH[hash].ach_MACsrc[4] = ach_MACsrc[4];
	asHASH[hash].ach_MACsrc[5] = ach_MACsrc[5];
	asHASH[hash].n_Port=bridgeport;
	asHASH[hash].n_Age=aging+now;
	asHASH[hash].n_Filter=filter;
}

void fn_search_rm() { // 
	int i;
	time_t now;
	time(&now);
	#ifdef DEBUG
	printf("Now is %ld\n", now);
	#endif
	for(i=0;i<HASH_TABLE;i++) {
		//if(asHASH[i].n_Port != 0 && asHASH[i].n_Age < now && asHASH[i].n_Filter != 0 ) {
		if(asHASH[i].n_Age < now && asHASH[i].n_Age  != 0 && asHASH[i].n_Filter != 1 ) {
			#ifdef DEBUG
			printf("[DB]Removing hash %d\n",i);
			#endif
			fn_remove(i);
		}
	}
	#ifdef DEBUG
	printf("Now is %ld\n", now);
	#endif
}

void fn_entry() { // single entry
	#ifdef DEBUG
	//printf("[DB] adding %02x:%02x:%02x:%02x:%02x:%02x into %d bridgeport %d AGING %d\n", ach_MACsrc[0], ach_MACsrc[1], ach_MACsrc[2], ach_MACsrc[3], ach_MACsrc[4], ach_MACsrc[5],fn_hash(ach_MACsrc),bridgeport,aging);
	#endif
}

void fn_readfile() { //
	#ifdef DEBUG
	printf("[DB] Reading config file\n");
	#endif
	FILE *fp;
	fp=NULL;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int i;
	i=0;
	int ai_tmp[12];
	unsigned char ach_MAC[6];
	aging=AGING;
	fp=fopen(CONFIGFILE, "r");
	if (fp == NULL) {
        perror("Fail open configfile.txt");
    } else {
		while ((read = getline(&line, &len, fp)) != -1) {
			++i;
			#ifdef DEBUG
			printf("Retrieved line %d of length %zu :\n", i, read);
			#endif
			if(i == 1) {
				aging=atoi(line);
				printf("[FIRST] %s", line);
			} else {
				printf("%s", line);
				if(line[0] != '\n' ) {
					for(i=0;i<12;++i) {
						if(line[i] < 97 ) {
							ai_tmp[i] = (line[i] - 48 );
						} else {
							ai_tmp[i] = (line[i] - 87 );
						}
					}
					ach_MAC[0] = (ai_tmp[0] * 16 + ai_tmp[1]) & 0xFF;
					ach_MAC[1] = (ai_tmp[2] * 16 + ai_tmp[3]) & 0xFF;
					ach_MAC[2] = (ai_tmp[4] * 16 + ai_tmp[5]) & 0xFF;
					ach_MAC[3] = (ai_tmp[6] * 16 + ai_tmp[7]) & 0xFF;
					ach_MAC[4] = (ai_tmp[8] * 16 + ai_tmp[9]) & 0xFF;
					ach_MAC[5] = (ai_tmp[10] * 16 + ai_tmp[11]) & 0xFF;
					#ifdef DEBUG
					printf("MAC: %02x:%02x:%02x:%02x:%02x:%02x port %d\n", ach_MAC[0], ach_MAC[1], ach_MAC[2], ach_MAC[3], ach_MAC[4], ach_MAC[5], atoi(&line[13]));
					#endif
					fn_add_srcmac(ach_MAC,atoi(&line[13]),1);
				}
			}
		}
		#ifdef DEBUG
		printf("Aging %d\n", aging);
		#endif
		free(line);
		fclose(fp);
	}
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
