#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/ioctl.h>

#define DEVICE_NAME "simple_char_driver"
#define IOCTL_SET_MSG _IOW('q', 1, char *)

static char msg[100] = "Default message from the driver\n";
static int msg_len = 30;
static int major;

static int device_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device opened\n");
    return 0;
}

static int device_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device closed\n");
    return 0;
}

static ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t *offset) {
    int bytes_read = 0;
    if (*offset >= msg_len)
        return 0;
    while (length && msg_len) {
        put_user(msg[(*offset)++], buffer++);
        length--;
        bytes_read++;
    }
    return bytes_read;
}

static ssize_t device_write(struct file *filp, const char *buffer, size_t length, loff_t *offset) {
    int bytes_written = 0;
    if (*offset >= 100)
        return -ENOSPC;
    while (length && (*offset < 100)) {
        get_user(msg[(*offset)++], buffer++);
        length--;
        bytes_written++;
    }
    msg_len = *offset;
    return bytes_written;
}

static long device_ioctl(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param) {
    char *temp;
    switch (ioctl_num) {
        case IOCTL_SET_MSG:
            temp = (char *)ioctl_param;
            copy_from_user(msg, temp, 100);
            msg_len = strlen(msg);
	    printk(KERN_INFO "New messages set: %s\n",msg);
            break;
        default:
            return -EINVAL;
    }
    return 0;
}

static struct file_operations fops = {
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release,
    .unlocked_ioctl = device_ioctl,
};

static int __init char_driver_init(void) {
    major = register_chrdev(0, DEVICE_NAME, &fops);
    if (major < 0) {
        printk(KERN_ALERT "Failed to register a major number\n");
        return major;
    }
    printk(KERN_INFO "Registered correctly with major number %d\n", major);
    return 0;
}

static void __exit char_driver_exit(void) {
    unregister_chrdev(major, DEVICE_NAME);
    printk(KERN_INFO "Unregistered the device\n");
}

module_init(char_driver_init);
module_exit(char_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ganavi");
MODULE_DESCRIPTION("A simple character device driver");
MODULE_VERSION("1.0");
