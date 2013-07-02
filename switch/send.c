#include <stdio.h>
#include <stdlib.h>
#include "switch.h"
#include "recv.h"
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

void fn_send(int i, SFrame *frame) {
	int msqid;
	int msgflg = IPC_CREAT | 0666;
	key_t key;
	message_buf sbuf;
	//key = 1100 + i;
	key = 1234;
	
	
	printf("%d %d\n", key,i );

    if ((msqid = msgget(key, msgflg )) < 0) {
        perror("msgget");
        exit(1);
    }
    else 
		(void) fprintf(stderr,"msgget: msgget succeeded: msqid = %d\n", msqid);
	
	sbuf.mtype = 1;
	(void) fprintf(stderr,"msgget: msgget succeeded: msqid = %d\n", msqid);
	memcpy((void *) &sbuf.frame, (void *) frame, sizeof(message_buf));
	printf("duap= %d\n", sbuf.frame.ach_Length);
	printf("Frame Length: %d\n", sbuf.frame.ach_Length);
	(void) fprintf(stderr,"msgget: msgget succeeded: msqid = %d\n", msqid);
	printf("sizeof: %d\n", sizeof(sbuf.frame));
	//if (msgsnd(msqid, &sbuf, sizeof(sbuf.frame), IPC_NOWAIT) < 0) {
	if (msgsnd(msqid, &sbuf, sizeof(sbuf.frame), IPC_NOWAIT) < 0) {
		//printf("%d %"l %l \n", msqid, sbuf.mtype, sizeof(sbuf.frame) );
		perror("msgsnd");
		exit(1);
	} else 
		printf("Message: Sent\n");
}
