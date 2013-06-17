#include <stdio.h>
#include <stdlib.h>
#include <memory.h> // http://pl.wikibooks.org/wiki/C/memcpy
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
	char *buff;
	buff=buff_create();
	// jedziemy z koksem
	buff_add(COMB1, buff);
	buff_print(buff);
	buff_add(COMB2, buff);
	buff_print(buff);
	buff_add(COMB1, buff);
	buff_print(buff);
	buff_add(COMB3, buff);
	buff_print(buff);
	buff_add(COMB4, buff);
	buff_print(buff);
	// printowanie
	
	// zwalnianie buffora
	buff_free(buff);
	return(EXIT_SUCCESS);
}

void buff_add(comb_t comb, char * buff) {
	order_t tmp_seq;
	msg1_t m1;
	msg2_t m2;
	msg3_t m3;
	// ustawianie wiadomosci
	m1.m1 = 11;
	m1.m2 = 12;
	m1.m3 = 13;
	m2.m1 = 21;
	m2.m2 = 22;
	m2.m3 = 23;
	m3.m1 = 31;
	m3.m2 = 32;
	m3.m3 = 33;
	switch (comb) {
		case COMB1:
			tmp_seq.one = sizeof(msg1_t);
			tmp_seq.two = sizeof(msg2_t);
			tmp_seq.three = sizeof(msg3_t);
			tmp_seq.comb = comb;
			memcpy(buff, &tmp_seq, sizeof(order_t));
			memcpy(buff + sizeof(tmp_seq), &m1, sizeof(msg1_t));
			memcpy(buff + (sizeof(tmp_seq) + sizeof(msg1_t)), &m2, sizeof(msg2_t));
			memcpy(buff + (sizeof(tmp_seq) + sizeof(msg1_t) + sizeof(msg2_t)), &m3, sizeof(msg3_t));
			break;
		case COMB2:
			tmp_seq.one = sizeof(msg2_t);
			tmp_seq.two = sizeof(msg3_t);
			tmp_seq.three = sizeof(msg1_t);
			tmp_seq.comb = comb;
			memcpy(buff, &tmp_seq, sizeof(order_t));
			memcpy(buff + sizeof(tmp_seq), &m2, sizeof(msg2_t));
			memcpy(buff + (sizeof(tmp_seq) + sizeof(msg2_t)), &m3, sizeof(msg3_t));
			memcpy(buff + (sizeof(tmp_seq) + sizeof(msg2_t) + sizeof(msg3_t)), &m1, sizeof(msg1_t));
		break;
		case COMB3:
			tmp_seq.one = sizeof(msg3_t);
			tmp_seq.two = sizeof(msg1_t);
			tmp_seq.three = sizeof(msg2_t);
			tmp_seq.comb = comb;
			memcpy(buff, &tmp_seq, sizeof(order_t));
			memcpy(buff + sizeof(tmp_seq), &m3, sizeof(msg3_t));
			memcpy(buff + (sizeof(tmp_seq) + sizeof(msg3_t)), &m1, sizeof(msg1_t));
			memcpy(buff + (sizeof(tmp_seq) + sizeof(msg3_t) + sizeof(msg1_t)), &m2, sizeof(msg2_t));
		break;
		default:
			printf("Combination N/A\n");
		break;
	}
}

void buff_print(char * buff) {
	order_t seq;
	msg_t msg;

	switch (seq.comb) {
		case COMB1:
			printf("COMB1: ");
			memcpy(&msg.um1, buff + sizeof(seq), sizeof(msg1_t));
			printf("%d, %d, %d ", msg.um1.m1, msg.um1.m2, msg.um1.m3);
			memcpy(&msg.um2, buff + (sizeof(seq) + sizeof(msg1_t)), sizeof(msg2_t));
			printf("%.2f, %.2f, %.2f ", msg.um2.m1, msg.um2.m2, msg.um2.m3);
			memcpy(&msg.um3,buff + (sizeof(seq) + sizeof(msg1_t) + sizeof(msg2_t)), sizeof(msg3_t));
			printf("%.2f, %.2f, %.2f ", msg.um3.m1, msg.um3.m2, msg.um3.m3);
			printf("\n");
		break;
		case COMB2:
			printf("COMB2: ");
			memcpy(&msg.um1, buff + sizeof(seq), sizeof(msg2_t));
			printf("%.2f, %.2f, %.2f ", msg.um2.m1, msg.um2.m2, msg.um2.m3);
			memcpy(&msg.um2, buff + (sizeof(seq) + sizeof(msg2_t)), sizeof(msg3_t));
			printf("%.2f, %.2f, %.2f ", msg.um3.m1, msg.um3.m2, msg.um3.m3);
			memcpy(&msg.um3,buff + (sizeof(seq) + sizeof(msg2_t) + sizeof(msg3_t)), sizeof(msg1_t));
			printf("%d, %d, %d ", msg.um1.m1, msg.um1.m2, msg.um1.m3);
			printf("\n");
		break;
		case COMB3:
			printf("COMB3: ");
			memcpy(&msg.um3, buff + sizeof(seq), sizeof(msg3_t));
			printf("%.2f, %.2f, %.2f ", msg.um3.m1, msg.um3.m2, msg.um3.m3);
			memcpy(&msg.um1, buff + (sizeof(seq) + sizeof(msg3_t)), sizeof(msg1_t));
			printf("%d, %d, %d ", msg.um1.m1, msg.um1.m2, msg.um1.m3);
			memcpy(&msg.um2,buff + (sizeof(seq) + sizeof(msg3_t) + sizeof(msg1_t)), sizeof(msg2_t));
			printf("%.2f, %.2f, %.2f ", msg.um2.m1, msg.um2.m2, msg.um2.m3);
			printf("\n");
		break;
		default:
			printf("Combination N/A");
		break;
	}
}

char *buff_create() {
	char * buff = malloc(sizeof(order_t) + sizeof(msg1_t) +  sizeof(msg2_t) + sizeof(msg3_t));
	if(buff == NULL) {
		printf("Something wrong!\n");
		free(buff);
		buff=NULL;
		exit(EXIT_FAILURE);
	}
	return(buff);
}
void buff_free(char (*buff)) {
	free(buff);
	buff=NULL;
}
