#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/i2c.h>
#include <linux/module.h>
#include <linux/of_device.h>
#include <linux/err.h>
#include <linux/jiffies.h>
#include "mpu6050.h"


MODULE_AUTHOR("SOL");
MODULE_DESCRIPTION("SOL device MPU6050 driver");
MODULE_LICENSE("GPL");
                          

unsigned char seqw[3]={REG_WHO_AM_I};
unsigned char seqrbuf[3]={0};
unsigned short int temp16bit = 0;
unsigned long int cur_jiffies = 0;
unsigned long int exp_jiffies = 0;
unsigned char i=0;
static short int temp_raw = 0;
static float temperature = 0;
static unsigned short reg_add = 0;
struct task_struct* heart_beat_func = NULL;

module_param(reg_add, ushort, 0);


int mpu_6050_heart_beat(void * data);
int mpu_6050_probe(struct i2c_client * mpu_client, const struct i2c_device_id * mpu_dev_id);
int mpu_6050_remove(struct i2c_client *mpu_client);
//static void mpu_6050_accel_func(void);

static const struct of_device_id mpu_6050_of_match[] = {
        {
                .compatible = "invense,mpu6050",
        },
	{
	}
};
MODULE_DEVICE_TABLE(of, mpu_6050_of_match);

static const struct i2c_device_id mpu_6050_id[] = {
        {"mpu6050", 1},
        {}
};


static struct i2c_driver mpu_6050_driver = {
        .probe          =       mpu_6050_probe,
        .remove         =       mpu_6050_remove,
        .id_table       =       mpu_6050_id,
        .driver = {
                .of_match_table = mpu_6050_of_match,
                .name   =       "sol-mpu6050",
        },
};

/*void mpu_6050_accel_func()
{
        seqw[0] = REG_ACCEL_XOUT_H;

        for (i=0;i<20;i++)
        {
                if(1 == i2c_master_send(mpu_client, seqw, 1))
                {
                        if(2 == i2c_master_recv(mpu_client, seqrbuf, 2))
                        {
                                cur_jiffies = jiffies;
                                exp_jiffies = cur_jiffies + HZ/2;
                                while(cur_jiffies < exp_jiffies);

                                temp16bit = (seqrbuf[0]<<8) | seqrbuf[1];
                                printk("mpu6050: sample %u==> ACCEL_XOUT value is %u\n", i, temp16bit);
                        }
                }

        }

}*/


int mpu_6050_probe(struct i2c_client * mpu_client, const struct i2c_device_id * mpu_dev_id)
{
	heart_beat_func = kthread_create(mpu_6050_heart_beat,mpu_client,"mpu_6050 HeartBeat");
	
	if(heart_beat_func != NULL)
	{
		wake_up_process(heart_beat_func);
	}
	else
	{
		printk("Heartbeat thread creation failed...\n");
	}

	if(1 == i2c_master_recv(mpu_client, seqrbuf, 1))
		printk("mpu6050: data read form mpu6050 is 0x%.2x\n",seqrbuf[0]);
	else
		printk("mpu6050: issue in recving data\n");

	seqw[0] = REG_PWR_MGMT_1;
	seqw[1] = 0x00;	//this is to wake up the device

	if(2 == i2c_master_send(mpu_client,seqw,2))
                printk("mpu6050: waking up the device\n");

	seqw[0] = REG_TEMP_OUT_H;
	if(1 == i2c_master_send(mpu_client, seqw, 1))
	{
		if(2 == i2c_master_recv(mpu_client, seqrbuf, 2))
		{
			temp_raw = (seqrbuf[0]<<8) | seqrbuf[1];
			temperature = (temp_raw/360.0)+36.53;
			printk("mpu6050: raw temperature is %d\n", temp_raw);
			printk("mpu6050: temperature is %f\n", temperature);
		}
	}


	if(1 == i2c_master_send(mpu_client, (char*)&reg_add, 1))
	{
		if(2 == i2c_master_recv(mpu_client, seqrbuf, 2))
		{
			//temp16bit = (seqrbuf[0]<<8) | seqrbuf[1];
			printk("mpu6050: sample %u==> ACCEL_XOUT value is 0x%.2x%.2x\n", i, seqrbuf[1], seqrbuf[0]);
		}
	}

	return 0;
}

int mpu_6050_remove(struct i2c_client *mpu_client)
{
	if(heart_beat_func != NULL)
	{
		kthread_stop(heart_beat_func);
	}
	printk("mpu_6050 is removed.\n");
	return 0;
}

module_i2c_driver(mpu_6050_driver);


int mpu_6050_heart_beat(void * data)
{
	struct i2c_client * mpu_client = (struct i2c_client *)data;
	int i;
	unsigned char l_seqw[3]={REG_WHO_AM_I};
	printk("mpu6050: Heartbeat is running...\n");
	while(1)
	{
		i = i2c_master_send(mpu_client,l_seqw,1);

        	if(1 == i)
                	printk("mpu6050: read request sent successfully\n");
        	else
                	printk("mpu6050: problem in sending read request\n");
		usleep_range(50000,50001);
	}

}


