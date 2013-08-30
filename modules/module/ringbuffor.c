#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/semaphore.h>
#include "ringbuffor.h"


/* global variable for CB */
static CircularBuffer cb; 
/* Global variable for one char */
static char ch; 
/* Global variable for buffor */
static char buf[BUFFER_SIZE]; 
/* Global variable for the first device number */
static dev_t first; 
/* Global variable for the character device structure */
static struct cdev c_dev; 
/* Global variable for the device class */
static struct class *cl; 
/* mutual exclusion semaphore */
struct semaphore sem;     


// init of ring buffor
void cbInit(CircularBuffer *cb)
{
	int i;
	cb->size  = BUFFER_SIZE;
	cb->start = 0;
	cb->count = 0;
	for(i=0;i<BUFFER_SIZE;++i) // zero for all array elements
	{
		cb->array[i]=0;
	}
}

// return 0 if Full
int cbIsFull(CircularBuffer *cb) 
{
	return cb->count == cb->size;
}

// return 0 if empty
int cbIsEmpty(CircularBuffer *cb) 
{
	return cb->count == 0;
}

// write single char to ring buffor
void cbWrite(CircularBuffer *cb,  char value)
{
	int end;
	//#ifdef DEBUG
	//printk(KERN_INFO "[W] %d %02x [%c]\n", value,value,value);
	//#endif
	end=(cb->start + cb->count) % cb->size;
    cb->array[end]=value;
    if (cb->count == cb->size)
    {
        cb->start=(cb->start + 1) % cb->size;
	}
    else
    {
        ++cb->count; 
	}
	

	//#ifdef DEBUG
	//printk(KERN_INFO "[W] start %d count %d\n",cb->start,cb->count);
	//#endif
}

// read single char from ring buffor
void cbRead(CircularBuffer *cb,  char  *value)
{
    *value=cb->array[cb->start];
    cb->array[cb->start]=0;
    //#ifdef DEBUG
    //printk(KERN_INFO "[R] %d %0x [%c]\n", ( char )*value,( char )*value,(char)*value);
    //printk(KERN_INFO "[R] %d %0x [%c]\n", cb->array[cb->start],cb->array[cb->start],cb->array[cb->start]);
    //#endif
    cb->start=(cb->start + 1) % cb->size;
    --cb->count;
}


static int my_open(struct inode *i, struct file *f)
{
	if(down_interruptible(&sem)) 
	{
		return -1;
		printk(KERN_INFO " could not hold semaphore");
	}
	
	printk(KERN_INFO "Driver: open()\n");
	return 0;
}

static int my_close(struct inode *i, struct file *f)
{
	up(&sem);
	printk(KERN_INFO "Driver: close()\n");
	return 0;
}

/* read from ring buffor and write to user */
static ssize_t my_read(struct file *filp, char __user *buffer, 
										size_t length, loff_t *offset)
{
	int i;
	printk(KERN_INFO "Driver: read()\n");
	if(!cbIsEmpty(&cb)) // if not empty
	{
		//printk(KERN_INFO "[READ] is not empty!\n");
		for(i=0;cb.count != 0;++i)
		{
			if(!cbIsEmpty(&cb)) { //if not mepty
				//printk(KERN_INFO "[READ] is not empty\n");
				cbRead(&cb,&ch);
				//printk(KERN_INFO "dupa %d [%c]\n",ch,ch);
				buf[i]=ch;
			}
		}
		return simple_read_from_buffer(buffer, length, offset, buf, i); // write to user
	}
	else
	{
		return simple_read_from_buffer(buffer, length, offset, buf, 0); // write to user (empty)
	}
	
}

/* write to ring buffor from user (/dev) */
static ssize_t my_write(struct file *f, const char __user *buf, 
								size_t len, loff_t *off)
{
	int i;
	printk(KERN_INFO "Driver: write()\n");

    for(i=0;i<len;++i)
    {
		//printk(KERN_INFO "[%d]buf = %c clen = %d\n",i+1,(char)buf[i],len);
		if(copy_from_user(&ch, buf + i,1) == 0) /* copy from user to kernel space */
		{
			cbWrite(&cb,ch); // if full, overwrite!
		}
	}
	return len;
}

/* ioctl */
int my_ioctl(struct inode *inode, struct file *f, unsigned int cmd, 
							unsigned long arg)
{
	int i;
	int len = BUFFER_SIZE;
	char *temp;
	switch(cmd) {
	// not needed
		case READ_IOCTL:
			printk(KERN_INFO "ioctl read\n");
			for(i=0;cb.count != 0;++i)
			{
				cbRead(&cb,&ch);
				buf[i] = ch;
	//			printk(KERN_INFO "[IOCTL R] %d [%c]\n",ch,ch);
			}
			if(copy_to_user((char *)arg, buf, BUFFER_SIZE) == 0) {
				
			}

		break;
	// not needed
		case WRITE_IOCTL: // add something wronga!
			printk(KERN_INFO "ioctl write\n");
			temp = (char *)arg;
			get_user(ch, temp);
			for (i = 0; ch && i < len; i++, temp++)
			{
				get_user(ch, temp);
				//printk(KERN_INFO "[IOCTL W] [%d]arg = %d [%c]\n",i+1,ch,ch);
				cbWrite(&cb,ch);
			}
		break;
	// empty?
		case EMPTY_IOCTL:
			if(cbIsEmpty(&cb) != 0)
			{
				printk(KERN_INFO "ioctl empty\n");
				return -1; // yes, is empty
			} 
			else 
			{
				printk(KERN_INFO "ioctl not empty\n");
			}
			break;
	// full?
		case FULL_IOCTL:
			if(cbIsFull(&cb) != 0)
			{
				printk(KERN_INFO "ioctl full\n");
				return -1; // yes, is full
			}
			else 
			{
				printk(KERN_INFO "ioctl not full\n");
			}
			break;
	// cleanup 
		case CLEAR_IOCTL:
			cbInit(&cb);
			printk(KERN_INFO "ioctl clear\n");
			break;
	// size
		case SIZE_IOCTL:
			printk(KERN_INFO "ioctl size\n");
			return cb.count;
			break;
	// ?!
		default:
			printk(KERN_INFO "ioctl default\n");
			return -ENOTTY;
	}
	return len;
}

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
 
/* creating char device and init ring buffor */
static int __init ofcd_init(void) /* Constructor */
{
	init_MUTEX(&sem);
	printk(KERN_INFO "Loading kernel\n");
	if (alloc_chrdev_region(&first, 0, 1, "Shweta") < 0)
	{
		return -1;
	}
	if ((cl = class_create(THIS_MODULE, "chardrv")) == NULL)
	{
		unregister_chrdev_region(first, 1);
		return -1;
	}
	if (device_create(cl, NULL, first, NULL, "ringbuffor") == NULL)
	{
		class_destroy(cl);
		unregister_chrdev_region(first, 1);
		return -1;
	}
	cdev_init(&c_dev, &pugs_fops);
	if (cdev_add(&c_dev, first, 1) == -1)
	{
		device_destroy(cl, first);
		class_destroy(cl);
		unregister_chrdev_region(first, 1);
		return -1;
	}
	cbInit(&cb);
  
	return 0;
}

/* close char device */
static void __exit ofcd_exit(void) /* Destructor */
{
	up(&sem);
	cdev_del(&c_dev);
	device_destroy(cl, first);
	class_destroy(cl);
	unregister_chrdev_region(first, 1);
	printk(KERN_INFO "Unloading module\n");
}

/* execute when load or remove */
module_init(ofcd_init);
module_exit(ofcd_exit);

