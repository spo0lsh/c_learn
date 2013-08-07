#ifndef __fifo3_H
#define __fifo3_H
#define BUFFER_SIZE 10

/* Circular buffer object */
typedef struct {
    int size;   /* maximum number of elements           */
    int start;  /* index of oldest element              */
    int count;    /* index at which to write new element  */
    int array[BUFFER_SIZE];  /* vector of elements                   */
} CircularBuffer;

void cbInit(CircularBuffer *);

int cbIsFull(CircularBuffer *);
 
int cbIsEmpty(CircularBuffer *);
 
void cbWrite(CircularBuffer *, int );

void cbRead(CircularBuffer *, int *);


#endif /* __fifo3_H */
