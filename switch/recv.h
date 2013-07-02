#ifndef __recv_H
#define __recv_H

typedef struct msgbuf {
	long    mtype;
	SFrame frame;
} message_buf;

void fn_recv(int i,SFrame *frame);

#endif /* __recv_H */
