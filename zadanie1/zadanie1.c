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
	int ***Array;
	Array=tab3d_create();
	// filling
	tab3d_filling(Array);
	// print
	tab3d_print(Array);
	// free
	tab3d_free(Array);
}

int ***tab3d_create() {
	/*
	Tworzymy 3d array i zwracamy wskaźnik do niej
	*/
	int ix;
	int iy;
	int ***Array = (int ***) malloc(sizeof(int **) * MAXX);
	//something wrong -> clean
	if(Array == NULL) {
		free(Array);
		Array=NULL;
		exit(EXIT_FAILURE);
	}
	for(ix=0;ix<MAXX;++ix) {
		Array[ix] = (int **) malloc(sizeof(int *) * MAXY);
		//something wrong -> clean
		if(Array[ix] == NULL) {
			for(ix=0;ix<MAXX;++ix) {
				free(Array[ix]);
				Array[ix]=NULL;
			}
			free(Array);
			Array=NULL;
			exit(EXIT_FAILURE);
		}
		for(iy=0;iy<MAXY;++iy) {
			Array[ix][iy] = (int*) malloc(sizeof(int) * MAXZ);
			//something wrong -> clean
			if(Array[ix][iy] == NULL) {
				for(iy=0;iy<MAXY;++iy) {
					free(Array[ix][iy]);
					Array[ix][iy]=NULL;
				}
				for(ix=0;ix<MAXX;++ix) {
					free(Array[ix]);
					Array[ix]=NULL;
				}
				free(Array);
				Array=NULL;
				exit(EXIT_FAILURE);
			}
		}
	}
	return(Array);
}
void tab3d_filling(int (***Array)) {
	/*
	Wypełniamy tablicę śmieciami
	*/
	int ix;
	int iy;
	int iz;
	for(ix=0;ix<MAXX;++ix) {
		for(iy=0;iy<MAXY;++iy) {
			for(iz=0;iz<MAXZ;++iz) {
				Array[ix][iy][iz] = ix * iy * iz;
			}
		}
	}
}
void tab3d_print(int (***Array)) {
	/*
	Wyświetlamy zawartość tablicy (jakby nas to interesowało)
	*/
	int ix;
	int iy;
	int iz;
	for(ix=0;ix<MAXX;++ix) {
		for(iy=0;iy<MAXY;++iy) {
			for(iz=0;iz<MAXZ;++iz) {
				printf ("[%3d][%3d][%3d]\n",ix, iy, iz); //printf("[%3d][%3d][%3d] = %3d ",ix, iy, iz,Array[ix][iy][iz]);
			}
		}
	}
	printf("\n");
}
void tab3d_free(int (***Array)) {
	/*
	Usuwamy 3d array za pamięci
	*/
	int ix;
	int iy;
	for(ix=0;ix<MAXX;++ix) {
		for(iy=0;iy<MAXY;++iy) {
			free((void *) Array[ix][iy]);
			Array[ix][iy]=NULL;
		}
		free((void *) Array[ix]);
		Array[ix]=NULL;
	}
	free((void *) Array);
	Array=NULL;
}
