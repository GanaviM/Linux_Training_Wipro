#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/random.h>

#define DEVICE_NAME "randomdev"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ganavi");
MODULE_DESCRIPTION("A simple random number device driver");

static int Major;

static int device_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "Device opened\n");
    return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "Device closed\n");
    return 0;
}

static ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t *offset)
{
    int bytes_read;
    get_random_bytes(&bytes_read, sizeof(int));
    bytes_read %= 1000; // Limit to 0-999 for simplicity

    if (copy_to_user(buffer, &bytes_read, sizeof(int)) != 0) {
        return -EFAULT; // Error while copying data to user space
    }

    return sizeof(int);
}

static struct file_operations fops = {
    .read = device_read,
    .open = device_open,
    .release = device_release,
};

static int __init randomdev_init(void)
{
    Major = register_chrdev(0, DEVICE_NAME, &fops);
    if (Major < 0) {
        printk(KERN_ALERT "Registering char device failed with %d\n", Major);
        return Major;
    }
    printk(KERN_INFO "Registered char device with major number %d\n", Major);
    return 0;
}

static void __exit randomdev_exit(void)
{
    unregister_chrdev(Major, DEVICE_NAME);
    printk(KERN_INFO "Unregistered char device\n");
}

module_init(randomdev_init);
module_exit(randomdev_exit);
