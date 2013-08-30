#ifndef __ringbuffor_H
#define __ringbuffor_H

#define BUFFER_SIZE 256 /* size of ring buffor */
/* defines the magic number */
#define MY_MACIG 'G'
/* IOCTL to read */
#define READ_IOCTL _IOR(MY_MACIG, 0, int)
/* IOCTL to write */
#define WRITE_IOCTL _IOW(MY_MACIG, 1, int)
/* IOCTL checking status EMPTY */
#define EMPTY_IOCTL _IO(MY_MACIG, 2)
/* IOCTL checking status FULL */
#define FULL_IOCTL _IO(MY_MACIG, 3)
/* IOCTL clear data */
#define CLEAR_IOCTL _IO(MY_MACIG, 4)
/* IOCTL buffor usage (size of data) */
#define SIZE_IOCTL _IO(MY_MACIG, 5)

typedef struct {
	int size;   /* maximum number of elements            */
	int start;  /* index of oldest element               */
	int count;    /* index at which to write new element */
	char array[BUFFER_SIZE];  /* array of elements      */
} CircularBuffer;

#endif /* __ringbuffor_H */
