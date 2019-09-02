#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vinoth R");
MODULE_DESCRIPTION("Its a dummy driver writtent for learning purpose\n");
MODULE_VERSION("0.1");
MODULE_ALIAS("dummy driver");

dev_t my_dev;

