#include <stdio.h>
#include <stdlib.h>
#include "fifo4.h"
//#define DEBUG


// http://pl.wikipedia.org/wiki/Plik:Bufor_cykliczny_1.png


int main() {
	
	CircularBuffer cb;
	unsigned char  *value;
	value = (unsigned char *)0xFF; // cast must be 
	value = (unsigned char *)10;  // cast must be
	printf("[ ] %d %02X\n", (unsigned int)value,(unsigned int)value); // cast must be

	cbInit(&cb);

	cbWrite(&cb, (unsigned int)value); //cbWrite(&cb, (unsigned char *)value);
	

	int i;
	for(i=0;i<10;++i)
	{
		value = (unsigned char *)i;
		printf("[T] %d %0X\n", (unsigned int)value,( unsigned int)value); // cast must be
		if(! cbIsFull(&cb)) { /* if not full */
			cbWrite(&cb, (unsigned int)value); //cbWrite(&cb, (unsigned char *)value);
		} 
	}
	while(!cbIsEmpty(&cb)) 
	{
		cbRead(&cb, (unsigned char*)&value);
		printf("[P] %d 0x%02X\n", (unsigned int)value,(unsigned int)value); // cast must be
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

void cbWrite(CircularBuffer *cb, unsigned char value)
{
	#ifdef DEBUG
	printf("[W] %d %0x\n", value,value);
	#endif
    int end=(cb->start + cb->count) % cb->size;
    cb->array[end]=value;
    if (cb->count == cb->size)
    {
        cb->start=(cb->start + 1) % cb->size;
	}
    else
    {
        ++cb->count; 
	}
	#ifdef DEBUG
	printf("[W] start %d count %d\n",cb->start,cb->count);
	#endif
}
 
void cbRead(CircularBuffer *cb, unsigned char  *value)
{
    *value=cb->array[cb->start];
    #ifdef DEBUG
    printf("[R] %d %0x\n", (unsigned char )*value,(unsigned char )*value);
    #endif
    cb->start=(cb->start + 1) % cb->size;
    --cb->count;
}

