#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>
#include <linux/slab.h>

#define DEVICE_NAME "calc_device"
#define IOCTL_MAGIC 'c'
#define IOCTL_CALC _IOWR(IOCTL_MAGIC, 1, calc_data_t)

typedef struct {
    int num1;
    int num2;
    char operation[8];
    int result;
    int error; // 0 = no error, 1 = division by zero
} calc_data_t;

static int device_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Calculator device opened\n");
    return 0;
}

static int device_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Calculator device closed\n");
    return 0;
}

static long device_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    calc_data_t data;

    if (copy_from_user(&data, (calc_data_t __user *)arg, sizeof(calc_data_t))) {
        return -EFAULT;
    }

    data.error = 0;

    if (strcmp(data.operation, "+") == 0) {
        data.result = data.num1 + data.num2;
    } else if (strcmp(data.operation, "-") == 0) {
        data.result = data.num1 - data.num2;
    } else if (strcmp(data.operation, "*") == 0) {
        data.result = data.num1 * data.num2;
    } else if (strcmp(data.operation, "/") == 0) {
        if (data.num2 == 0) {
            data.error = 1;
            data.result = 0;
        } else {
            data.result = data.num1 / data.num2;
        }
    } else {
        return -EINVAL;
    }

    if (copy_to_user((calc_data_t __user *)arg, &data, sizeof(calc_data_t))) {
        return -EFAULT;
    }

    return 0;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = device_open,
    .release = device_release,
    .unlocked_ioctl = device_ioctl,
};

static int major_number;
static struct cdev my_cdev;

static int __init calc_init(void) {
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        printk(KERN_ALERT "Registering char device failed with %d\n", major_number);
        return major_number;
    }

    cdev_init(&my_cdev, &fops);
    my_cdev.owner = THIS_MODULE;
    if (cdev_add(&my_cdev, MKDEV(major_number, 0), 1)) {
        unregister_chrdev(major_number, DEVICE_NAME);
        printk(KERN_ALERT "Adding cdev failed\n");
        return -1;
    }

    printk(KERN_INFO "Calculator device registered with major number %d\n", major_number);
    return 0;
}

static void __exit calc_exit(void) {
    cdev_del(&my_cdev);
    unregister_chrdev(major_number, DEVICE_NAME);
    printk(KERN_INFO "Calculator device unregistered\n");
}

module_init(calc_init);
module_exit(calc_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("GANAVI");
MODULE_DESCRIPTION("A simple Linux char driver for a calculator with ioctl");
MODULE_VERSION("0.1");
