#include <stdio.h>
#include <stdlib.h>
#include "switch.h"
#include "recv.h"
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>



void fn_send(int i, SFrame *frame) {

	//SFrame frame1;
	//memcpy(&frame1, frame, sizeof(message_buf));
	//printf("[S2] Length: %d\n", frame->ach_Length);
	
	// 
	int msqid;
	int msgflg = IPC_CREAT | 0666;
	key_t key;
	message_buf sbuf;
	key = 1100 + i;
	
	//(void) fprintf(stderr, "\nmsgget: Calling msgget(%#lx,\%#o)\n",key, msgflg);
    if ((msqid = msgget(key, msgflg )) < 0) {
        perror("msgget");
        exit(1);
    }
    else 
    {
		(void) fprintf(stderr,"msgget: msgget succeeded: msqid = %d\n", msqid);
	}
	sbuf.mtype = 1;
	(void) fprintf(stderr,"msgget: msgget succeeded: msqid = %d\n", msqid);
	//sbuf.frame = frame1;
	//memcpy((void *)&(sbuf.frame), (void *) frame, sizeof(message_buf));
	memcpy(&(sbuf.frame), frame, sizeof(SFrame));
	printf("frame1 Length: %d\n", sbuf.frame.ach_Length);
	(void) fprintf(stderr,"msgget: msgget succeeded: msqid = %d\n", msqid);
	
	if (msgsnd(msqid, &sbuf, sizeof(sbuf.frame), IPC_NOWAIT) < 0) {
		//printf("%d %"l %l \n", msqid, sbuf.mtype, sizeof(sbuf.frame1) );
		perror("msgsnd");
		exit(1);
	} else 
		printf("Message: Sent\n");
}