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
#include "db.h"
#include "uni_br_multi.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "src_dst_iface.h"

sHashTable *asHASH;
int n_aging;

int main() {
	/* create database */
	asHASH=fn_create_hash();
	
	/* reading file */
	fn_readfile();
	
	/* generate bridgeports */
	fn_generate_interafaces();
	
	/* thread variables */
	pthread_t pthread_bridgeport[SWITCH];
	pthread_t pthread_aging;
	int an_vals[SWITCH];
	int n_i;

	/* create threads */  
	for(n_i=0;n_i<SWITCH;++n_i) {
		an_vals[n_i] = n_i + 1;
		if ( pthread_create( &pthread_bridgeport[n_i], NULL, (void *) &fn_pthread_bridgeport, (void *) &an_vals[n_i]) ) {
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
	char ch_menu;
	scanf("%s",&ch_menu);
	switch(ch_menu) {
		case 'q':
			fn_hash_show(asHASH);
			printf("Quit\n");
			/* remove interfaces */
			fn_remove_interafaces();
			fn_destroy_hash(asHASH);
		break;
	}
    return(EXIT_SUCCESS);
}

void fn_pthread_bridgeport(void * p_arg) {
	int *n_bridge;
	int n_flood; // flood or unicast
	int n_crc; // crc
	int n_hash;
	if(NULL != p_arg) {
		n_bridge = (int *) p_arg;
	}
	#ifdef DEBUG
	printf("fn_pthread_bridgeport number %d!\n", *n_bridge);
	#endif
	SFrame s_Frame;
	while(1) {
		/* recv frame */
		n_crc=fn_recv(*n_bridge,&s_Frame);
		if(n_crc) {
			/* learn or refresh */
			fn_learn_or_refresh(*n_bridge,&s_Frame);
			/* unicast broadcast multicast */
			n_hash = fn_hash(s_Frame.ach_MACsrc);
			if(asHASH[n_hash].n_Filter == 0) {
				n_flood=fn_unicast_broadcast_multicast(*n_bridge,&s_Frame);
				/* flood */
				if(n_flood) {
					#ifdef DEBUG
					printf("[FLOOD] flooding\n");
					#endif
					fn_flood(*n_bridge,&s_Frame);
				} else {
					n_hash=0;
					n_hash = fn_hash(s_Frame.ach_MACdst);
					#ifdef DEBUG
					printf("[flood] unicast to port %d hash %d\n",asHASH[n_hash].n_Port,n_hash+1);
					#endif
					/* source destination + filter */
					if(fn_src_dst_iface(*n_bridge, asHASH[n_hash].n_Port) && asHASH[n_hash].n_Port < SWITCH+1) {
						/* send frame */
						fn_send(asHASH[n_hash].n_Port,&s_Frame);
					}
				}
			} else {
				#ifdef DEBUG
				printf("[FILTER] removing frame\n");
				#endif
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

void fn_generate_interafaces() {
	int n_i;
	#ifdef DEBUG
	printf("Creating bridgeport pseudo interfaces\n");
	#endif
	key_t key; /* key to be passed to msgget() */ 
	int msqid; /* return value from msgget() */
	int msgflg = IPC_CREAT | 0666;
	for(n_i=0;n_i<SWITCH;++n_i) {
		key = MSQKEYRECV + n_i + 1; // recv
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
	for(n_i=0;n_i<SWITCH;++n_i) {
		key = MSQKEYSEND + n_i + 1; // send
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
void fn_remove_interafaces() {
	int n_i;
	key_t key; /* key to be passed to msgget() */ 
	int msgflg = IPC_CREAT | 0666;
	#ifdef DEBUG
	printf("Removing bridgeport pseudo interfaces\n");
	#endif
	for(n_i=0;n_i<SWITCH;++n_i) {
		key = MSQKEYRECV + n_i + 1; // recv
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
	for(n_i=0;n_i<SWITCH;++n_i) {
		key = MSQKEYSEND + n_i + 1; // recv
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

