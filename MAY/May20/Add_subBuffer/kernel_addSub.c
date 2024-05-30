#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/poll.h>
#include <linux/wait.h>

#define DEVICE_NAME "ADD_SUB_device"

static int major_number;
static int num1, num2, result;
static char operation;
static wait_queue_head_t wq;
static int flag = 0;

static ssize_t device_read(struct file *file, char *buffer, size_t len, loff_t *offset) {
    wait_event_interruptible(wq, flag != 0);
    if (operation == '+') {
        result = num1 + num2;
    } else if (operation == '-') {
        result = num1 - num2;
    }
    flag = 0;
    if (copy_to_user(buffer, &result, sizeof(result))) {
        return -EFAULT;
    }
    return sizeof(result);
}

static ssize_t device_write(struct file *file, const char *buffer, size_t len, loff_t *offset) {
    if (len < sizeof(num1) + sizeof(num2) + sizeof(operation)) {
        return -EINVAL;
    }
    if (copy_from_user(&num1, buffer, sizeof(num1)) ||
        copy_from_user(&num2, buffer + sizeof(num1), sizeof(num2)) ||
        copy_from_user(&operation, buffer + sizeof(num1) + sizeof(num2), sizeof(operation))) {
        return -EFAULT;
    }
    flag = 1;
    wake_up_interruptible(&wq);
    return len;
}

static struct file_operations fops = {
    .read = device_read,
    .write = device_write,
};

static int __init calc_init(void) {
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        printk(KERN_ALERT "Failed to register device\n");
        return major_number;
    }
    init_waitqueue_head(&wq);
    printk(KERN_INFO "Calc module loaded with device major number %d\n", major_number);
    return 0;
}

static void __exit calc_exit(void) {
    unregister_chrdev(major_number, DEVICE_NAME);
    printk(KERN_INFO "Calc module unloaded\n");
}

module_init(calc_init);
module_exit(calc_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple calculation module");
MODULE_AUTHOR("Ganavi");
