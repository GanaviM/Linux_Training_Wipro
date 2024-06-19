#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "benchmarkdevice"
#define BUF_LEN 80

static int Major;
static char message[BUF_LEN];
static char *msg_ptr;

// File operation prototypes
static int dev_open(struct inode *, struct file *);
static int dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char __user *, size_t, loff_t *);

// File operations structure
struct file_operations fops = {
    .read = dev_read,
    .write = dev_write,
    .open = dev_open,
    .release = dev_release
};

// Initialization function
static int __init benchmarkdev_init(void) {
    Major = register_chrdev(0, DEVICE_NAME, &fops);
    if (Major < 0) {
        printk(KERN_ALERT "Registering char device failed with %d\n", Major);
        return Major;
    }
    printk(KERN_INFO "Benchmark device registered with major number %d\n", Major);
    return 0;
}

// Cleanup function
static void __exit benchmarkdev_exit(void) {
    unregister_chrdev(Major, DEVICE_NAME);
    printk(KERN_INFO "Benchmark device unregistered\n");
}

// Open function
static int dev_open(struct inode *inode, struct file *file) {
    static int counter = 0;
    sprintf(message, "Benchmark device opened %d times\n", counter++);
    msg_ptr = message;
    try_module_get(THIS_MODULE);
    return 0;
}

// Release function
static int dev_release(struct inode *inode, struct file *file) {
    module_put(THIS_MODULE);
    return 0;
}

// Read function
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

// Write function
static ssize_t dev_write(struct file *filp, const char __user *buff, size_t len, loff_t * off) {
    if (len > BUF_LEN - 1) {
        len = BUF_LEN - 1;
    }
    if (copy_from_user(message, buff, len)) {
        return -EFAULT;
    }
    message[len] = '\0';
    msg_ptr = message;
    return len;
}

module_init(benchmarkdev_init);
module_exit(benchmarkdev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Benchmark Device Driver");
