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
	call(Array,1);
	add(Array,1, &example);
	call(Array,1);
	return(EXIT_SUCCESS);
}

fun_ptr *create() {
	fun_ptr *Array;
	Array = malloc(sizeof(fun_ptr)*5);
	return(Array);
}
void init(fun_ptr *Array) {
	int i;
	for (i=0; i < 5; i++){
		Array[i] = error;
	}
}
void add(fun_ptr *Array, int i, void *fun) {
	Array[i] = fun;
}
void call(fun_ptr *Array,int i){
	Array[i]();
}
void error() {
	printf("Something wrong!\n");
}
void example() {
	printf("Pointer?\n");
}
