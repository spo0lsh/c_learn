#include <stdio.h>
#include <stdlib.h>
#include "switch.h"
#include "recv.h"
#include "flood.h"
#include "send.h"
#include "aging.h"
#include <pthread.h>
#include <unistd.h>
#include <memory.h>



//void *fn_pthread_recv(void *arg);



int main() {
	/* thread variables */
	pthread_t pthread_bridgeport[SWITCH];
	pthread_t pthread_aging;
	int vals[SWITCH];
	int i;

	/* create threads */  
	for(i=0;i<SWITCH;++i) {
		vals[i] = i + 1;
		if ( pthread_create( &pthread_bridgeport[i], NULL, (void *) &fn_pthread_bridgeport, (void *) &vals[i]) ) {
			#ifdef DEBUG
			printf("blad przy tworzeniu watku\n"); 
			#endif
			abort();
		}
	}
	if ( pthread_create( &pthread_aging, NULL, (void *) &fn_pthread_aging, NULL) ) {
		#ifdef DEBUG
		printf("blad przy tworzeniu watku\n"); 
		#endif
		abort();
	}
	/* Waiting for finish by user */
	printf("q [enter] - quit\n");
	char menu;
	scanf("%s",&menu);
	switch(menu) {
		case 'q':
			printf("Quit\n");
		break;
	}
    return(EXIT_SUCCESS);
}

void fn_pthread_bridgeport(void *arg) {
	int *n_bridge;
		if(NULL != arg) {
			n_bridge = (int *) arg;
		}
		#ifdef DEBUG
		printf("fn_pthread_bridgeport number %d!\n", *n_bridge);
		#endif
		while(1) {
		/* recv frame */
		SFrame frame;
		fn_recv(*n_bridge,&frame);
		/* learn or refresh */
		
		/* unicast broadcast multicast */
		
		/* flood */
		int flood=1;
		if(flood) {
			#ifdef DEBUG
			printf("flooding\n");
			#endif
			fn_flood(*n_bridge,&frame);
		} else {
			#ifdef DEBUG
			printf("unicast\n");
			#endif
			/* send frame */
			fn_send(*n_bridge+1,&frame); // n_bridge+1 wrong!
		}
	}
	pthread_exit(0); /* exit */
}


void fn_pthread_aging(void *arg) {
	#ifdef DEBUG
	printf("fn_aging\n");
	#endif
	while(1) {
		#ifdef DEBUG
		printf("Aging procedure ...\n");
		#endif
		sleep(AGING);
	}
	pthread_exit(0); /* exit */
}

