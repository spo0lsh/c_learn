#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#define BUFFER_SIZE 5
#define MY_MACIG 'G'	// defines the magic number
#define READ_IOCTL _IOR(MY_MACIG, 0, int)
#define WRITE_IOCTL _IOW(MY_MACIG, 1, int)
#define EMPTY_IOCTL _IO(MY_MACIG, 2) // defines our ioctl call
#define FULL_IOCTL _IO(MY_MACIG, 3) // defines our ioctl call
#define CLEAR_IOCTL _IO(MY_MACIG, 4) // defines our ioctl call
#define SIZE_IOCTL _IO(MY_MACIG, 5) // defines our ioctl call
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
	int end;
	#ifdef DEBUG
	printk(KERN_INFO "[W] %d %02x [%c]\n", value,value,value);
	#endif
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
	

	#ifdef DEBUG
	printk(KERN_INFO "[W] start %d count %d\n",cb->start,cb->count);
	#endif
}
 
void cbRead(CircularBuffer *cb,  char  *value)
{
    *value=cb->array[cb->start];
    cb->array[cb->start]=0;
    #ifdef DEBUG
    printk(KERN_INFO "[R] %d %0x [%c]\n", ( char )*value,( char )*value,(char)*value);
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
static char msg[200];
static char dupa;
static ssize_t my_read(struct file *filp, char __user *buffer, size_t length, loff_t *offset)
{
	int i;
	for(i=0;i<BUFFER_SIZE;++i)
	{
		if(!cbIsEmpty(&cb)) {
			printk(KERN_INFO "[READ] is not empty\n");
			cbRead(&cb,&dupa);
			printk(KERN_INFO "dupa %d [%c]",dupa,dupa);
			msg[i]=dupa;
		}
		else
		{
			printk(KERN_INFO "[READ] is empty\n");
		}
	}
	return simple_read_from_buffer(buffer, length, offset, msg, 200);
}

static ssize_t my_write(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
	int i;
  printk(KERN_INFO "Driver: write()\n");

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

char buf[200]; //
int my_ioctl(struct inode *inode, struct file *f, unsigned int cmd, unsigned long arg)
{
	int i;
	int len = 200;
	char *temp;
	char ch;
	switch(cmd) {
	case READ_IOCTL:
		for(i=0;i<BUFFER_SIZE;++i)
		{
			cbRead(&cb,&ch);
			buf[i] = ch;
			printk(KERN_INFO "[IOCTL R] %d [%c]\n",ch,ch);
		}
		copy_to_user((char *)arg, buf, BUFFER_SIZE);
		/*	
		int i;
		for(i=0;i<BUFFER_SIZE;++i)
		{
			if(!cbIsEmpty(&cb)) {
				printk(KERN_INFO "[READ] is not empty\n");
				cbRead(&cb,&dupa);
				printk(KERN_INFO "dupa %d [%c]",dupa,dupa);
				msg[i]=dupa;
			}
			else
			{
				printk(KERN_INFO "[READ] is empty\n");
			}
		}
		return simple_read_from_buffer(buffer, length, offset, msg, 200);
		*/
		/*
		if(copy_to_user((char *)arg, buf, 200) != 0) {
			printk(KERN_INFO "ioctl read: something wrong\n");
			return -EFAULT;
		}
		*/
		break;
	
		case WRITE_IOCTL: // add something wronga!
			temp = (char *)arg;
			get_user(ch, temp);
			for (i = 0; ch && i < len; i++, temp++)
			{
				get_user(ch, temp);
				printk(KERN_INFO "[IOCTL W] [%d]arg = %d [%c]\n",i+1,ch,ch);
				cbWrite(&cb,ch);
			}
		break;

	case EMPTY_IOCTL:
		if(cbIsEmpty(&cb) != 0)
		{
			printk(KERN_INFO "ioctl empty\n");
			return -1;
		}
		break;
				
	case FULL_IOCTL:
		if(cbIsFull(&cb) != 0)
		{
			printk(KERN_INFO "ioctl full\n");
			return -1;
		}
		break;
/*		
	case CLEAR_IOCTL:
		printk(KERN_INFO "ioctl clear\n");
		break;
*/	 
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

	printk(KERN_INFO "[EXIT] %d [%c]\n",cb.array[0],cb.array[0]);
	printk(KERN_INFO "[EXIT] %d [%c]\n",cb.array[1],cb.array[1]);
	printk(KERN_INFO "[EXIT] %d [%c]\n",cb.array[2],cb.array[2]);
  cdev_del(&c_dev);
  device_destroy(cl, first);
  class_destroy(cl);
  unregister_chrdev_region(first, 1);
  printk(KERN_INFO "Alvida: ofcd unregistered");
  printk(KERN_INFO "--------------------------------------------------------------------");
}
 
module_init(ofcd_init);
module_exit(ofcd_exit);
MODULE_LICENSE("GPL");

