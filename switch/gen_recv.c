#include <stdio.h>
#include <stdlib.h>
#include "gen_recv.h"
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <memory.h>
//#define DEBUG

int main() {
	int msqid;
    key_t key;
    message_buf  rbuf;
	SFrame *frame;

    /*
     * Get the message queue id for the
     * "name" 1234, which was created by
     * the server.
     */
    //key = 1234;
    key = ftok("/tmp/bridge0", 'b');
	
    if ((msqid = msgget(key, 0666)) < 0) {
        perror("msgget");
        exit(1);
    }

    /*
     * Receive an answer of message type 1.
     */
    if (msgrcv(msqid, &rbuf, sizeof(rbuf.frame), 1, 0) < 0) {
        perror("msgrcv");
        exit(1);
    }
	frame = &rbuf.frame;
	
    /*
     * Print the answer.
     */
	printf("%02x:%02x:%02x:%02x:%02x:%02x\n", frame->ach_MACdst[0], frame->ach_MACdst[1], frame->ach_MACdst[2], frame->ach_MACdst[3], frame->ach_MACdst[4], frame->ach_MACdst[5]);
	printf("%02x:%02x:%02x:%02x:%02x:%02x\n", frame->ach_MACsrc[0], frame->ach_MACsrc[1], frame->ach_MACsrc[2], frame->ach_MACsrc[3], frame->ach_MACsrc[4], frame->ach_MACsrc[5]);
	printf("Length: %d\n", frame->ach_Length);
	printf("Payload: %s\n", frame->ach_Payload);
	printf("CRC: %s\n", frame->ach_crc);


    return(EXIT_SUCCESS);
}
