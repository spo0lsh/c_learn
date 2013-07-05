#include <stdio.h>
#include <stdlib.h>
#include "switch.h"
#include "recv.h"
#include "send.h"
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>



void fn_send(int i, SFrame *frame) {
	// 
	int msqid;
	int msgflg = IPC_CREAT | 0666;
	key_t key;
	message_buf sbuf;
	key = MSQKEYSEND + i;
	//(void) fprintf(stderr, "\nmsgget: Calling msgget(%#lx,\%#o)\n",key, msgflg);
    if ((msqid = msgget(key, msgflg )) < 0) {
		#ifdef DEBUG
        perror("msgget");
        #endif
        exit(1);
    }
    #ifdef DEBUG
    else 
    {
		(void) fprintf(stderr,"msgget: msgget succeeded: msqid = %d\n", msqid);
	}
	#endif
	sbuf.mtype = 1;
	#ifdef DEBUG
	(void) fprintf(stderr,"msgget: msgget succeeded: msqid = %d\n", msqid);
	#endif
	memcpy(&(sbuf.frame), frame, sizeof(SFrame));
	if (msgsnd(msqid, &sbuf, sizeof(sbuf.frame), IPC_NOWAIT) < 0) {
		#ifdef DEBUG
		//printf("%d %"l %l \n", msqid, sbuf.mtype, sizeof(sbuf.frame1) );
		perror("msgsnd");
		#endif
		exit(1);
	} 
	else {
		#ifdef DEBUG			
		printf("Message: Sent on bridgeport %d\n",i);
		printf("[S] MACdst: %02x:%02x:%02x:%02x:%02x:%02x\n", frame->ach_MACdst[0], frame->ach_MACdst[1], frame->ach_MACdst[2], frame->ach_MACdst[3], frame->ach_MACdst[4], frame->ach_MACdst[5]);
		printf("[S] MACsrc: %02x:%02x:%02x:%02x:%02x:%02x\n", frame->ach_MACsrc[0], frame->ach_MACsrc[1], frame->ach_MACsrc[2], frame->ach_MACsrc[3], frame->ach_MACsrc[4], frame->ach_MACsrc[5]);
		printf("[S] Length: %d\n", frame->ach_Length);
		printf("[S] Payload: %s\n", frame->ach_Payload);
		printf("[S] CRC: %s\n", frame->ach_crc);
		#endif
		//void();
	}
}
