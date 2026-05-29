#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>

MODULE_LICENSE("GPL-2.0");
MODULE_AUTHOR("Praveen");
MODULE_DESCRIPTION("Yocto Kernel Module");
MODULE_VERSION("1.0");

static int __init mymodule_init(void)
{
    printk(KERN_INFO "Mymodule loaded\n");
    return 0;
}

static void __exit mymodule_exit(void)
{
    printk(KERN_INFO "Mymodule unloaded\n");
}


module_init(mymodule_init);
module_exit(mymodule_exit);