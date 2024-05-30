#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "calculator_dev"

static int major_number;
static char operation;
static int operand1;
static int operand2;
static int result;

static int calculator_dev_open(struct inode *inode, struct file *file) {
    return 0;
}

static int calculator_dev_release(struct inode *inode, struct file *file) {
    return 0;
}

static ssize_t calculator_dev_write(struct file *file, const char *buf, size_t count, loff_t *ppos) {
    sscanf(buf, "%c %d %d", &operation, &operand1, &operand2);
    switch (operation) {
        case '+':
            result = operand1 + operand2;
            break;
        case '-':
            result = operand1 - operand2;
            break;
        case '*':
            result = operand1 * operand2;
            break;
        case '/':
            if (operand2 != 0)
                result = operand1 / operand2;
            else
                result = -1; // Division by zero error
            break;
        default:
            return -EINVAL; // Invalid operation
    }
    return count;
}

static ssize_t calculator_dev_read(struct file *file, char *buf, size_t count, loff_t *ppos) {
    int len = 0;
    if (result >= 0) {
        len = snprintf(buf, count, "%d\n", result);
        result = -1; // Reset result
    }
    return len;
}

static struct file_operations calculator_dev_fops = {
    .open = calculator_dev_open,
    .release = calculator_dev_release,
    .write = calculator_dev_write,
    .read = calculator_dev_read,
};

static int __init calculator_dev_init(void) {
    major_number = register_chrdev(0, DEVICE_NAME, &calculator_dev_fops);
    if (major_number < 0) {
        printk(KERN_ALERT "Failed to register a major number\n");
        return major_number;
    }
    printk(KERN_INFO "Calculator device registered, major number: %d\n", major_number);
    return 0;
}

static void __exit calculator_dev_exit(void) {
    unregister_chrdev(major_number, DEVICE_NAME);
    printk(KERN_INFO "Calculator device unregistered\n");
}

module_init(calculator_dev_init);
module_exit(calculator_dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ganavi");
MODULE_DESCRIPTION("Simple calculator device driver");
