#ifndef __zadanie3_H
#define __zadanie3_H

// kombinacje (enum)
typedef enum comb_e {
	COMB1, COMB2, COMB3
}comb_t;
// kolejność
typedef struct order_s {
	comb_t comb;
	int one; // sizeof(msg?_t)
	int two; // sizeof(msg?_t)
	int three; // sizeof(msg?_t)
}__attribute__((packed)) order_t;

// definicja wiadomosci
typedef struct msg1_s {
	short int m1;
	short int m2;
	short int m3;
} __attribute__((packed)) msg1_t;
typedef struct msg2_s {
	float m1;
	float m2;
	float m3;
} __attribute__((packed)) msg2_t;
typedef struct msg3_s {
	double m1;
	double m2;
	double m3;
} __attribute__((packed)) msg3_t;

typedef union {
	msg1_t um1; // struct msg1_t
	msg2_t um2; // struct msg2_t
	msg3_t um3; // struct msg3_t
} msg_t;

void buff_add(comb_t, char *); // wrzucanie do buffor
void buff_print(char *); // czytanie z buffora


#endif /* __zadanie3_H */
