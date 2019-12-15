#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#define DEV_SIZE 1024
MODULE_LICENSE("GPL");

static int driver1_init(void);
static void driver1_exit(void);
int driver1_open (struct inode *, struct file *);
ssize_t driver1_read (struct file *, char __user *, size_t, loff_t *);
ssize_t driver1_write (struct file *, const char __user *, size_t, loff_t *);
int driver1_close (struct inode *, struct file *);
loff_t driver1_lseek (struct file *, loff_t, int);

dev_t dev_number = MKDEV(220,0);
unsigned char *buffer=NULL;

struct cdev * my_cdev = NULL;
struct file_operations fops = {
	.open = driver1_open,
	.read = driver1_read,
	.write = driver1_write,
	.release = driver1_close,
	.llseek = driver1_lseek
};
// fops.open = driver1_open;


int driver1_open (struct inode *inodep, struct file *filep)
{
	unsigned char c;
	unsigned int i;
	unsigned int count;

	printk("open is called\n");
	printk("allocating memory\n");
	buffer = (unsigned char*)kmalloc(DEV_SIZE,GFP_KERNEL);

	//for testing purpose kernel data buffer is filled with printable char
	//usually this is not done by driver.	
	for(c='!',count=0,i=0; c<='~';c++,i++,count++)
	{
		buffer[i]=c;
	}
	printk("number of bytes initialized is %d\n",count);
	return 0;
}

ssize_t driver1_read (struct file *filep, char __user *userp, size_t size, loff_t *offp)
{
	unsigned char *p;
//	loff_t off = *offp;
	unsigned long int ret_cp;

	printk("read is called\n");
	printk("userp = %p size %lu offset %lld\n", userp, size, *offp);
	//jump to the offset
	p = buffer + *offp;
	
	//read number of bytes of data and store it in user buffer
	//for(loop1 = 0; loop1 < size; loop1++)
	//{
	//	userp[loop1] = *p++;
	//}
	ret_cp = copy_to_user(userp, p, size);	
	printk("ret_cp = %lu",ret_cp);
	*offp = *offp + size;

	return size-ret_cp;
}

ssize_t driver1_write (struct file *filep, const char __user *userp, size_t size, loff_t *offp)
{
	unsigned long ret_val;
	unsigned char *p;
	printk("write is called\n");
	// jump to the offset mentioned by user
	p = buffer + *offp;

	ret_val = copy_from_user(p, userp,size);
	
	*offp = *offp + size;
	return size - ret_val;
}

int driver1_close (struct inode *inodep, struct file *filep)
{

	printk("close is called\n");
	printk("freeing the allocated memory\n");
	kfree(buffer);
	return 0;
}


loff_t driver1_lseek (struct file *filep, loff_t offt, int ref)
{
	off_t offset = filep-> f_pos;
	printk("lseek is called. offset is %ld\n", offset);
	return offset;
}


static int driver1_init(void) {
	//register char driver
	register_chrdev_region(dev_number,1,"my_device");
	
	//allocating a cdev structure
	printk("allocating cdev structure\n");
	my_cdev = cdev_alloc();
	
	//assigning the operations to the cdev
	printk("assigning file operations into cdev structure\n");
	my_cdev->ops = &fops;

	// adding to the system
	printk("attaching cdev structure to the system\n");
	cdev_add(my_cdev,dev_number,1);

	printk("driver initializaion\n");
	return 0;
}

static void driver1_exit(void) {
	printk("removing from system and deleting cdev structure\n");
	cdev_del(my_cdev);
	//unregister char driver
	unregister_chrdev_region(dev_number,1);
	printk("driver removed\n");
}

module_init(driver1_init);
module_exit(driver1_exit);


