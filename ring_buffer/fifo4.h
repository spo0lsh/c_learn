#ifndef __fifo4_H
#define __fifo4_H
#define BUFFER_SIZE 10

/* Circular buffer object */
typedef struct {
    int size;   /* maximum number of elements           */
    int start;  /* index of oldest element              */
    int count;    /* index at which to write new element  */
    unsigned char array[BUFFER_SIZE];  /* vector of elements                   */
} CircularBuffer;

void cbInit(CircularBuffer *);

int cbIsFull(CircularBuffer *);
 
int cbIsEmpty(CircularBuffer *);
 
void cbWrite(CircularBuffer *, unsigned char  );

void cbRead(CircularBuffer *, unsigned char  *);


#endif /* __fifo4_H */
