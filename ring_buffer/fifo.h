#ifndef __fifo_H
#define __fifo_H
#define BUFFER_SIZE 256

/* Opaque buffer element type.  This would be defined by the application. */
typedef struct { int value; } ElemType;

typedef struct {
	int size;				/* maximum number of elements */
	int start;				/* index of oldest element */
	int end;				/* index at which to write new element */
	ElemType *buffer_elements;	/* vector of elements */
} RingBuffer;

void RingBufferInit(RingBuffer *, int );

void RingBufferFree(RingBuffer *);

int RingBufferFull(RingBuffer *);

int RingBufferEmpty(RingBuffer *);

void RingBufferWrite(RingBuffer *, ElemType *);

void RingBufferRead(RingBuffer *, ElemType *);

#endif /* __fifo_H */
