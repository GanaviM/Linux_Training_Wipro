#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "simchardev"
#define BUF_LEN 80

// IOCTL Commands
#define IOCTL_SET_MSG _IOW('a', 1, char *)
#define IOCTL_GET_MSG _IOR('a', 2, char *)

static int Major;
static char message[BUF_LEN];
static char *msg_ptr;

// Function Prototypes
static int dev_open(struct inode *, struct file *);
static int dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char __user *, size_t, loff_t *);
static long dev_ioctl(struct file *, unsigned int, unsigned long);

// File Operations Structure
struct file_operations fops = {
    .read = dev_read,
    .write = dev_write,
    .unlocked_ioctl = dev_ioctl,
    .open = dev_open,
    .release = dev_release
};

// Initialization Function
static int __init chardev_init(void) {
    Major = register_chrdev(0, DEVICE_NAME, &fops);
    if (Major < 0) {
        printk(KERN_ALERT "Registering char device failed with %d\n", Major);
        return Major;
    }
    printk(KERN_INFO "I was assigned major number %d. To talk to\n", Major);
    printk(KERN_INFO "the driver, create a dev file with\n");
    printk(KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, Major);
    return 0;
}

// Cleanup Function
static void __exit chardev_exit(void) {
    unregister_chrdev(Major, DEVICE_NAME);
    printk(KERN_INFO "Goodbye, world!\n");
}

// Open Function
static int dev_open(struct inode *inode, struct file *file) {
    static int counter = 0;
    sprintf(message, "I already told you %d times Hello world!\n", counter++);
    msg_ptr = message;
    try_module_get(THIS_MODULE);
    return 0;
}

// Release Function
static int dev_release(struct inode *inode, struct file *file) {
    module_put(THIS_MODULE);
    return 0;
}

// Read Function
static ssize_t dev_read(struct file *filp, char __user *buffer, size_t length, loff_t * offset) {
    int bytes_read = 0;
    if (*msg_ptr == 0)
        return 0;
    while (length && *msg_ptr) {
        put_user(*(msg_ptr++), buffer++);
        length--;
        bytes_read++;
    }
    return bytes_read;
}

// Write Function
static ssize_t dev_write(struct file *filp, const char __user *buff, size_t len, loff_t * off) {
    printk(KERN_ALERT "Sorry, this operation isn't supported.\n");
    return -EINVAL;
}

// Ioctl Function
static long dev_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    switch (cmd) {
        case IOCTL_SET_MSG:
            if (copy_from_user(message, (char __user *)arg, BUF_LEN))
                return -EFAULT;
            msg_ptr = message;
            break;
        case IOCTL_GET_MSG:
            if (copy_to_user((char __user *)arg, message, BUF_LEN))
                return -EFAULT;
            break;
        default:
            return -ENOTTY;
    }
    return 0;
}

// Register Module Initialization and Cleanup Functions
module_init(chardev_init);
module_exit(chardev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A Simple Character Device Driver");
