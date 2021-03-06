#ifndef __ioctl_H
#define __ioctl_H


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

#endif /* __ioctl_H */
