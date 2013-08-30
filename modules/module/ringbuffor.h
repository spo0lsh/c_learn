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

/* ring buffor structure */
typedef struct {
	int size;   /* maximum number of elements            */
	int start;  /* index of oldest element               */
	int count;    /* index at which to write new element */
	char array[BUFFER_SIZE];  /* array of elements      */
} CircularBuffer;

/* must have */
MODULE_LICENSE("GPL");


void cbInit(CircularBuffer *);
int cbIsFull(CircularBuffer *cb);
int cbIsEmpty(CircularBuffer *cb);
void cbWrite(CircularBuffer *cb,  char value);
void cbRead(CircularBuffer *cb,  char  *value);
static int my_open(struct inode *i, struct file *f);
static int my_close(struct inode *i, struct file *f);
static ssize_t my_read(struct file *filp, char __user *buffer, 
								size_t length, loff_t *offset);
static ssize_t my_write(struct file *f, const char __user *buf, 
								size_t len, loff_t *off);
int my_ioctl(struct inode *inode, struct file *f, unsigned int cmd, 
								unsigned long arg);


/* what we can to in /dev/ ... */
static struct file_operations pugs_fops =
{
	.owner = THIS_MODULE,
	.open = my_open,
	.release = my_close,
	.read = my_read,
	.write = my_write,
	.ioctl = my_ioctl
};

#endif /* __ringbuffor_H */
