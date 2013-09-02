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
} CircularBuffer; /* typedef */

/* must have */
MODULE_LICENSE("GPL");

/* init of ring buffor */
void init_ringbuffor(CircularBuffer *);

/* return 0 if Full */
int check_full_ringbuffor(CircularBuffer *);

/* return 0 if empty */
int check_empty_ringbuffor(CircularBuffer *);

/* write single char to ring buffor */
void write_to_ringbuffor(CircularBuffer *, char);

/* read single char from ring buffor */
void read_from_ringbuffor(CircularBuffer *, char *);

/* open /dev/ file */
static int my_open(struct inode *, struct file *);

/* close /dev/ file */
static int my_close(struct inode *, struct file *);

/* reading /dev/ file */
static ssize_t my_read(struct file *, char  *, 
								size_t , loff_t *);
								
/* writing /dev/ file */
static ssize_t my_write(struct file *, const char __user *, 
								size_t , loff_t *);

/* ioctl implementation */
int my_ioctl(struct inode *, struct file *, unsigned int , 
								unsigned long );

/* creating char device and init ring buffor */
static int __init ofcd_init(void);

/* close char device */
static void __exit ofcd_exit(void);

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
