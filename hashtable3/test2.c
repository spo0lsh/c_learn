#define SWITCH 2 // number of bridgeports
#define MAC 16 // mac table = SWITCH * MAC
#define HASH_TABLE (SWITCH * MAC) // mac table = SWITCH * MAC

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	unsigned char ach_MACsrc[6];
	int n_Port;
	int n_Age;
	int n_Filter;
} sHashTable;

sHashTable *asHASH;
int main() {
	sHashTable *asHASH = (sHashTable *) malloc(sizeof(sHashTable) * HASH_TABLE);
	
	asHASH[0].n_Age = 1;
	printf("%d\n", asHASH[0].n_Age);
	printf("%d\n", asHASH[1].n_Age);
	asHASH[30].n_Age = 1123;
	printf("%d\n", asHASH[30].n_Age);
}
