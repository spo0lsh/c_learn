#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#define MY_MACIG 'G'
#define READ_IOCTL _IOR(MY_MACIG, 0, int)
#define WRITE_IOCTL _IOW(MY_MACIG, 1, int)
 
static int major; 
static char msg[200];
char buf[200];

typedef struct {
    int size;   /* maximum number of elements           */
    int start;  /* index of oldest element              */
    int count;    /* index at which to write new element  */
    char msg[200];  /* elements  */
} CircularBuffer;


static ssize_t device_read(struct file *filp, char __user *buffer, size_t length, loff_t *offset)
{
  	return simple_read_from_buffer(buffer, length, offset, msg, 200); // read from kernel
}


static ssize_t device_write(struct file *filp, const char __user *buff, size_t len, loff_t *off)
{
	if (len > 199)
		return -EINVAL;
	//copy_from_user(msg, buff, len); // write to kernel
	if(copy_from_user(msg, buff, len) != 0) {
		return -EFAULT;
	} 
	else 
	{
		msg[len] = '\0';
		return len;
	}
}

int device_ioctl(struct inode *inode, struct file *filep, unsigned int cmd, unsigned long arg) {
	int len = 200;
	switch(cmd) {
	case READ_IOCTL:	
		//copy_to_user((char *)arg, buf, 200);
		if(copy_to_user((char *)arg, buf, 200) != 0) {
			printk(KERN_INFO "ioctl read: something wrong\n");
		}
		break;
	
	case WRITE_IOCTL:
		if(copy_from_user(buf, (char *)arg, len) != 0) {
			printk(KERN_INFO "ioctl write: something wrong\n");
		}
		break;

	default:
		return -ENOTTY;
	}
	return len;

}
static struct file_operations fops = {
	.read = device_read, 
	.write = device_write,
	.ioctl = device_ioctl,
};

static int __init cdevexample_module_init(void)
{
	major = register_chrdev(0, "ringbuffor", &fops);
	if (major < 0) {
     		printk ("Registering the character device failed with %d\n", major);
	     	return major;
	}
	printk("cdev example: assigned major: %d\n", major);
	printk("create node with mknod /dev/ringbuffor c %d 0\n", major);
 	return 0;
}

static void __exit cdevexample_module_exit(void)
{
	unregister_chrdev(major, "ringbuffor");
}  

module_init(cdevexample_module_init);
module_exit(cdevexample_module_exit);
