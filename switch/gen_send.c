#include <stdio.h>
#include <stdlib.h>
#include "gen_send.h"
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <memory.h>
//#define DEBUG

int main() {
	
	//tworzenie
	SFrame frame;
	frame.ach_MACdst[0] = 0x00;
	frame.ach_MACdst[1] = 0x0d;
    frame.ach_MACdst[2] = 0x3f;
    frame.ach_MACdst[3] = 0xff;
    frame.ach_MACdst[4] = 0x02;
    frame.ach_MACdst[5] = 0x5f;
	
	frame.ach_MACsrc[0] = 0x00;
	frame.ach_MACsrc[1] = 0x0d;
	frame.ach_MACsrc[2] = 0x3f;
	frame.ach_MACsrc[3] = 0xff;
	frame.ach_MACsrc[4] = 0xff;
	frame.ach_MACsrc[5] = 0xff;

	frame.ach_Length = 64;
	(void) strcpy(frame.ach_Payload,"DUAP");
	(void) strcpy(frame.ach_crc,"42");
	
	// 
	int msqid;
	int msgflg = IPC_CREAT | 0666;
	key_t key;
	message_buf sbuf;
	key = 1001;
	//key = ftok("/tmp/bridge0", 'b');
	
	//(void) fprintf(stderr, "\nmsgget: Calling msgget(%#lx,\%#o)\n",key, msgflg);
    if ((msqid = msgget(key, msgflg )) < 0) {
        perror("msgget");
        exit(1);
    }
    else 
		(void) fprintf(stderr,"msgget: msgget succeeded: msqid = %d\n", msqid);
	
	sbuf.mtype = 1;
	(void) fprintf(stderr,"msgget: msgget succeeded: msqid = %d\n", msqid);
	sbuf.frame = frame;
	printf("Frame Length: %d\n", sbuf.frame.ach_Length);
	(void) fprintf(stderr,"msgget: msgget succeeded: msqid = %d\n", msqid);
	
	if (msgsnd(msqid, &sbuf, sizeof(sbuf.frame), IPC_NOWAIT) < 0) {
		//printf("%d %"l %l \n", msqid, sbuf.mtype, sizeof(sbuf.frame) );
		perror("msgsnd");
		exit(1);
	} else 
		printf("Message: Sent\n");
	
    return(EXIT_SUCCESS);
}
