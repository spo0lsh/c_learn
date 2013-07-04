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
	//pthread_t pthread_recv[SWITCH];
	//pthread_t pthread_send[SWITCH];
	pthread_t pthread_bridgeport[SWITCH];
	pthread_t pthread_aging;
	int vals[SWITCH];
	int i;
	/* structs to be passed to threads */
	//SFrame pth_rcv;
	//SFrame pth_snd;
	
	/* create threads */  
	for(i=0;i<SWITCH;++i) {
		vals[i] = i + 1;
		/*if ( pthread_create( &pthread_recv[i], NULL, (void *) &fn_pthread_recv, (void *) &vals[i]) ) {
			#ifdef DEBUG
			printf("blad przy tworzeniu watku\n"); abort();
			#endif
		}
		if ( pthread_create( &pthread_send[i], NULL, (void *) &fn_pthread_send, (void *) &vals[i]) ) {
			#ifdef DEBUG
			printf("blad przy tworzeniu watku\n"); abort();
			#endif
		}*/
		if ( pthread_create( &pthread_bridgeport[i], NULL, (void *) &fn_pthread_bridgeport, (void *) &vals[i]) ) {
			#ifdef DEBUG
			printf("blad przy tworzeniu watku\n"); abort();
			#endif
		}
	}
	if ( pthread_create( &pthread_aging, NULL, (void *) &fn_pthread_aging, NULL) ) {
		#ifdef DEBUG
		printf("blad przy tworzeniu watku\n"); abort();
		#endif
	}
	//int bridge;
	//SFrame frame;
	/*
	receive frame
	*/
	/*
	bridge=1;
	fn_recv(bridge,&frame);
	printf("[D] MACdst: %02x:%02x:%02x:%02x:%02x:%02x\n", frame.ach_MACdst[0], frame.ach_MACdst[1], frame.ach_MACdst[2], frame.ach_MACdst[3], frame.ach_MACdst[4], frame.ach_MACdst[5]);
	printf("[D] MACsrc: %02x:%02x:%02x:%02x:%02x:%02x\n", frame.ach_MACsrc[0], frame.ach_MACsrc[1], frame.ach_MACsrc[2], frame.ach_MACsrc[3], frame.ach_MACsrc[4], frame.ach_MACsrc[5]);
	printf("[D] Length: %d\n", frame.ach_Length);
	printf("[D] Payload: %s\n", frame.ach_Payload);
	printf("[D] CRC: %s\n", frame.ach_crc);
	*/
	/*
	learn or refresh
	*/

	/*
	unicast broadcast multicast
	*/	
	/*
	flood
	*/
	/*bridge=1;
	fn_send(bridge,&frame);
	*/

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

//void *fn_pthread_recv(void *arg) {
//	printf("DUPA\n");
//	pthread_exit(0); /* exit */
//}

void fn_pthread_bridgeport(void *arg) {
	int *n_bridge;
	if(NULL != arg) {
	    n_bridge = (int *) arg;
	}
	#ifdef DEBUG
	printf("fn_pthread_bridgeport number %d!\n", *n_bridge);
	#endif
	pthread_exit(0); /* exit */
}

void fn_pthread_recv(void *arg) {
	int *n_bridge;
	if(NULL != arg) {
	    n_bridge = (int *) arg;
	}
	//SFrame frame;
	//fn_recv(*n_bridge,&frame);
	//memcpy((void *) &n_bridge, (void *) arg, sizeof(int));
	//n_bridge = (n_bridge *) arg;
	//n_bridge = (n_bridge *) &arg; /* type cast to a pointer to n_bridge */
	//memcpy(&n_bridge, arg,sizeof(int));
	//SFrame *pth_rcv;
	//pth_rcv = (SFrame *) arg;  /* type cast to a pointer to thdata */
	//int _bridge_rcv;
	//_bridge_rcv=1;
	//fn_recv(_bridge_rcv,&pth_rcv);
	#ifdef DEBUG
	printf("fn_pthread_recv number %d!\n", *n_bridge);
	#endif
	//fn_send(n_bridge,&frame);
	pthread_exit(0); /* exit */
}

void fn_pthread_send(void *arg) {
	int *n_bridge;
	if(NULL != arg) {
	    n_bridge = (int *) arg;
	}
	//memcpy((void *) &n_bridge, (void *) arg, sizeof(int));
	//n_bridge = (n_bridge *) arg;
	//n_bridge = (n_bridge *) &arg; /* type cast to a pointer to n_bridge */
	//memcpy(&n_bridge, arg,sizeof(int));
	//SFrame *pth_rcv;
	//pth_rcv = (SFrame *) arg;  /* type cast to a pointer to thdata */
	//int _bridge_rcv;
	//_bridge_rcv=1;
	//fn_recv(_bridge_rcv,&pth_rcv);
	#ifdef DEBUG
	printf("fn_pthread_send number %d!\n", *n_bridge);
	#endif
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


//void *pthread_send(void *arg) {
//	SFrame *pth_snd;
//	pth_snd = (SFrame *) arg;  /* type cast to a pointer to thdata */
//	int _bridge_snd;
//	_bridge_snd=1;
//	fn_send(_bridge_snd,&pth_snd);
//	return NULL;
//}
