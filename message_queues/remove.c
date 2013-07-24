#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h> 
#include <sys/msg.h>

typedef struct {
	unsigned char ach_MACdst[6];
	unsigned char ach_MACsrc[6];
	int ach_Length;
	char ach_Payload[46]; // minimal
	char ach_crc[4]; // 32bit crc
} SFrame;

typedef struct msgbuf {
	long    mtype;
	SFrame frame;
} message_buf;



/*
int main() {
key_t key;
int i;
for(i=0;i<20;++i){
key = 1000 + i;
int msqid = msgget(key, 0666);
 if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        //exit(1);
    }
}
}
* */

int main() {
key_t key;
int i;
 int msqid;
for(i=0;i<10;++i){
key = 1000 + i;
		printf("create %d: \n", i);
 if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }
printf("remove %d: \n", i);
if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }
}
}

//message_buf sbuf;
//sbuf.mtype = 1;

//if (msgctl(msqid, IPC_RMID, &sbuf) == -1) {
//perror("msgctl: msgctl failed");
//exit(1);
//}

//if (msgctl(msqid, IPC_SET, &sbuf) == -1) {
//perror("msgctl: msgctl failed");
//exit(1);

//}
