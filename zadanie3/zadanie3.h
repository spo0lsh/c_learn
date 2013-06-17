#ifndef __zadanie3_H
#define __zadanie3_H


void test_size(); // testowa

// kombinacje (enum)
typedef enum comb_e {
	COMB1, COMB2, COMB3
}comb_t;
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
	msg1_t um1;
	msg2_t um2;
	msg3_t um3;
} msg_t;

#endif /* __zadanie3_H */
