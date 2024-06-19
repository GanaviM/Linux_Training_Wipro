#include <linux/init.h>        // Header for module initialization and cleanup functions
#include <linux/module.h>      // Header for module macros and functions
#include <linux/fs.h>          // Header for file operations structure
#include <linux/cdev.h>        // Header for character device registration
#include <linux/uaccess.h>     // Header for user space access functions

// Define device major and minor numbers (adjust as needed)
#define LED_DEV_MAJOR 170
#define LED_DEV_MINOR 0

// Forward declarations of the file operations functions
static int led_open(struct inode *inode, struct file *filp);
static int led_release(struct inode *inode, struct file *filp);
static ssize_t led_write(struct file *filp, const char __user *user_buf, size_t count, loff_t *f_pos);

static dev_t led_dev;               // Device number
static struct cdev led_cdev;        // Character device structure
static struct file_operations led_fops = {
    .owner = THIS_MODULE,           // Owner of the module
    .open = led_open,               // Open function pointer
    .release = led_release,         // Release function pointer
    .write = led_write,             // Write function pointer
};

// Virtual LED state (replace with actual LED manipulation logic)
static spinlock_t led_lock;         // Spinlock for synchronization
static int led_state = 0;           // 0: off, 1: on

// Open function for the device
static int led_open(struct inode *inode, struct file *filp) {
    return 0; // Allow opening the device
}

// Release function for the device
static int led_release(struct inode *inode, struct file *filp) {
    return 0; // Clean up (no specific resources in this example)
}

// Write function for the device
static ssize_t led_write(struct file *filp, const char __user *user_buf, size_t count, loff_t *f_pos) {
    char value;

    if (count != sizeof(value)) {
        return -EINVAL; // Validate data size
    }

    // Copy data from user space to kernel space
    if (copy_from_user(&value, user_buf, count)) {
        return -EFAULT; // Handle copy_from_user error
    }

    // Acquire the spinlock before updating the LED state
    spin_lock(&led_lock);
    led_state = (value == '1') ? 1 : 0; // Update state (1: on, 0: off)
    spin_unlock(&led_lock); // Release the spinlock

    // Print the LED state to the kernel log
    printk(KERN_INFO "LED state: %d\n", led_state);
    return count; // Return the number of bytes written
}

// Module initialization function
static int __init led_driver_init(void) {
    int ret;

    // Allocate a device number
    ret = alloc_chrdev_region(&led_dev, LED_DEV_MINOR, 1, "led_dev");
    if (ret < 0) {
        return ret; // Return error if allocation fails
    }

    // Initialize character device structure
    cdev_init(&led_cdev, &led_fops);

    // Add character device to the kernel
    ret = cdev_add(&led_cdev, led_dev, 1);
    if (ret < 0) {
        goto free_dev; // Jump to cleanup if addition fails
    }

    spin_lock_init(&led_lock); // Initialize spinlock

    // Print initialization message to the kernel log
    printk(KERN_INFO "LED driver initialized\n");
    return 0;

free_dev:
    // Free the device number on failure
    unregister_chrdev_region(led_dev, 1);
    return ret; // Return error code
}

// Module exit function
static void __exit led_driver_exit(void) {
    cdev_del(&led_cdev); // Delete character device from the kernel
    unregister_chrdev_region(led_dev, 1); // Unregister the device number
    printk(KERN_INFO "LED driver exited\n"); // Print exit message to the kernel log
}

// Specify the initialization and exit functions
module_init(led_driver_init);
module_exit(led_driver_exit);

// Module metadata
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Virtual LED Driver");
