#include <stdio.h>
#include <stdlib.h>
#include "zadanie2.h"

/*
Stwórz:
Tablicę wskaźników do funkcji (dynamicznie).
Funkcję „void init()”, która wypełnia tę tablicę wskaźnikami do funkcji wypisującej błąd.
Stwórz typ (typedef enum) który będzie odpowiadał indeksowi do tablicy (tzn. dla pewnej 
 wartości wywołaj pewną funkcję).
Funkcję która dodaje to tablicy funkcję podaną w parametrze. Indeksem powinien być stworzony 
 wcześniej typ wyliczeniowy (również podany w parametrze).
Funkcję, która wywołuję funkcję z tablicy na podstawie otrzymanego parametru wyliczeniowego.
Pod uwagę będą brane zabezpieczenia przed wykroczeniem poza tablicę oraz usuwanie 
 zadeklarowanej pamięci.
*/

int main() {
	fun_ptr *Array;
	Array=create();

	init(Array);
	call(Array,HANDLE1);
	call(Array,HANDLE4);
	add(Array,HANDLE1, &example);
	add(Array,HANDLE4, &example);
	call(Array,HANDLE1);
	delete(Array);
	return(EXIT_SUCCESS);
}

fun_ptr *create() {
	fun_ptr *Array;
	Array = malloc(sizeof(fun_ptr)*SIZE);
	return(Array);
}
void delete(fun_ptr * Array) {
	free((void *) Array);
	Array=NULL;
}
void init(fun_ptr *Array) {
	int i;
	for (i=0; i < SIZE; i++){
		Array[i] = error;
	}
}
void add(fun_ptr *Array, duap_s i, void *fun) {
	if(i < SIZE) {
		Array[i] = fun;
	} else {
		error_v();
	}
}
void call(fun_ptr *Array,duap_s i) {
	if(i < SIZE) {
		Array[i]();
	} else {
		error_v();
	}
}
void error() {
	printf("Something wrong!\n");
}
void error_v() {
	printf("Something very wrong!\n");
}
void example() {
	printf("Pointer?\n");
}
