#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "reverse_string"
#define MAX_LENGTH 100

static int major_number;
static char input_string[MAX_LENGTH];
static char reversed_string[MAX_LENGTH];

static int reverse_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device opened\n");
    return 0;
}

static int reverse_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device closed\n");
    return 0;
}

static ssize_t reverse_write(struct file *file, const char *buffer, size_t length, loff_t *offset) {
    if (length > MAX_LENGTH) {
        printk(KERN_ALERT "Input string is too long\n");
        return -EINVAL;
    }

    if (copy_from_user(input_string, buffer, length)) {
        return -EFAULT;
    }
    input_string[length] = '\0'; // Null-terminate the input string

    // Reverse the input string
    int i, j;
    for (i = 0, j = length - 1; i < length; ++i, --j) {
        reversed_string[i] = input_string[j];
    }
    reversed_string[i] = '\0'; // Null-terminate the reversed string

    printk(KERN_INFO "Input string: %s\n", input_string);
    printk(KERN_INFO "Reversed string: %s\n", reversed_string);

    return length;
}

static ssize_t reverse_read(struct file *file, char *buffer, size_t length, loff_t *offset) {
    int bytes_to_copy = strlen(reversed_string);
    if (bytes_to_copy > length) {
        bytes_to_copy = length;
    }

    if (copy_to_user(buffer, reversed_string, bytes_to_copy)) {
        return -EFAULT;
    }

    return bytes_to_copy;
}

static struct file_operations fops = {
    .open = reverse_open,
    .release = reverse_release,
    .write = reverse_write,
    .read = reverse_read,
};

static int __init reverse_init(void) {
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        printk(KERN_ALERT "Failed to register a major number\n");
        return major_number;
    }
    printk(KERN_INFO "Reverse string device registered, major number: %d\n", major_number);
    return 0;
}

static void __exit reverse_exit(void) {
    unregister_chrdev(major_number, DEVICE_NAME);
    printk(KERN_INFO "Reverse string device unregistered\n");
}

module_init(reverse_init);
module_exit(reverse_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ganavi");
MODULE_DESCRIPTION("Kernel module for reversing a string");
