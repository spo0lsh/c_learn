#include <stdio.h>
#include <stdlib.h>
#include "zadanie3.h"

/*
Stwórz:
Funkcję, która w bufor otrzymany w parametrze wpisuje 3 typy wiadomości
 (typedef struct..., rozmiary każdego typu powinny być różne i spakowane
 (packed)) w kolejności podanej w parametrze (typ wyliczeniowy). 
Kolejność powinna również zostać zapisana w buforze (najlepiej na
 początku buforu, w typie wiadomości stworzonej do tego celu). Wszystkie
 typy to typedef.
Funkcję, która odczytuje wszystkie wiadomości z buforu w kolejności
 zgodnej z zapisaną na jego początku. Następnym krokiem jest wypisanie
  wartości każdego z pól wiadomości. W funkcji powinna zostać
 wykorzystana unia nienazwana.

*/

int main() {
	// definicja buffora
	char * buff = malloc(sizeof(msg1_t) +  sizeof(msg2_t) + sizeof(msg3_t));
	if(buff == NULL) {
		printf("Something wrong!\n");
		free(buff);
		buff=NULL;
		exit(EXIT_FAILURE);
	}
	
	// debug
	//test_size();
	
	// zwalnianie buffora
	free(buff);
	buff=NULL;
	return(EXIT_SUCCESS);
}


void test_size() {
	printf("int %d\n", sizeof(int));
	printf("short int %d\n", sizeof(short int));
	printf("char %d\n", sizeof(char));
	printf("long int %d\n", sizeof(long int));
	printf("float %d\n", sizeof(float));
	printf("double %d\n", sizeof(double));
	printf("msg1_t %d\n", sizeof(msg1_t));
	printf("msg2_t %d\n", sizeof(msg2_t));
	printf("msg3_t %d\n", sizeof(msg3_t));
}
