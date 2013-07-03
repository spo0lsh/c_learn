#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include <signal.h>

void hello(char* tekst) {
	printf("[hello s] %s\n", tekst);
	char tekst1[60] = "dupa";
	printf("[hello e] %s\n", tekst1);
	strcpy(tekst,tekst1);
}

void *MojaFunkcjaDlaWatku(void *arg) {
        int i;
        for ( i=0; i<5; i++ ) {
                printf("[mojwatek] Watek mowi czesc!\n");
                sleep(1);
        }
        return NULL;
}

void *fn_w1(void *arg) {
	printf("[w1]\n");
	char tekst1[60]="w1w1w1";
	hello(strcpy(tekst1,"WuWuWu"));
	return NULL;
}





int main(void) {
	char tekst[60]="lalala";
	hello(tekst);
	printf("%s\n",tekst);
	strcpy(tekst,"dupa2");
	hello(tekst);
	hello(strcpy(tekst,"dupa3"));
	
	pthread_t mojwatek;
	pthread_t w1;
	
	if ( pthread_create( &mojwatek, NULL, MojaFunkcjaDlaWatku, NULL) ) {
		printf("blad przy tworzeniu watku\n"); abort();
	}

	if ( pthread_create( &w1, NULL, fn_w1, NULL) ) {
		printf("blad przy tworzeniu watku\n"); abort();
	}

	printf("q [enter] - wyłączenie\n");
	char menu;
	scanf("%s",&menu);
	switch(menu) {
		case 'q':
			printf("Quit\n");
			hello(tekst);
		break;
	}
	
	exit(0);

}
