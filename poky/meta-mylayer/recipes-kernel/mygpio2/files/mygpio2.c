// #include <linux/module.h>
// #include <linux/kernel.h>
// #include <linux/init.h>
// #include <linux/fs.h>
// #include <linux/cdev.h>
// #include <linux/device.h>
// #include <linux/uaccess.h>
// #include <linux/gpio.h>

// #include <linux/mm.h>
// #include <linux/io.h>



// #define GPIO_LED 21   
// #define DEVICE_NAME "gpio_led"
// #define CLASS_NAME  "gpio_class"


// #define GPIO_BASE_PHYS  0xFE200000
// #define GPIO_SIZE      0x1000


// static dev_t dev;
// static struct cdev gpio_cdev;
// static struct class *gpio_class;

// /* ---------- File Operations ---------- */

// static int gpio_open(struct inode *inode, struct file *file)
// {
//     pr_info("GPIO Device opened\n");
//     return 0;
// }

// static int gpio_release(struct inode *inode, struct file *file)
// {
//     pr_info("GPIO Device closed\n");
//     return 0;
// }

// static ssize_t gpio_read(struct file *file, char __user *buf,
//                          size_t len, loff_t *off)
// {
//     char gpio_state;
//     gpio_state = gpio_get_value(GPIO_LED) ? '1' : '0';

//     if (copy_to_user(buf, &gpio_state, 1))
//         return -EFAULT;

//     return 1; 
// }

// static ssize_t gpio_write(struct file *file, const char __user *buf,
//                           size_t len, loff_t *off)
// {
//     char kbuf;

//     if (copy_from_user(&kbuf, buf, 1))
//         return -EFAULT;


//     if (kbuf == '1')
//         gpio_set_value(GPIO_LED, 1);
//     else if (kbuf == '0')
//         gpio_set_value(GPIO_LED, 0);

//     return len;
// }



// static int gpio_mmap(struct file *file, struct vm_area_struct *vma)
// {
//     unsigned long size = vma->vm_end - vma->vm_start;

//     if ((size) > (GPIO_SIZE))
//     {
//         pr_err("Requested mmap size too big\n");
//         return -EINVAL;
//     }

//     vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

//     if (remap_pfn_range(vma,
//                         vma->vm_start,
//                         GPIO_BASE_PHYS >> PAGE_SHIFT,
//                         size,
//                         vma->vm_page_prot))               
//         {
//         pr_err("remap_pfn_range failed\n");

//         return -EAGAIN;
//         }

//     pr_info("GPIO mmap successful\n");
//     return 0;
// }




// static struct file_operations fops = {
//     .owner   = THIS_MODULE,
//     .open    = gpio_open,
//     .read    = gpio_read,
//     .write   = gpio_write,
//     .mmap    = gpio_mmap,
//     .release = gpio_release,
// };



// static int __init gpio_driver_init(void)
// {
//     /* Allocate device number */
//     alloc_chrdev_region(&dev, 0, 1, DEVICE_NAME);

//     /* Initialize cdev */
//     cdev_init(&gpio_cdev, &fops);
//     cdev_add(&gpio_cdev, dev, 1);

//     /* Create class and device */
//     gpio_class = class_create(THIS_MODULE, CLASS_NAME);
//     //gpio_class = class_create(CLASS_NAME);

//     device_create(gpio_class, NULL, dev, NULL, DEVICE_NAME);


//     if (!gpio_is_valid(GPIO_LED)) {
//         pr_err("Invalid GPIO\n");
//         return -ENODEV;
//     }

//     gpio_request(GPIO_LED, "gpio_led");
//     gpio_direction_output(GPIO_LED, 0);

//     pr_info("GPIO Driver loaded successfully\n");
//     return 0;
// }


// static void __exit gpio_driver_exit(void)
// {
//     gpio_set_value(GPIO_LED, 0);
//     gpio_free(GPIO_LED);

//     device_destroy(gpio_class, dev);
//     class_destroy(gpio_class);
//     cdev_del(&gpio_cdev);
//     unregister_chrdev_region(dev, 1);

//     pr_info("GPIO Driver unloaded\n");
// }

// module_init(gpio_driver_init);
// module_exit(gpio_driver_exit);

// MODULE_LICENSE("GPL");
// MODULE_AUTHOR("Your Name");
// MODULE_DESCRIPTION("GPIO Kernel Driver for Raspberry Pi");
// MODULE_VERSION("1.0");











































// //Program  of 
// // ● Develop a simple C/C++ or Python application to control GPIOs via the custom device node.

// // ● Use ioctl(), read(), or write() for communication.

// // ● Demonstrate real-time control (e.g., toggle LED or read button state).


// user prgm is user_gpio_app.c

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>
#include <linux/ioctl.h>

#define GPIO_LED 21
#define DEVICE_NAME "gpio_led"
#define CLASS_NAME  "gpio_class"

static dev_t dev;
static struct cdev gpio_cdev;
static struct class *gpio_class;
#include <linux/ioctl.h>

/* Use 'G' as magic number */
#define GPIO_MAGIC 'G'

/* Define the IOCTL commands */
#define GPIO_SET_HIGH  _IO(GPIO_MAGIC, 1)
#define GPIO_SET_LOW   _IO(GPIO_MAGIC, 2)
#define GPIO_TOGGLE    _IO(GPIO_MAGIC, 3)

/* ---------- File Operations ---------- */

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

static ssize_t gpio_read(struct file *file, char __user *buf, size_t len, loff_t *off)
{
    char gpio_state;
    gpio_state = gpio_get_value(GPIO_LED) ? '1' : '0';

    if (copy_to_user(buf, &gpio_state, 1))
        return -EFAULT;

    return 1; 
}

static ssize_t gpio_write(struct file *file, const char __user *buf, size_t len, loff_t *off)
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


static long gpio_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    switch (cmd)
    {
        case GPIO_SET_HIGH:
            gpio_set_value(GPIO_LED, 1);
            break;

        case GPIO_SET_LOW:
            gpio_set_value(GPIO_LED, 0);
            break;

        case GPIO_TOGGLE:
        {
            int value = gpio_get_value(GPIO_LED);
            gpio_set_value(GPIO_LED, !value);
            break;
        }

        default:
            return -EINVAL;
    }

    return 0;
}


static struct file_operations fops = {
    .owner   = THIS_MODULE,
    .open    = gpio_open,
    .read    = gpio_read,
    .write   = gpio_write,
    .release = gpio_release,
    .unlocked_ioctl = gpio_ioctl,
};



static int __init gpio_driver_init(void)
{
    alloc_chrdev_region(&dev, 0, 1, DEVICE_NAME);

    cdev_init(&gpio_cdev, &fops);
    cdev_add(&gpio_cdev, dev, 1);

    gpio_class = class_create(THIS_MODULE, CLASS_NAME);
    //gpio_class = class_create(CLASS_NAME);

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
