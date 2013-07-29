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


/*
 * Author: Krzysztof Krych
 * email: krzysztof.krych@tieto.com
 * version: stable ;)
 * 
 * Frame structure
 * 00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 ... 45
      dstmac        |      srcmac     | length    |   payload
         6 byte     |      6 byte     | 4 byte(*) |   payload -> static -> up to 45
         * - in x86 GCC
*/

sHashTable *pas_HASH;
int n_aging;

int main() {
	/* create database */
	pas_HASH=fn_create_hash();
	
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
	char ch_menu;
	while(1) {
	printf("p [enter] - print without empty\n");
	printf("a [enter] - print all\n");
	printf("r [enter] - reload config file\n");
	printf("q [enter] - quit\n");
	scanf("%s",&ch_menu);
		switch(ch_menu) {
			case 'p':
				printf("MAC table: \n");
				fn_mac_show();
			break;
			case 'a':
				printf("MAC table: \n");
				fn_hash_show();
			break;
			case 'r':
				printf("Reload configfile\n");
				for(n_i=0;n_i<HASH_TABLE;n_i++) { // all DB
					fn_remove(n_i);
				}
				fn_readfile();
			break;
			case 'q':
				// show hash table (should be in indef?)
				fn_hash_show(pas_HASH);
				printf("Quit\n");
				/* remove interfaces */
				fn_remove_interafaces();
				// destroy hash
				fn_destroy_hash(pas_HASH);
				return(EXIT_SUCCESS);
			break;
		}
	}
    return(EXIT_SUCCESS);
}

// bridgeport thread
void fn_pthread_bridgeport(void * p_arg) {
	int *n_bridge;
	int n_forward; //
	int n_flood;  // flood or unicast
	int n_crc;   // crc
	int n_hash;
	if(NULL != p_arg) {
		n_bridge = (int *) p_arg;
	}
	#ifdef DEBUG
	printf("fn_pthread_bridgeport number %d!\n", *n_bridge);
	#endif
	SFrame s_Frame;
	//infinity loop - reading from MQ
	while(1) {
		/* recv frame */
		n_crc=fn_recv(*n_bridge,&s_Frame); // if CRC is ok -> true
		if(n_crc) {
			/* unicast broadcast multicast */
			n_hash = fn_hash(s_Frame.ach_MACsrc); // calc hash key
			// no forward broadcast/unicast or filter frame
			if(pas_HASH[n_hash].n_Port < SWITCH+1) {
				n_forward=1;
			} else {
				n_forward=1;
			}
			if((s_Frame.ach_MACsrc[0] % 2 ) == 0) {
				n_forward=1;
			} else {
				n_forward=0;
			}
			if(n_forward) {
				/* learn or refresh */
				fn_learn_or_refresh(*n_bridge,&s_Frame); //adding entry to DB

				n_flood=fn_unicast_broadcast_multicast(*n_bridge,&s_Frame); // TRUE if flooding, FALSE if unicast
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
					printf("[flood] unicast to port %d hash %d\n",pas_HASH[n_hash].n_Port,n_hash+1);
					#endif
					/* source destination + filter */
					if(fn_src_dst_iface(*n_bridge, pas_HASH[n_hash].n_Port) && pas_HASH[n_hash].n_Port < SWITCH+1) { // TRUE if not on the same iface and not filtering
						/* send frame */
						fn_send(pas_HASH[n_hash].n_Port,&s_Frame);
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
			printf("Removing wrong CRC frame or removing multicast broadcast frame\n");
		}
		#endif
	}
	pthread_exit(0); /* exit */
}

/* aging procedure */
void fn_pthread_aging(void *arg) {
	#ifdef DEBUG
	printf("fn_pthread_aging\n");
	#endif
	//infinity loop
	while(1) {
		#ifdef DEBUG
		printf("Starting aging procedure ...\n");
		#endif
		fn_aging();
		sleep(AGING);
	}
	pthread_exit(0); /* exit */
}
/* generate MQ as pseudo interface */
void fn_generate_interafaces() {
	int n_i;
	#ifdef DEBUG
	printf("Creating bridgeport pseudo interfaces\n");
	#endif
	key_t key; /* key to be passed to msgget() */ 
	int msqid; /* return value from msgget() */
	int msgflg = IPC_CREAT | 0666; // set correct access
	//create input
	for(n_i=0;n_i<SWITCH;++n_i) {
		key = MSQKEYRECV + n_i + 1; // recv
		if ((msqid = msgget(key, msgflg )) < 0) { //
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
	//create output
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

/* remove pseudo interfaces */
void fn_remove_interafaces() {
	int n_i;
	key_t key; /* key to be passed to msgget() */ 
	int msgflg = IPC_CREAT | 0666; // need this for IPC_RMID
	#ifdef DEBUG
	printf("Removing bridgeport pseudo interfaces\n");
	#endif
	// remove input
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
	// remove outpu
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

