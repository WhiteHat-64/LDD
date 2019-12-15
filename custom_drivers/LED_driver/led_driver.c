#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>                 // Required for the GPIO functions
#include <linux/interrupt.h>            // Required for the IRQ code


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hafizulla Khan");
MODULE_DESCRIPTION("This is the sample LED driver based on gpio subsystem in Beagle bone board");
MODULE_VERSION("0.1");



unsigned int gpio_led = 48;
int ret_gprq=0;

static int myled_init(void)
{
	printk("myled driver is initialized\n");
	ret_gprq = gpio_request(gpio_led,"myled");
	if(ret_gprq)
	{
		printk("ret_gprq %d: problem in getting gpio %d\n",ret_gprq, gpio_led);
		return 2;
	}
	if(!gpio_direction_output(gpio_led,1))
	{
		printk("pin state is set to 1\n");	//making the pin as output and led is on
	}
	else
	{
		printk("init: error in setting in pin state\n");
		return 2;
	}
	return 0;
}

static void myled_exit(void)
{
	gpio_set_value(gpio_led,0);	//led_off
	printk("pin state is set to 0\n");
	
	gpio_free(gpio_led);
	printk("gpio %d is released\n",gpio_led);
}


module_init(myled_init);
module_exit(myled_exit);

