#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/spinlock.h> // Include for spinlock

// Define device major and minor numbers (adjust as needed)
#define LED_DEV_MAJOR 170
#define LED_DEV_MINOR 0

static dev_t led_dev;
static struct cdev led_cdev;

// Function declarations
static int led_open(struct inode *inode, struct file *filp);
static int led_release(struct inode *inode, struct file *filp);
static ssize_t led_write(struct file *filp, const char __user *user_buf, size_t count, loff_t *f_pos);

static struct file_operations led_fops = {
    .owner = THIS_MODULE,
    .open = led_open,
    .release = led_release,
    .write = led_write,
};

// Virtual LED state (replace with actual LED manipulation logic)
static spinlock_t led_lock; // Spinlock for synchronization
static int led_state = 0; // 0: off, 1: on

static int led_open(struct inode *inode, struct file *filp) {
    return 0; // Allow opening the device
}

static int led_release(struct inode *inode, struct file *filp) {
    return 0; // Clean up (no specific resources in this example)
}

static ssize_t led_write(struct file *filp, const char __user *user_buf,
                         size_t count, loff_t *f_pos) {
    char value;

    if (count != sizeof(value)) {
        return -EINVAL; // Validate data size
    }

    if (copy_from_user(&value, user_buf, count)) {
        return -EFAULT; // Handle copy_from_user error
    }

    spin_lock(&led_lock);
    led_state = (value == '1') ? 1 : 0; // Update state (1: on, 0: off)
    spin_unlock(&led_lock);

    printk(KERN_INFO "LED state: %d\n", led_state);
    return count;
}

static int __init led_driver_init(void) {
    int ret;

    // Allocate a device number
    ret = alloc_chrdev_region(&led_dev, LED_DEV_MINOR, 1, "led_dev");
    if (ret < 0) {
        return ret;
    }

    // Initialize character device structure
    cdev_init(&led_cdev, &led_fops);

    // Add character device to the kernel
    ret = cdev_add(&led_cdev, led_dev, 1);
    if (ret < 0) {
        goto free_dev;
    }

    spin_lock_init(&led_lock); // Initialize spinlock

    printk(KERN_INFO "LED driver initialized\n");
    return 0;

free_dev:
    unregister_chrdev_region(led_dev, 1);
    return ret;
}

static void __exit led_driver_exit(void) {
    cdev_del(&led_cdev);
    unregister_chrdev_region(led_dev, 1);
    printk(KERN_INFO "LED driver exited\n");
}

module_init(led_driver_init);
module_exit(led_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Virtual LED Driver");
