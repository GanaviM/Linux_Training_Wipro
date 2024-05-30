#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/ioctl.h>

#define DEVICE_NAME "IOCTL_string_reverse"
#define IOCTL_REVERSE_STRING _IOWR('q', 2, char *)

static int major;

static void reverse_string(char *str) {
    int len = strlen(str);
    int i;
    char temp;
    for (i = 0; i < len / 2; i++) {
        temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

static long device_ioctl(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param) {
    char *str;
    switch (ioctl_num) {
        case IOCTL_REVERSE_STRING:
            str = (char *)ioctl_param;
            reverse_string(str);
            break;
        default:
            return -EINVAL;
    }
    return 0;
}

static struct file_operations fops = {
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
