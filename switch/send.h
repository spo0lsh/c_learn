#ifndef __send_H
#define __send_H

#ifndef __recv_H
typedef struct msgbuf {
	long    mtype;
	SFrame frame;
} message_buf;
#endif /* __recv_H */

void fn_send(int i, SFrame *frame);

#endif /* __send_H */
