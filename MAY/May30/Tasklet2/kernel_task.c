#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>
#include <linux/device.h>

// Define the tasklet handler function
void my_tasklet_handler(unsigned long data)
{
    printk(KERN_INFO "Tasklet handler called with data: %lu\n", data);
}

// Declare and initialize the tasklet
DECLARE_TASKLET(my_tasklet,0);

// Device file operations
static int my_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "Device opened\n");
    return 0;
}

static ssize_t my_write(struct file *file, const char __user *buffer, size_t len, loff_t *offset)
{
    printk(KERN_INFO "Device write called, scheduling tasklet\n");
    tasklet_schedule(&my_tasklet);
    return len;
}

// File operations structure
static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .write = my_write,
};

// Module initialization and cleanup functions
static int major;
static struct cdev my_cdev;
static struct class *my_class;

static int __init my_module_init(void)
{
    dev_t dev;
    int ret;

    printk(KERN_INFO "Loading tasklet module\n");

    // Allocate major number
    ret = alloc_chrdev_region(&dev, 0, 1, "my_tasklet_device");
    if (ret < 0) {
        printk(KERN_ERR "Failed to allocate major number\n");
        return ret;
    }
    major = MAJOR(dev);

    // Initialize cdev
    cdev_init(&my_cdev, &fops);
    my_cdev.owner = THIS_MODULE;

    // Add cdev
    ret = cdev_add(&my_cdev, dev, 1);
    if (ret < 0) {
        printk(KERN_ERR "Failed to add cdev\n");
        unregister_chrdev_region(dev, 1);
        return ret;
    }

    // Create class and device
    my_class = class_create("my_tasklet_class");
    if (IS_ERR(my_class)) {
        printk(KERN_ERR "Failed to create class\n");
        cdev_del(&my_cdev);
        unregister_chrdev_region(dev, 1);
        return PTR_ERR(my_class);
    }
    device_create(my_class, NULL, dev, NULL, "my_tasklet_device");

    return 0;
}

static void __exit my_module_exit(void)
{
    dev_t dev = MKDEV(major, 0);

    // Cleanup device
    device_destroy(my_class, dev);
    class_destroy(my_class);
    cdev_del(&my_cdev);
    unregister_chrdev_region(dev, 1);

    // Ensure the tasklet is killed before module exit
    tasklet_kill(&my_tasklet);
    printk(KERN_INFO "Unloading tasklet module\n");
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ganavi");
MODULE_DESCRIPTION("A simple tasklet example with device file");
