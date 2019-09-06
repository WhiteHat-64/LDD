#ifndef _MY_DRIVER_H_
#define _MY_DRIVER_H_


#include <linux/module.h>	//module_init, module_exit
#include <linux/init.h>		
#include <linux/fs.h>		//struct_file_operations
#include <linux/slab.h>		//kmalloc
#include <linux/cdev.h>		//kmalloc
#include <linux/uaccess.h>	//copy_from_user

#define MAX_BUFF_SIZE 1024

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vinoth R");
MODULE_DESCRIPTION("Its a dummy driver writtent for learning purpose\n");
MODULE_VERSION("0.1");
MODULE_ALIAS("dummy driver");

int my_open (struct inode *inode_, struct file *file_);
ssize_t my_read (struct file *, char __user *, size_t, loff_t *);
ssize_t my_write (struct file *file_, const char __user *, size_t, loff_t *);
int my_close (struct inode *, struct file *);

struct file_operations my_fops={
	.owner = THIS_MODULE,
        .open = my_open,
        .read = my_read,
        .write = my_write,
        .release = my_close
};

static dev_t my_dev;
static unsigned char ref_count;
static unsigned char *buff;
static struct cdev *my_cdev;


#endif //_MY_DRIVER_
