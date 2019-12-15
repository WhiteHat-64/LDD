#include <linux/delay.h>
#include <linux/i2c.h>
#include <linux/module.h>
#include <linux/of_device.h>
#include <linux/err.h>



MODULE_AUTHOR("SOL");
MODULE_DESCRIPTION("SOL device MPU6050 driver");
MODULE_LICENSE("GPL");
                          

int mpu_6050_probe(struct i2c_client * mpu_client, const struct i2c_device_id * mpu_dev_id);
int mpu_6050_remove(struct i2c_client *mpu_client);

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

int mpu_6050_probe(struct i2c_client * mpu_client, const struct i2c_device_id * mpu_dev_id)
{
	printk("mpu_6050 is probed.\n");
	return 0;
}
int mpu_6050_remove(struct i2c_client *mpu_client)
{
	printk("mpu_6050 is removed.\n");
	return 0;
}

module_i2c_driver(mpu_6050_driver);
