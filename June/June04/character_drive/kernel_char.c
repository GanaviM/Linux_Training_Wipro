#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "simple_char_dev"

static int major;
static char stored_char = 0;
static int device_open_count = 0;

static int device_open(struct inode *inode, struct file *file) {
    if (device_open_count > 0)
        return -EBUSY;

    device_open_count++;
    try_module_get(THIS_MODULE);
    return 0;
}

static int device_release(struct inode *inode, struct file *file) {
    device_open_count--;
    module_put(THIS_MODULE);
    return 0;
}

static ssize_t device_read(struct file *file, char __user *user_buffer, size_t count, loff_t *offset) {
    if (*offset > 0)
        return 0;

    if (copy_to_user(user_buffer, &stored_char, 1))
        return -EFAULT;

    (*offset)++;
    return 1;
}

static ssize_t device_write(struct file *file, const char __user *user_buffer, size_t count, loff_t *offset) {
    if (copy_from_user(&stored_char, user_buffer, 1))
        return -EFAULT;

    return 1;
}

static struct file_operations fops = {
    .open = device_open,
    .release = device_release,
    .read = device_read,
    .write = device_write,
};

static int __init simple_char_init(void) {
    major = register_chrdev(0, DEVICE_NAME, &fops);
    if (major < 0) {
        printk(KERN_ALERT "Registering char device failed with %d\n", major);
        return major;
    }

    printk(KERN_INFO "Registered char device with major number %d\n", major);
    return 0;
}

static void __exit simple_char_exit(void) {
    unregister_chrdev(major, DEVICE_NAME);
    printk(KERN_INFO "Unregistered char device\n");
}

module_init(simple_char_init);
module_exit(simple_char_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple character device driver without buffer");
