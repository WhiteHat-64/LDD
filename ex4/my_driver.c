#include "my_driver.h"

static dev_t my_dev = 0;
static unsigned char *buff=NULL;
static unsigned char ref_count=0;
static struct cdev *my_cdev = NULL;

int my_open (struct inode *inode_, struct file *file_){
	int loop1=0;
	unsigned char val;
	printk("Open called...\n");
	ref_count +=1;
	if (ref_count==1){
		printk("Allocating resources...");
		//allocating memory for the device.
		//arg1 is number of bytes that has to be allocated.
		//arg2 is the default flag.
		buff = (unsigned char*) kmalloc(MAX_BUFF_SIZE, GFP_KERNEL);
		
		if (NULL == buff){
			printk("Resource allocation failed...");
			return ENOMEM;
		}

		for(loop1=0,val=0x21; loop1<MAX_BUFF_SIZE; loop1++){
			buff[loop1] = val++;
			if(val >= 0x7E){
				val = 0x21;
			}
		}
	}

	printk("Instance %d is opened.",ref_count);
	return 0;
}

ssize_t my_read (struct file *file_, char __user *user_buf, size_t size_, loff_t *offset){
	size_t size;
	loff_t off = *offset;
	unsigned long ret_ctu;
	
	size = (size_ + off <= MAX_BUFF_SIZE) ? size_ : MAX_BUFF_SIZE - off;

	ret_ctu = copy_to_user(user_buf, buff+off, size);
	
	size = (0 == ret_ctu) ?  size  : (size - ret_ctu);
	
	printk("read: offset = %lld size = %ld no_bytes = %ld ret_ctu = %ld\n",off,size_, size, ret_ctu);
	*offset += size;

	return size;
}

ssize_t my_write (struct file *file_, const char __user *user_buf, size_t size_, loff_t *offset){
	size_t size;
	loff_t off = *offset;
	unsigned long ret_ctu;
	
	size = (size_ + off <= MAX_BUFF_SIZE) ? size_ : MAX_BUFF_SIZE - off;

	ret_ctu = copy_from_user(buff+off,user_buf, size);
	
	size = (0 == ret_ctu) ?  size  : (size - ret_ctu);
	
	printk("write: offset = %lld size = %ld no_bytes = %ld ret_ctu = %ld\n",off,size_, size, ret_ctu);
	*offset += size;

	return size;
}

int my_close (struct inode *inode_, struct file * file_){
	printk("Close called...\n");
	
	if(ref_count==0){
		printk("All instances are closed. releasing allocated resources\n");
		kfree(buff);
	}
	else{
		ref_count -= 1; 
		printk("One instance closed, remaining instances => %d\n",ref_count);
	}
	return 0;
}

static int my_init(void){
	// check  Documentation/devices.txt or /proc/devices for an unused major number
	unsigned char major_num = 237;	

	my_dev = MKDEV(major_num, 0);	//arg1 => major number, arg2 => minor number
	printk("Registering char device \"my_driver\"\n");
	// arg2 => number of minor numbers to be used, arg3 => name of the driver visible while checking in /proc/devices.
	if(0 != register_chrdev_region(my_dev,1,"my_device")){
	       printk("register_chrdev_region: failed to allocate major number\n");
	       return -1;
	}
	my_cdev = cdev_alloc();

	if(NULL == my_cdev){
		unregister_chrdev_region(my_dev,1);
		printk("cdev_alloc: failed to allocate chardev\n");
		return -1;
	}

	my_cdev->ops = &my_fops;
	my_cdev->owner = THIS_MODULE;
	
	// registering the character device to the kernel
	if(0 != cdev_add(my_cdev, my_dev, 1)){
		printk("cdev_add: failed to add device to kernel\n");
		cdev_del(my_cdev);
		unregister_chrdev_region(my_dev,1);

	}

  	return 0;
}


static void my_exit(void){
	printk("unregistering char device \"my_device\"\n");
	cdev_del(my_cdev);
	unregister_chrdev_region(my_dev,1);
}



//use these two macros to inform kernel about init and exit funcitons
module_init(my_init);
module_exit(my_exit);


