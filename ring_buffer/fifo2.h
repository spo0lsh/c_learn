#ifndef __fifo2_H
#define __fifo2_H
#define BUFFER_SIZE 256

typedef struct {
	int size;				/* maximum number of elements */
	int start;				/* index of oldest element */
	int end;				/* index at which to write new element */
	int buf_value[BUFFER_SIZE];	/* vector of elements */
} RingBuffer;

/* init */
void RingBufferInit(RingBuffer *);
/* free */
void RingBufferFree(RingBuffer *);
/* full */
int RingBufferFull(RingBuffer *);
/* empty */
int RingBufferEmpty(RingBuffer *);
/* read */
void RingBufferWrite(RingBuffer *, char *);
/* write */
void RingBufferRead(RingBuffer *, char *);


#endif /* __fifo2_H */
