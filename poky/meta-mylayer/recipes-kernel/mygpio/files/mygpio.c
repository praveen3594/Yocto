#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>

#define GPIO_LED 21 
//#define GPIO_LED 533     // GPIO pin connected to LED
#define DEVICE_NAME "gpio_led"
#define CLASS_NAME  "gpio_class"

static dev_t dev;
static struct cdev gpio_cdev;
static struct class *gpio_class;



static int gpio_open(struct inode *inode, struct file *file)
{
    pr_info("GPIO Device opened\n");
    return 0;
}

static int gpio_release(struct inode *inode, struct file *file)
{
    pr_info("GPIO Device closed\n");
    return 0;
}

static ssize_t gpio_read(struct file *file, char __user *buf,
                         size_t len, loff_t *off)
{
    char gpio_state;
    gpio_state = gpio_get_value(GPIO_LED) ? '1' : '0';

    if (copy_to_user(buf, &gpio_state, 1))
        return -EFAULT;

    return 1; 
}

static ssize_t gpio_write(struct file *file, const char __user *buf,
                          size_t len, loff_t *off)
{
    char kbuf;

    if (copy_from_user(&kbuf, buf, 1))
        return -EFAULT;


    if (kbuf == '1')
        gpio_set_value(GPIO_LED, 1);
    else if (kbuf == '0')
        gpio_set_value(GPIO_LED, 0);

    return len;
}

static struct file_operations fops = {
    .owner   = THIS_MODULE,
    .open    = gpio_open,
    .read    = gpio_read,
    .write   = gpio_write,
    .release = gpio_release,
};



static int __init gpio_driver_init(void)
{
    /* Allocate device number */
    alloc_chrdev_region(&dev, 0, 1, DEVICE_NAME);

    /* Initialize cdev */
    cdev_init(&gpio_cdev, &fops);
    cdev_add(&gpio_cdev, dev, 1);

    /* Create class and device */
    gpio_class = class_create(THIS_MODULE, CLASS_NAME);

    device_create(gpio_class, NULL, dev, NULL, DEVICE_NAME);

    if (!gpio_is_valid(GPIO_LED)) {
        pr_err("Invalid GPIO\n");
        return -ENODEV;
    }

    gpio_request(GPIO_LED, "gpio_led");
    gpio_direction_output(GPIO_LED, 0);

    pr_info("GPIO Driver loaded successfully\n");
    return 0;
}


static void __exit gpio_driver_exit(void)
{
    gpio_set_value(GPIO_LED, 0);
    gpio_free(GPIO_LED);

    device_destroy(gpio_class, dev);
    class_destroy(gpio_class);
    cdev_del(&gpio_cdev);
    unregister_chrdev_region(dev, 1);

    pr_info("GPIO Driver unloaded\n");
}

module_init(gpio_driver_init);
module_exit(gpio_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("GPIO Kernel Driver for Raspberry Pi");
MODULE_VERSION("1.0");
