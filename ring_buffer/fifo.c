#include <stdio.h>
#include "fifo.h"
//#include <memory.h>
#include <stdlib.h>

int main() {
	RingBuffer ringbuffer;
	ElemType elem = {0};
	
	/* init */
	RingBufferInit(&ringbuffer,2);
	
	/* write */
	for (elem.value = 0; elem.value < 20; ++ elem.value) {
		printf("[%d]\tFull: %d\n",elem.value+1,RingBufferFull(&ringbuffer));
		if(! RingBufferFull(&ringbuffer)) { /* if not full */
			RingBufferWrite(&ringbuffer, &elem);
		}
	}
	
	/* read */
    while (!RingBufferEmpty(&ringbuffer)) {
        RingBufferRead(&ringbuffer, &elem);
        printf("%d\n", elem.value);
    }
	
	/* remove */
	RingBufferFree(&ringbuffer);
	
	return 0;
}

void RingBufferInit(RingBuffer *ringbuffer, int size) {
	ringbuffer->size = size + 1; /* include empty element */
	ringbuffer->start = 0;
	ringbuffer->end = 0;
	ringbuffer->buffer_elements = (ElemType *)calloc(ringbuffer->size, sizeof(ElemType));
	//ringbuffer->buffer_elements = (char *)calloc(ringbuffer->size,sizeof(char)); //rewrite to malloc
}

void RingBufferFree(RingBuffer *ringbuffer) {
	free(ringbuffer->buffer_elements);	/* free pointer */
	ringbuffer->buffer_elements=NULL;	/* set NULL */
}

int RingBufferFull(RingBuffer *ringbuffer) {
	return(ringbuffer->end +1) % ringbuffer->size == ringbuffer->start;
}

int RingBufferEmpty(RingBuffer *ringbuffer) {
	return ringbuffer->end == ringbuffer->start;
}

void RingBufferWrite(RingBuffer *ringbuffer, ElemType *buffer_elements) {
	ringbuffer->buffer_elements[ringbuffer->end] = *buffer_elements;
	ringbuffer->end = (ringbuffer->end +1) % ringbuffer->size;
	if(ringbuffer->end == ringbuffer->start) {
		ringbuffer->start = (ringbuffer->start + 1) % ringbuffer->size; /* full, overwrite - WRONG! */
	}
}

void RingBufferRead(RingBuffer *ringbuffer, ElemType *buffer_elements) {
	*buffer_elements = ringbuffer->buffer_elements[ringbuffer->start];
	ringbuffer->start = (ringbuffer->start +1) % ringbuffer->size;
}
