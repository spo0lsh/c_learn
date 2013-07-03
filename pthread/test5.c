#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void idiota() {
	printf("Jestem idiotą!\n");
}

int duap() {
	int i=0;
	printf("DUAP!\n");
	return i;
}


void *MojaFunkcjaDlaWatku1(void *arg) {
	idiota();
	duap();
	return NULL;
}

void *MojaFunkcjaDlaWatku2(void *arg) {
	while(1) {
		idiota();
		sleep(1);
	}
	return NULL;
}


int main(void) {
	pthread_t thread1;
	pthread_t thread2;
	
	if ( pthread_create( &thread1, NULL, MojaFunkcjaDlaWatku1, NULL) ) {
		printf("blad przy tworzeniu watku\n"); abort();
	}
	if ( pthread_create( &thread2, NULL, MojaFunkcjaDlaWatku2, NULL) ) {
		printf("blad przy tworzeniu watku\n"); abort();
	}
	if ( pthread_join ( thread1, NULL ) ) {
		printf("blad przy tworzeniu watku\n");
		abort();
	}
	if ( pthread_join ( thread2, NULL ) ) {
		printf("blad przy tworzeniu watku\n");
		abort();
	}

	exit(0);
}
