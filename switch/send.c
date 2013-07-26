#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "switch.h"
#include "send.h"
#include "recv.h"

/* write structure to MQ */
void fn_send(int n_i, SFrame *ps_Frame) {
	// 
	int n_msqid;
	int n_msgflg = IPC_CREAT | 0666;
	key_t key;
	SMessage_buf S_Sbuf; // struct for MQ
	key = MSQKEYSEND + n_i; // send key -> bridgeport in MQ
    if ((n_msqid = msgget(key, n_msgflg )) < 0) { // if fail write to MQ -> exit; BUG?
		#ifdef DEBUG
        perror("msgget");
        #endif
        exit(1);
    }
    #ifdef DEBUG
    else 
    {
		(void) fprintf(stderr,"msgget: msgget succeeded: msqid = %d\n", n_msqid);
	}
	#endif
	S_Sbuf.d_Mtype = 1; // set Mtype
	#ifdef DEBUG
	(void) fprintf(stderr,"msgget: msgget succeeded: msqid = %d\n", n_msqid);
	#endif
	memcpy(&(S_Sbuf.s_Frame), ps_Frame, sizeof(SFrame)); //rewrite Frame to MQ struct.
	if (msgsnd(n_msqid, &S_Sbuf, sizeof(S_Sbuf.s_Frame), IPC_NOWAIT) < 0) { // if fail write to MQ -> exit; BUG?
		#ifdef DEBUG
		perror("msgsnd");
		#endif
		exit(1);
	} 
	else {
		#ifdef DEBUG			
		printf("Message: Sent on bridgeport %d\n",n_i);
		printf("[SEND] MACdst: %02x:%02x:%02x:%02x:%02x:%02x\n", ps_Frame->ach_MACdst[0], ps_Frame->ach_MACdst[1], ps_Frame->ach_MACdst[2], ps_Frame->ach_MACdst[3], ps_Frame->ach_MACdst[4], ps_Frame->ach_MACdst[5]);
		printf("[SEND] MACsrc: %02x:%02x:%02x:%02x:%02x:%02x\n", ps_Frame->ach_MACsrc[0], ps_Frame->ach_MACsrc[1], ps_Frame->ach_MACsrc[2], ps_Frame->ach_MACsrc[3], ps_Frame->ach_MACsrc[4], ps_Frame->ach_MACsrc[5]);
		printf("[SEND] Length: %d\n", ps_Frame->ach_Length);
		printf("[SEND] Payload: %s\n", ps_Frame->ach_Payload);
		printf("[SEND] CRC: %02x%02x%02x%02x\n",ps_Frame->ach_crc[0],ps_Frame->ach_crc[1],ps_Frame->ach_crc[2],ps_Frame->ach_crc[3]);
		#endif
		//void();
	}
}
