#include "my_driver.h"

static int my_init(void){
	unsigned char major_num = 237;	//run:$ "cat /proc/devices". check for an unused major number and pick

	my_dev = MKDEV(major_num, 0);	//arg1 => major number, arg2 => minor number
	printk("registering char device \"my_device\"\n");
	register_chrdev_region(my_dev,1,"my_device"); //arg2 => number of minor numbers to be used, arg3 => name of the driver visible while checking in /proc/devices.
  	return 0;
}


static void my_exit(void){
	printk("unregistering char device \"my_device\"\n");
	unregister_chrdev_region(my_dev,1);
}



//use these two macros to inform kernel about init and exit funcitons
module_init(my_init);
module_exit(my_exit);


