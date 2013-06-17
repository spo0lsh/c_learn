#ifndef __zadanie2_H
#define __zadanie2_H

typedef void (*fun_ptr)(); // nowytyp fun_ptr jako wskaźnik do funkcji
typedef enum duap_t {
	HANDLE1,
	HANDLE2,
	HANDLE3,
	SIZE,
	HANDLE4 // for test
} duap_s;

fun_ptr *create(); // po co mnie to?
void delete(fun_ptr *); // remove
void init(fun_ptr *); // dodanie do tablicy error()
void add(fun_ptr *, duap_s , void *); // dodanie funkcji
void call(fun_ptr *Array, duap_s ); // wywołanie funkcji
void error(); // info o błędach
void error_v(); // info o błędach bardzo poważnych
void example(); // przykładowa funkcja

#endif /* __zadanie2_H */
