#ifndef __zadanie2_H
#define __zadanie2_H

typedef void (*fun_ptr)(); // nowytyp fun_ptr jako wskaźnik do funkcji
typedef enum duap_t {
	HANDLE1 = 0,
	HANDLE2,
	HANDLE3,
	SIZE
} duap_s;

fun_ptr create(); // po co mnie to?
void init(fun_ptr *); // dodanie do tablicy error()
void add(fun_ptr *, int , void *); // dodanie funkcji
void call(fun_ptr *,int ); // wywołanie funkcji
void error(); // info o błędach
void example(); // przykładowa funkcja

#endif /* __zadanie2_H */
