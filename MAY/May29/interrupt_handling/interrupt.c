#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/interrupt.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "interrupt_chardev"
#define CLASS_NAME  "mycharclass"
#define IRQ_NUMBER  1  // Example IRQ number

static int major_number;
static struct class*  char_class  = NULL;
static struct device* char_device = NULL;
static struct cdev my_cdev;

static irqreturn_t my_interrupt_handler(int irq, void *dev_id);
static int dev_open(struct inode *inodep, struct file *filep);
static int dev_release(struct inode *inodep, struct file *filep);
static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset);

static struct file_operations fops = {
    .open = dev_open,
    .read = dev_read,
    .release = dev_release,
};

static irqreturn_t my_interrupt_handler(int irq, void *dev_id)
{
    printk(KERN_INFO "Interrupt handled\n");
    return IRQ_HANDLED;
}

static int __init mychar_init(void)
{
    int ret;

    printk(KERN_INFO "Initializing the mychar device...\n");

    // Register a major number for the device
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        printk(KERN_ALERT "Failed to register a major number\n");
        return major_number;
    }
    printk(KERN_INFO "Registered correctly with major number %d\n", major_number);

    // Register the device class
    char_class = class_create(CLASS_NAME);
    if (IS_ERR(char_class)) {
        unregister_chrdev(major_number, DEVICE_NAME);
        printk(KERN_ALERT "Failed to register device class\n");
        return PTR_ERR(char_class);
    }
    printk(KERN_INFO "Device class registered correctly\n");

    // Register the device driver
    char_device = device_create(char_class, NULL, MKDEV(major_number, 0), NULL, DEVICE_NAME);
    if (IS_ERR(char_device)) {
        class_destroy(char_class);
        unregister_chrdev(major_number, DEVICE_NAME);
        printk(KERN_ALERT "Failed to create the device\n");
        return PTR_ERR(char_device);
    }
    printk(KERN_INFO "Device created correctly\n");

    // Initialize the cdev structure and add it to kernel space
    cdev_init(&my_cdev, &fops);
    my_cdev.owner = THIS_MODULE;
    ret = cdev_add(&my_cdev, MKDEV(major_number, 0), 1);
    if (ret < 0) {
        device_destroy(char_class, MKDEV(major_number, 0));
        class_destroy(char_class);
        unregister_chrdev(major_number, DEVICE_NAME);
        printk(KERN_ALERT "Failed to add cdev\n");
        return ret;
    }

    // Request IRQ
    ret = request_irq(IRQ_NUMBER, my_interrupt_handler, IRQF_SHARED, DEVICE_NAME, (void *)(my_interrupt_handler));
    if (ret) {
        printk(KERN_ALERT "mychar: cannot register IRQ %d\n", IRQ_NUMBER);
        cdev_del(&my_cdev);
        device_destroy(char_class, MKDEV(major_number, 0));
        class_destroy(char_class);
        unregister_chrdev(major_number, DEVICE_NAME);
        return ret;
    }

    printk(KERN_INFO "mychar: device driver initialized\n");
    return 0;
}

static void __exit mychar_exit(void)
{
    printk(KERN_INFO "Exiting the mychar device...\n");
    free_irq(IRQ_NUMBER, (void *)(my_interrupt_handler));
    cdev_del(&my_cdev);
    device_destroy(char_class, MKDEV(major_number, 0));
    class_destroy(char_class);
    unregister_chrdev(major_number, DEVICE_NAME);
    printk(KERN_INFO "mychar: device driver exited\n");
}

static int dev_open(struct inode *inodep, struct file *filep)
{
    printk(KERN_INFO "mychar: device opened\n");
    return 0;
}

static int dev_release(struct inode *inodep, struct file *filep)
{
    printk(KERN_INFO "mychar: device closed\n");
    return 0;
}

static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset)
{
    char message[256] = "Hello from kernel space!\n";
    int message_len = strlen(message);

    if (len > message_len) {
        len = message_len;
    }

    if (copy_to_user(buffer, message, len)) {
        return -EFAULT;
    }

    return len;
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ganavi");
MODULE_DESCRIPTION("A simple Linux char driver with interrupt handling");
MODULE_VERSION("0.1");

module_init(mychar_init);
module_exit(mychar_exit);
