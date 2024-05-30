#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/mutex.h>

#define DEVICE_NAME "block_ioctl_device"
#define IOCTL_MAGIC 'k'
#define IOCTL_CMD _IOW(IOCTL_MAGIC, 1, int)

static int major_number;
static struct cdev my_cdev;
static wait_queue_head_t my_queue;
static int flag = 0;
static DEFINE_MUTEX(my_mutex);

static int device_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device opened\n");
    return 0;
}

static int device_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device closed\n");
    return 0;
}

static ssize_t device_read(struct file *file, char __user *buffer, size_t len, loff_t *offset) {
    int ret;

    wait_event_interruptible(my_queue, flag != 0);
    
    mutex_lock(&my_mutex);
    flag = 0;  // Reset the flag
    mutex_unlock(&my_mutex);

    ret = copy_to_user(buffer, &flag, sizeof(flag));
    if (ret) {
        return -EFAULT;
    }

    printk(KERN_INFO "Data read from device\n");
    return sizeof(flag);
}

static ssize_t device_write(struct file *file, const char __user *buffer, size_t len, loff_t *offset) {
    int value;
    int ret = copy_from_user(&value, buffer, sizeof(value));
    if (ret) {
        return -EFAULT;
    }

    mutex_lock(&my_mutex);
    flag = value;
    mutex_unlock(&my_mutex);

    wake_up_interruptible(&my_queue);

    printk(KERN_INFO "Data written to device\n");
    return sizeof(value);
}

static long device_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    int value;

    switch (cmd) {
        case IOCTL_CMD:
            if (copy_from_user(&value, (int __user *)arg, sizeof(value))) {
                return -EFAULT;
            }
            printk(KERN_INFO "IOCTL received: %d\n", value);
            break;
        default:
            return -ENOTTY;
    }
    return 0;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = device_open,
    .release = device_release,
    .read = device_read,
    .write = device_write,
    .unlocked_ioctl = device_ioctl,
};

static int __init my_ioctl_init(void) {
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

    init_waitqueue_head(&my_queue);

    printk(KERN_INFO "Device registered with major number %d\n", major_number);
    return 0;
}

static void __exit my_ioctl_exit(void) {
    cdev_del(&my_cdev);
    unregister_chrdev(major_number, DEVICE_NAME);
    printk(KERN_INFO "Device unregistered\n");
}

module_init(my_ioctl_init);
module_exit(my_ioctl_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("GANAVI");
MODULE_DESCRIPTION("A simple Linux char driver with ioctl and blocking I/O");
MODULE_VERSION("0.1");
