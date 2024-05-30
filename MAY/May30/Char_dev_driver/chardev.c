#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>

#define DEVICE_NAME "simple_char_device"
#define BUFFER_SIZE 1024

static int major_number;
static char device_buffer[BUFFER_SIZE];
static struct cdev my_cdev;
static int device_open_count = 0;

static int device_open(struct inode *inode, struct file *file) {
    device_open_count++;
    printk(KERN_INFO "simple_char_device: Device opened %d time(s)\n", device_open_count);
    return 0;
}

static int device_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "simple_char_device: Device closed\n");
    return 0;
}

static ssize_t device_read(struct file *file, char __user *buffer, size_t len, loff_t *offset) {
    ssize_t bytes_read = len > BUFFER_SIZE - *offset ? BUFFER_SIZE - *offset : len;
    if (bytes_read == 0) {
        printk(KERN_INFO "simple_char_device: Nothing to read\n");
        return 0;
    }
    if (copy_to_user(buffer, device_buffer + *offset, bytes_read)) {
        return -EFAULT;
    }
    *offset += bytes_read;
    printk(KERN_INFO "simple_char_device: Read %ld bytes\n", bytes_read);
    return bytes_read;
}

static ssize_t device_write(struct file *file, const char __user *buffer, size_t len, loff_t *offset) {
    ssize_t bytes_to_write = len > BUFFER_SIZE - *offset ? BUFFER_SIZE - *offset : len;
    if (bytes_to_write == 0) {
        printk(KERN_INFO "simple_char_device: No space left to write\n");
        return -ENOMEM;
    }
    if (copy_from_user(device_buffer + *offset, buffer, bytes_to_write)) {
        return -EFAULT;
    }
    *offset += bytes_to_write;
    printk(KERN_INFO "simple_char_device: Wrote %ld bytes\n", bytes_to_write);
    return bytes_to_write;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = device_open,
    .release = device_release,
    .read = device_read,
    .write = device_write,
};

static int __init simple_char_device_init(void) {
    dev_t dev;
    int ret;

    // Allocate a major number dynamically
    ret = alloc_chrdev_region(&dev, 0, 1, DEVICE_NAME);
    if (ret < 0) {
        printk(KERN_ALERT "simple_char_device: Failed to allocate a major number\n");
        return ret;
    }
    major_number = MAJOR(dev);
    printk(KERN_INFO "simple_char_device: Registered with major number %d\n", major_number);

    // Initialize the character device
    cdev_init(&my_cdev, &fops);
    my_cdev.owner = THIS_MODULE;

    // Add the character device to the system
    ret = cdev_add(&my_cdev, dev, 1);
    if (ret < 0) {
        unregister_chrdev_region(dev, 1);
        printk(KERN_ALERT "simple_char_device: Failed to add the character device\n");
        return ret;
    }

    printk(KERN_INFO "simple_char_device: Device initialized\n");
    return 0;
}

static void __exit simple_char_device_exit(void) {
    dev_t dev = MKDEV(major_number, 0);

    // Remove the character device from the system
    cdev_del(&my_cdev);

    // Unregister the major number
    unregister_chrdev_region(dev, 1);

    printk(KERN_INFO "simple_char_device: Device unregistered\n");
}

module_init(simple_char_device_init);
module_exit(simple_char_device_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple character device driver");
