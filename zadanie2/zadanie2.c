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
