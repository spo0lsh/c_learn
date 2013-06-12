#include <stdio.h>
#include <stdlib.h>
#include "zadanie1.h"

/*
Stwórz tablicę o rozmiarze [1000][500][100] alokując ją dynamicznie.
Do każdego elementu przypisz iloczyn indeksów. Pamiętaj o zwolnieniu pamięci.
Podaj wzór w jaki sposób kompilator oblicza odwołanie do elementu [x][y][z].
*/

/*
M[i][j][k] ==>  *(*(*(M+i)+j)+k)
*/

int main() {
	tab3d(MAXX,MAXY,MAXZ);
	return(EXIT_SUCCESS);
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
	for(ix=0;ix<x;++ix) {
		for(iy=0;iy<y;++iy) {
			for(iz=0;iz<z;++iz) {
				Array[ix][iy][iz] = ix * iy * iz;
			}
		}
	}
				
	// print
	for(ix=0;ix<x;++ix) {
		for(iy=0;iy<y;++iy) {
			for(iz=0;iz<z;++iz) {
				printf("[%3d][%3d][%3d] = %3d ",ix, iy, iz,Array[ix][iy][iz]);
			}
		}
	}
	printf("\n");
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
