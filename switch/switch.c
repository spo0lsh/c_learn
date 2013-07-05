#include <stdio.h>
#include <stdlib.h>
#include "switch.h"
#include "recv.h"
#include "flood.h"
#include "aging.h"
#include "send.h"
#include "aging.h"
#include <pthread.h>
#include <unistd.h>
#include <memory.h>
#include "learn.h"
#include "uni_br_multi.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
	/* generate bridgeports */
	generate_interafaces();

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
			/* remove interfaces */
			remove_interafaces();
		break;
	}
    return(EXIT_SUCCESS);
}

void fn_pthread_bridgeport(void *arg) {
	int *n_bridge;
	int flood; // flood or unicast
	int crc; // crc
	if(NULL != arg) {
		n_bridge = (int *) arg;
	}
	#ifdef DEBUG
	printf("fn_pthread_bridgeport number %d!\n", *n_bridge);
	#endif
	SFrame frame;
	while(1) {
		/* recv frame */
		crc=fn_recv(*n_bridge,&frame);
		if(crc) {
			/* learn or refresh */
			fn_learn_or_refresh(*n_bridge,&frame);
			/* unicast broadcast multicast */
			flood=fn_unicast_broadcast_multicast(*n_bridge,&frame);
			/* flood */
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
		#ifdef DEBUG
		else {
			printf("Removing wrong CRC frame\n");
		}
		#endif
	}
	pthread_exit(0); /* exit */
}


void fn_pthread_aging(void *arg) {
	#ifdef DEBUG
	printf("fn_pthread_aging\n");
	#endif
	while(1) {
		#ifdef DEBUG
		printf("Starting aging procedure ...\n");
		#endif
		fn_aging();
		sleep(AGING);
	}
	pthread_exit(0); /* exit */
}

void generate_interafaces() {
	int i;
	#ifdef DEBUG
	printf("Creating bridgeport pseudo interfaces\n");
	#endif
	key_t key; /* key to be passed to msgget() */ 
	int msqid; /* return value from msgget() */
	int msgflg = IPC_CREAT | 0666;
	for(i=0;i<SWITCH;++i) {
		key = MSQKEYRECV + i + 1; // recv
		if ((msqid = msgget(key, msgflg )) < 0) {
			#ifdef DEBUG
			perror("msgget");
			#endif
			exit(1);
		} 
		#ifdef DEBUG
		else {
				printf("Creating msqid %d key %d\n",msqid,key);
		}
		#endif
	}
	for(i=0;i<SWITCH;++i) {
		key = MSQKEYSEND + i + 1; // send
		if ((msqid = msgget(key, msgflg )) < 0) {
			#ifdef DEBUG
			perror("msgget");
			#endif
			exit(1);
		} 
		#ifdef DEBUG
		else {
				printf("Creating msqid %d key %d\n",msqid,key);
		}
		#endif
	}

}
void remove_interafaces() {
	int i;
	key_t key; /* key to be passed to msgget() */ 
	int msgflg = IPC_CREAT | 0666;
	#ifdef DEBUG
	printf("Removing bridgeport pseudo interfaces\n");
	#endif
	for(i=0;i<SWITCH;++i) {
		key = MSQKEYRECV + i + 1; // recv
		#ifdef DEBUG
		printf("Removing msqid %d key %d\n", msgget(key, msgflg ),key);
		#endif
		if (msgctl(msgget(key, msgflg ), IPC_RMID, NULL) == -1) {
			#ifdef DEBUG
			perror("msgctl");
			#endif
	//        exit(1);
		}
	}
	for(i=0;i<SWITCH;++i) {
		key = MSQKEYSEND + i + 1; // recv
		#ifdef DEBUG
		printf("Removing msqid %d key %d\n", msgget(key, msgflg ),key);
		#endif
		if (msgctl(msgget(key, msgflg ), IPC_RMID, NULL) == -1) {
			#ifdef DEBUG
			perror("msgctl");
			#endif
	//        exit(1);
		}
	}
}

