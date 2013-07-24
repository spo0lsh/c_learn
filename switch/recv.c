#include <stdio.h>
#include <stdlib.h>
#include "switch.h"
#include "recv.h"
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
//#include <memory.h>


int fn_recv(int n_i,SFrame *s_Frame) {
	int n_msqid;
	key_t key;
	SMessage_buf S_Rbuf;

    key = MSQKEYRECV + n_i;
    #ifdef DEBUG
	printf("%d %d\n", key,n_i );
	#endif
    if ((n_msqid = msgget(key, 0666)) < 0) {
		#ifdef DEBUG
        perror("msgget");
        #endif
        exit(1);
    }

    /*
     * Receive an answer of message type 1.
     */
    if (msgrcv(n_msqid, &S_Rbuf, sizeof(S_Rbuf.s_Frame), 1, 0) < 0) {
		#ifdef DEBUG
        perror("msgrcv");
        #endif
        exit(1);
    }
	//s_Frame = S_Rbuf.s_Frame;
	memcpy((void *)s_Frame, (void *) &S_Rbuf.s_Frame, sizeof(SFrame));
	
	#ifdef DEBUG
    /*
     * Print the answer.
     */
    printf("[RECV] on bridgeport %d\n", n_i);
	printf("[RECV] MACdst: %02x:%02x:%02x:%02x:%02x:%02x\n", s_Frame->ach_MACdst[0], s_Frame->ach_MACdst[1], s_Frame->ach_MACdst[2], s_Frame->ach_MACdst[3], s_Frame->ach_MACdst[4], s_Frame->ach_MACdst[5]);
	printf("[RECV] MACsrc: %02x:%02x:%02x:%02x:%02x:%02x\n", s_Frame->ach_MACsrc[0], s_Frame->ach_MACsrc[1], s_Frame->ach_MACsrc[2], s_Frame->ach_MACsrc[3], s_Frame->ach_MACsrc[4], s_Frame->ach_MACsrc[5]);
	printf("[RECV] Length: %d\n", s_Frame->ach_Length);
	printf("[RECV] Payload: %s\n", s_Frame->ach_Payload);
	printf("[RECV] CRC: %s\n", s_Frame->ach_crc);
	#endif /* DEBUG */

	
	/*
	removing wrong crc
	*/
	char _ach_crc[4] = "42";
	if(strcmp(s_Frame->ach_crc , _ach_crc) == 0) {
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
