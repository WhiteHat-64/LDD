#include <linux/module.h>
#include <linux/init.h>
#include <linux/i2c.h>
#include <linux/of_device.h>
#include <linux/kthread.h>
#include <linux/jiffies.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");

/* Standard driver model interfaces */
static int my_mpu6050_probe(struct i2c_client *, const struct i2c_device_id *);
static int my_mpu6050_remove(struct i2c_client *);
static int my_mpu6050_read(struct i2c_client *my_i2c_cl, unsigned char addr, void* buf, unsigned long int count);
static int my_mpu6050_heartbeat(void*data);
static int my_mpu6050_init(void);


static unsigned char send_data[10]={0};
static unsigned char recv_data[10]={0};

struct i2c_device_id my_devid_table[] = {
	{"mpu6050",1},
	{},
};

MODULE_DEVICE_TABLE(i2c, my_devid_table);

struct of_device_id my_match_table[] = {
	{
		.name = "mpu6050",
		.compatible = "invense,mpu6050",
	},
	{},
};

struct i2c_driver my_mpu6050 = {
	.driver = {
		.name = "mpu6050",			//driver name
		.owner = THIS_MODULE,			//self reference
		.of_match_table = my_match_table,	//match table to match with the board file info
	},
	.probe = my_mpu6050_probe,			//function which connects driver and the device
	.remove = my_mpu6050_remove,			//function which disconnects driver and the device
	.id_table = my_devid_table,			//to mention the devices supported by this driver
};

/* Standard driver model interfaces */
static int my_mpu6050_probe(struct i2c_client *my_i2c_cl, const struct i2c_device_id *my_i2c_devid)
{
	struct task_struct *thread1;

	printk("mpu6050 probe called\n");
	printk("i2c device name: %s, i2c device addr: 0x%x\n", my_i2c_cl->name, my_i2c_cl->addr);

	//send_data[0] = my_i2c_cl->addr;
	
	thread1 = kthread_run(my_mpu6050_heartbeat,my_i2c_cl,"[[mpu6050 heartbeat]]");
	if(thread1 == NULL)
		printk("thread1 creation failed\n");

	//device init

	return 0;
}

static int my_mpu6050_read(struct i2c_client *my_i2c_cl, unsigned char addr, void* buf, unsigned long int count)
{
	i2c_master_send(my_i2c_cl,&addr,1);   // send devaddr with read bit, register address, stop
	i2c_master_recv(my_i2c_cl,(unsigned char*)buf,1);   // read 1 byte from this slave
	return 0;
}

static int my_mpu6050_write(struct i2c_client *my_i2c_cl, void* buf, unsigned long int count)
{
        i2c_master_send(my_i2c_cl,(unsigned char*)buf,count);   // send devaddr with read bit, register address, stop
        return 0;
}

static int my_mpu6050_heartbeat(void*data)
{
	static unsigned int state_change = 0, dead_count=0, alive_count=0;
	struct i2c_client * my_i2c_cl = (struct i2c_client *) data;
	while(1)
	{
		my_mpu6050_read(my_i2c_cl, 0x75, recv_data, 1); //reading the WHO_AM_I register 
		if(recv_data[0] == 0x68)
		{	
			dead_count = 0;		//resetting the dead_count to 0
			state_change = 1;	//changed to 1 when the mpu6050 is alive
			recv_data[0] = 0;	//clearing the return value of i2crecv
			alive_count ++;		//counting for device alive state
		}
		else
		{
			alive_count =0;		//resetting the alive count as the device is dead
			state_change = 0;	//setting state change to 0;
			dead_count ++;		//counting for device dead state
		}

		if(state_change == 1 && alive_count==1)
			printk("mpu6050 is alive\n");
		else if(state_change == 0 && dead_count == 1)
			printk("mpu6050 is dead\n");
		else
			{}

		usleep_range(500000,500001);		//delay of 500 ms
	}
	return 0;
}

static int my_mpu6050_remove(struct i2c_client *my_i2c_cl)
{
	printk("mpu6050 remove called\n");
	return 0;
}

module_i2c_driver(my_mpu6050);


static int my_mpu6050_init(struct i2c_client *my_i2c_cl)
{
	unsigned char temp[2]={0};
	temp[0] = 0x6B;
	
	//wake up	
	my_mpu6050_read(my_i2c_cl, temp[0], &temp[1], 1); //reading the PWR_MNGMT_1 register 
	temp[1] &= 0xBF// clearing sleep bit, to wake up the device (10111111)
	my_mpu6050_write(my_i2c_cl, temp, 2); //writing the PWR_MNGMT_1 register


}


/*
static int my_init(void)
{
  printk("i am in module init\n");
  return 0;
}*/

/*
static void my_exit(void)
{
  printk("i am in module exit\n");

}*/

//use these two macros to inform kernel about init and exit funcitons
//module_init(my_init);
//module_exit(my_exit);


