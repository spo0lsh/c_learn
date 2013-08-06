#include <stdio.h>
#include <stdlib.h>
#include "fifo2.h"
#define DEBUG


// http://pl.wikipedia.org/wiki/Plik:Bufor_cykliczny_1.png

int main() {
	RingBuffer rb; /* */
	
	RingBufferInit(&rb);
	RingBufferFree(&rb);
	
	return(0);
}


/* init */
void RingBufferInit(RingBuffer *rb)
{
	int i;
	rb->size = 0;
	rb->start = 0;
	rb->end = 0;
	for(i=0;i<BUFFER_SIZE;++i)
	{
		rb->buf_value[i] = -1;
	}
}
/* free */
void RingBufferFree(RingBuffer *rb)
{
	rb=NULL;
}
/* full */
int RingBufferFull(RingBuffer *rb)
{
	return(0);
}
/* empty */
int RingBufferEmpty(RingBuffer *rb)
{
	return(0);
}
/* read */
void RingBufferWrite(RingBuffer *rb, char *value)
{
}
/* write */
void RingBufferRead(RingBuffer *rb, char *value)
{
}
