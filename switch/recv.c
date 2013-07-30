#include <stdio.h>
#include <stdlib.h>
#include "switch.h"
#include "recv.h"
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "crc.h"

/* recive frame from MQ */
int fn_recv(int n_i,SFrame *ps_Frame) {
	int n_msqid;
	key_t key;
	SMessage_buf S_Rbuf;
	if(n_i == 0) { // hack
		n_i=n_i + 1;
	}
    key = MSQKEYRECV + n_i;
    #ifdef DEBUG
	printf("%d %d\n", key,n_i );
	#endif
    if ((n_msqid = msgget(key, 0666)) < 0) { // exit if fail read
		#ifdef DEBUG
		printf("key = %d\n",key);
        perror("msgget");
        #endif
        exit(1);
    }

    /*
     * Receive an answer of message type 1.
     */
    if (msgrcv(n_msqid, &S_Rbuf, sizeof(S_Rbuf.s_Frame), 1, 0) < 0) { // exit if fail read
		#ifdef DEBUG
        perror("msgrcv");
        #endif
        exit(1);
    }
	//s_Frame = S_Rbuf.s_Frame;
	memcpy((void *)ps_Frame, (void *) &S_Rbuf.s_Frame, sizeof(SFrame)); // copy frame from MQ struct
	
	#ifdef DEBUG
    /*
     * Print the answer.
     */
    printf("[RECV] on bridgeport %d\n", n_i);
	printf("[RECV] MACdst: %02x:%02x:%02x:%02x:%02x:%02x\n", ps_Frame->ach_MACdst[0], ps_Frame->ach_MACdst[1], ps_Frame->ach_MACdst[2], ps_Frame->ach_MACdst[3], ps_Frame->ach_MACdst[4], ps_Frame->ach_MACdst[5]);
	printf("[RECV] MACsrc: %02x:%02x:%02x:%02x:%02x:%02x\n", ps_Frame->ach_MACsrc[0], ps_Frame->ach_MACsrc[1], ps_Frame->ach_MACsrc[2], ps_Frame->ach_MACsrc[3], ps_Frame->ach_MACsrc[4], ps_Frame->ach_MACsrc[5]);
	printf("[RECV] Length: %d\n", ps_Frame->ach_Length);
	printf("[RECV] Payload: %s\n", ps_Frame->ach_Payload);
	printf("[RECV] CRC: %02x%02x%02x%02x\n",ps_Frame->ach_crc[0],ps_Frame->ach_crc[1],ps_Frame->ach_crc[2],ps_Frame->ach_crc[3]);
	#endif /* DEBUG */

	
	/*
	removing wrong crc
	*/
	if(fn_crc_frame(ps_Frame)) { // if TRUE CRC is ok
		#ifdef DEBUG
		printf("[CRC] PASS\n");
		#endif /* DEBUG */
		return(1);
	} else {
		#ifdef DEBUG
		printf("[CRC] DROP\n");
		#endif /* DEBUG */
		return(0);
	}
}
