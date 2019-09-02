#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");

static int my_init(void)
{
  printk("i am in module init\n");
  return 0;
}


static void my_exit(void)
{
  printk("i am in module exit\n");

}

//use these two macros to inform kernel about init and exit funcitons
module_init(my_init);
module_exit(my_exit);


