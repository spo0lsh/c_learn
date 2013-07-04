#include <stdio.h>
#include <stdlib.h>
#include "switch.h"
#include "recv.h"
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
//#include <memory.h>


void fn_recv(int i,SFrame *frame) {
	int msqid;
	key_t key;
	message_buf  rbuf;

    key = 1000 + i;
    #ifdef DEBUG
	printf("%d %d\n", key,i );
	#endif
    if ((msqid = msgget(key, 0666)) < 0) {
		#ifdef DEBUG
        perror("msgget");
        #endif
        exit(1);
    }

    /*
     * Receive an answer of message type 1.
     */
    if (msgrcv(msqid, &rbuf, sizeof(rbuf.frame), 1, 0) < 0) {
		#ifdef DEBUG
        perror("msgrcv");
        #endif
        exit(1);
    }
	//frame = rbuf.frame;
	memcpy((void *)frame, (void *) &rbuf.frame, sizeof(SFrame));
	
	#ifdef DEBUG
    /*
     * Print the answer.
     */
    printf("RECV on bridgeport %d\n",i);
	printf("[R] MACdst: %02x:%02x:%02x:%02x:%02x:%02x\n", frame->ach_MACdst[0], frame->ach_MACdst[1], frame->ach_MACdst[2], frame->ach_MACdst[3], frame->ach_MACdst[4], frame->ach_MACdst[5]);
	printf("[R] MACsrc: %02x:%02x:%02x:%02x:%02x:%02x\n", frame->ach_MACsrc[0], frame->ach_MACsrc[1], frame->ach_MACsrc[2], frame->ach_MACsrc[3], frame->ach_MACsrc[4], frame->ach_MACsrc[5]);
	printf("[R] Length: %d\n", frame->ach_Length);
	printf("[R] Payload: %s\n", frame->ach_Payload);
	printf("[R] CRC: %s\n", frame->ach_crc);
	#endif /* DEBUG */

	
	/*
	removing wrong crc
	*/
	#ifdef DEBUG
	printf("CRC\n");
	#endif
	//char _ach_crc[4] = "42";
//	if(strcmp(frame->ach_crc , _ach_crc) == 0) {
//		#ifdef DEBUG
//		printf("PASS\n");
//		#endif /* DEBUG */
//	} else {
//		#ifdef DEBUG
//		printf("DROP\n");
//		#endif /* DEBUG */
//	}
}
