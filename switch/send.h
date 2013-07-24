#ifndef __send_H
#define __send_H

#ifndef __recv_H
typedef struct {
	long    d_Mtype;
	SFrame s_Frame;
} SMessage_buf;
#endif /* __recv_H */

void fn_send(int , SFrame *);

#endif /* __send_H */
