#ifndef __recv_H
#define __recv_H

#ifndef __send_H
typedef struct {
	long    d_Mtype;
	SFrame s_Frame;
} SMessage_buf;
#endif
int fn_recv(int ,SFrame *);

#endif /* __recv_H */
