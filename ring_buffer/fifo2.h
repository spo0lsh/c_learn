#ifndef __fifo2_H
#define __fifo2_H
#define BUFFER_SIZE 256

/* Opaque buffer element type.  This would be defined by the application. */
typedef struct { int value; } ElemType;
 
/* Circular buffer object */
typedef struct {
    int         size;   /* maximum number of elements           */
    int         start;  /* index of oldest element              */
    int         count;    /* index at which to write new element  */
    ElemType   *elems;  /* vector of elements                   */
} CircularBuffer;

void cbInit(CircularBuffer *cb, int size);

void cbFree(CircularBuffer *cb);

int cbIsFull(CircularBuffer *cb);
 
int cbIsEmpty(CircularBuffer *cb);
 
void cbWrite(CircularBuffer *cb, ElemType *elem);
 
void cbRead(CircularBuffer *cb, ElemType *elem);


#endif /* __fifo2_H */
