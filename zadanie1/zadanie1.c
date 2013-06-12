#include <stdio.h>
#include <stdlib.h>
#include "zadanie1.h"

/*
Stwórz tablicę o rozmiarze [1000][500][100] alokując ją dynamicznie.
Do każdego elementu przypisz iloczyn indeksów. Pamiętaj o zwolnieniu pamięci.
Podaj wzór w jaki sposób kompilator oblicza odwołanie do elementu [x][y][z].
*/

int main() {
	test();
	//tab1d(20);
	//tab2d(7,7);
	tab3d(2,3,4);
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
	// create
	int ix;
	int iy;
	int **Array = (int **) malloc(sizeof(int *) * x);
	if(Array == NULL)
		exit(EXIT_FAILURE);
	for(ix=0;ix<x;++ix) {
		Array[ix] = (int*) malloc(sizeof(int) * y);
		if(Array[ix] == NULL) {
			for(ix=0;ix<x;++ix) {
				free(Array[ix]);
				Array[ix]=NULL;
			}
			exit(EXIT_FAILURE);
		}
	}

	// filling
	for(ix=0;ix<x;++ix) {
		for(iy=0;iy<y;++iy) {
			Array[ix][iy] = ix * iy;
		}
	}

	// print
	for(ix=0;ix<x;++ix) {
		for(iy=0;iy<y;++iy) {
			printf("%3d x %3d = %3d ", ix, iy, Array[ix][iy]);
			if((iy+1) % 5 == 0)
				printf("\n");
		}
	}
	printf("\n");
	
	//free
	for(ix=0;ix<x;++ix) {
		free(Array[ix]);
		Array[ix]=NULL;
	}
	free((void *) Array);
	Array=NULL;
}

void tab3d(int x, int y, int z) {
	// create
	int ix;
	int iy;
	int iz;
	// add clean!
	int ***Array = (int ***) malloc(sizeof(int **) * x);
	for(ix=0;ix<x;++ix) {
		Array[ix] = (int **) malloc(sizeof(int *) * y);
		for(iy=0;iy<y;++iy) {
			Array[ix][iy] = (int*) malloc(sizeof(int) * z);
		}
	}
	
	// filling
	// print
	// free
	for(ix=0;ix<x;++ix) {
		Array[ix] = (int **) malloc(sizeof(int *) * y);
		for(iy=0;iy<y;++iy) {
			free((void *) Array[ix][iy]);
			Array[ix][iy]=NULL;
		}
		free((void *) Array[ix]);
		Array[ix]=NULL;
	}
	free((void *) Array);
	Array=NULL;
}
