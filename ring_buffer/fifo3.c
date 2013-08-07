#include <stdio.h>
#include <stdlib.h>
#include "fifo3.h"
//#define DEBUG


// http://pl.wikipedia.org/wiki/Plik:Bufor_cykliczny_1.png


int main() {
	
	CircularBuffer cb;
	int *value;
	value = (int *)0; // cast must be
	
	printf("[ ] %d %0x\n", (int)value,(int)value); // cast must be
	
	cbInit(&cb);

	int i;
	for(i=0;i<20;++i)
	{
		value = (int *)i;
		printf("[T] %d %0x\n", (int)value,(int)value); // cast must be
		if(! cbIsFull(&cb)) { /* if not full */
			cbWrite(&cb, (int)value);
		} 
	}

	while(!cbIsEmpty(&cb)) 
	{
		cbRead(&cb, (int*)&value);
		printf("[P] %d %0x\n", (int)value,(int)value); // cast must be
	}
	
	return(0);
}


void cbInit(CircularBuffer *cb)
{
	int i;
	cb->size  = BUFFER_SIZE;
	cb->start = 0;
	cb->count = 0;
	for(i=0;i<BUFFER_SIZE;++i)
	{
		cb->array[i]=0;
	}
}

int cbIsFull(CircularBuffer *cb)
{
	return cb->count == cb->size;
}
 
int cbIsEmpty(CircularBuffer *cb)
{
	return cb->count == 0;
}
 
void cbWrite(CircularBuffer *cb, int value)
{
	#ifdef DEBUG
	printf("[W] %d %0x\n", value,value);
	#endif
    int end=(cb->start + cb->count) % cb->size;
    cb->array[end]=value;
    if (cb->count == cb->size) /* is full */
    {
        cb->start=(cb->start + 1) % cb->size; /* full, overwrite */
	}
    else
    {
        ++cb->count; /* count ++ */
	}
	#ifdef DEBUG
	printf("[W] start %d count %d\n",cb->start,cb->count);
	#endif
}
 
void cbRead(CircularBuffer *cb, int *value)
{
    *value=cb->array[cb->start];
    #ifdef DEBUG
    printf("[R] %d %0x\n", (int)*value,(int)*value);
    #endif
    cb->start=(cb->start + 1) % cb->size;
    --cb->count;
}
