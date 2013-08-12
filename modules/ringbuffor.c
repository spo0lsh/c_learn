#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#define BUFFER_SIZE 3
#define MY_MACIG 'G'
#define READ_IOCTL _IOR(MY_MACIG, 0, int)
#define WRITE_IOCTL _IOW(MY_MACIG, 1, int)
#define DEBUG

typedef struct {
	int size;   /* maximum number of elements           */
	int start;  /* index of oldest element              */
	int count;    /* index at which to write new element  */
	char array[BUFFER_SIZE];  /* vector of elements                   */
} CircularBuffer;

static CircularBuffer cb; // global variable for CB
static char c;
static dev_t first; // Global variable for the first device number 
static struct cdev c_dev; // Global variable for the character device structure
static struct class *cl; // Global variable for the device class



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

void cbWrite(CircularBuffer *cb,  char value)
{
	#ifdef DEBUG
	printk(KERN_INFO "[W] %d %0x\n", value,value);
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
	printk(KERN_INFO "[W] start %d count %d\n",cb->start,cb->count);
	#endif
}
 
void cbRead(CircularBuffer *cb,  char  *value)
{
    *value=cb->array[cb->start];
    cb->array[cb->start]=0;
    #ifdef DEBUG
    printk(KERN_INFO "[R] %d %0x\n", ( char )*value,( char )*value);
    #endif
    cb->start=(cb->start + 1) % cb->size;
    --cb->count;
}


static int my_open(struct inode *i, struct file *f)
{
  printk(KERN_INFO "Driver: open()\n");
  return 0;
}
  static int my_close(struct inode *i, struct file *f)
{
  printk(KERN_INFO "Driver: close()\n");
  return 0;
}

static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
    printk(KERN_INFO "Driver: read()\n");
    if (*off == 0)
    {
        if (copy_to_user(buf, &c, 1) != 0)
            return -EFAULT;
        else
        {
            (*off)++;
            return 1;
        }
    }
    else
    {
        return 0;
	}
}

static ssize_t my_write(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
  printk(KERN_INFO "Driver: write()\n");

    //if(copy_from_user(&c, buf + len - 1,1) != 0)
    //printk(KERN_INFO "buf = %s clen = %d\n",len);
    int i;
    for(i=0;i<len;++i)
    {
		printk(KERN_INFO "[%d]buf = %c clen = %d\n",i+1,(char)buf[i],len);
		copy_from_user(&c, buf + i,1); /* copy from user to kernel space */
		cbWrite(&cb,c);
	}
    if(copy_from_user(&c, buf + len - 1,1) != 0)
    //cbWrite(&cb, (unsigned int)value)
    {
        return -EFAULT;
	}
    else
    {
        return len;
	}
  return len;
}

char buf[200];
int my_ioctl(struct inode *inode, struct file *f, unsigned int cmd, unsigned long arg)
{
	int len = 200;
	switch(cmd) {
	case READ_IOCTL:	
		if(copy_to_user((char *)arg, buf, 200) != 0) {
			return -EFAULT;
		}
		break;
	
	case WRITE_IOCTL:
		if(copy_from_user(buf, (char *)arg, len) !=0) {
			printk(KERN_INFO "ioctl write: something wrong\n");
		}
		break;

	default:
		return -ENOTTY;
	}
	return len;
}


  static struct file_operations pugs_fops =
{
  .owner = THIS_MODULE,
  .open = my_open,
  .release = my_close,
  .read = my_read,
  .write = my_write,
  .ioctl = my_ioctl
};
 
static int __init ofcd_init(void) /* Constructor */
{
  printk(KERN_INFO "Namaskar: ofcd registered");
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
 
static void __exit ofcd_exit(void) /* Destructor */
{
	//cbRead(&cb,&c);
	//cbRead(&cb,&c);
	printk(KERN_INFO "[EXIT] %d [%c]\n",cb.array[0],cb.array[0]);
	printk(KERN_INFO "[EXIT] %d [%c]\n",cb.array[1],cb.array[1]);
	printk(KERN_INFO "[EXIT] %d [%c]\n",cb.array[2],cb.array[2]);
  cdev_del(&c_dev);
  device_destroy(cl, first);
  class_destroy(cl);
  unregister_chrdev_region(first, 1);
  printk(KERN_INFO "Alvida: ofcd unregistered");
}
 
module_init(ofcd_init);
module_exit(ofcd_exit);
MODULE_LICENSE("GPL");

