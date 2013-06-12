#include <stdio.h>
#include <stdlib.h>
#include "zadanie1.h"

/*
Stwórz tablicę o rozmiarze [1000][500][100] alokując ją dynamicznie.
Do każdego elementu przypisz iloczyn indeksów. Pamiętaj o zwolnieniu pamięci.
Podaj wzór w jaki sposób kompilator oblicza odwołanie do elementu [x][y][z].
*/

int main() {
	int x,y,z;
	test();
	tab1d(150);
	//tab2d(x,y);
	//tab3d(x,y,z);
	return(EXIT_SUCCESS);
}


void test() {
	printf("%d %d %d \n",MAXX, MAXY, MAXZ);
}

void tab1d(int x) {
	//create
	int ix;
	int* Array;
	Array = (int*) malloc(sizeof(int)*x);
	
	if(Array == NULL)
		exit(EXIT_FAILURE);
	
	
	// filling
	for(ix=0;ix<x;++ix) {
		Array[ix]=ix;
	}
	
	//print
	for(ix=0;ix<x;++ix) {
		printf("%d\t", Array[ix]+1);
		if((ix+1) % 10 == 0)
			printf("\n");
	}
	printf("\n");
	
	//free
	free((void *) Array);
	Array=NULL;
}

void tab2d(int x, int y) {
	for(x=0;x<10;++x) {
		for(y=0;y<10;++y) {
			printf("%d x %d ", x+1,y+1);
			if((y+1) % 10 == 0)
				printf("\n");
		}
	}
	printf("\n");
}

void tab3d(int x, int y, int z) {
	for(x=0;x<10;++x) {
		for(y=0;y<10;++y) {
			for(z=0;z<10;++z) {
				printf("%d x %d x %d ", x+1,y+1,z+1);
				if((z+1) % 5 == 0)
					printf("\n");
			}
		}
	}
	printf("\n");
}
