#include <linux/init.h>         // Initialization and cleanup macros
#include <linux/module.h>       // Module-related macros and functions
#include <linux/kernel.h>       // Kernel-related functions and macros
#include <linux/fs.h>           // File system-related functions and structures
#include <linux/uaccess.h>      // User space access functions
#include <linux/cdev.h>         // Character device-related functions and structures
#include <linux/string.h>       // String manipulation functions

#define DEVICE_NAME "mychardev"    // Name of the character device

static dev_t dev_number;           // Device number
static struct cdev mychardev_cdev; // Character device structure

// Function prototypes
static int mychardev_open(struct inode *inode, struct file *file);
static int mychardev_release(struct inode *inode, struct file *file);
static ssize_t mychardev_read(struct file *file, char __user *user_buffer, size_t count, loff_t *offset);
static ssize_t mychardev_write(struct file *file, const char __user *user_buffer, size_t count, loff_t *offset);

// File operations structure
static struct file_operations mychardev_fops = {
    .owner = THIS_MODULE,           // Owner of the file operations (this module)
    .open = mychardev_open,        // Pointer to the open function
    .release = mychardev_release,  // Pointer to the release function
    .read = mychardev_read,        // Pointer to the read function
    .write = mychardev_write,      // Pointer to the write function
};

// Open function
static int mychardev_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "MYCHARDEV: Device opened\n");  // Log message indicating device open
    return 0;                                        // Return success
}

// Release function
static int mychardev_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "MYCHARDEV: Device closed\n");  // Log message indicating device close
    return 0;                                        // Return success
}

// Read function
static ssize_t mychardev_read(struct file *file, char __user *user_buffer, size_t count, loff_t *offset) {
    char message[] = "Hello from the kernel!\n";     // Message to be read
    size_t to_copy = strlen(message);                // Length of the message

    if (count > to_copy) {
        count = to_copy;                              // Adjust count if it's greater than message length
    }

    if (copy_to_user(user_buffer, message, count)) {
        return -EFAULT;           //Error copying data to user space
    }

    return count;                    // Return number of bytes read
}

// Write function
static ssize_t mychardev_write(struct file *file, const char __user *user_buffer, size_t count, loff_t *offset) {
    printk(KERN_INFO "MYCHARDEV: Writing not supported\n");  // Log message indicating writing is not supported
    return -EOPNOTSUPP;                                      // Return operation not supported error
}

// Initialization function
static int __init mychardev_init(void) {
    int ret;

    // Allocate device number
    ret = alloc_chrdev_region(&dev_number, 0, 1, DEVICE_NAME);
    if (ret < 0) {
        return ret;             // Return error if allocation fails
    }

    // Initialize character device structure
    cdev_init(&mychardev_cdev, &mychardev_fops);

    // Add character device to the system
    ret = cdev_add(&mychardev_cdev, dev_number, 1);
    if (ret < 0) {
        goto free_dev_num;      // Return error if addition fails
    }

    printk(KERN_INFO "MYCHARDEV: Successfully registered character device\n");  // Log message indicating success
    return 0;                    // Return success

free_dev_num:
    unregister_chrdev_region(dev_number, 1);   // Free device number if addition fails
    return ret;                     // Return error
}

// Cleanup function
static void __exit mychardev_exit(void) {
    cdev_del(&mychardev_cdev);                // Delete character device
    unregister_chrdev_region(dev_number, 1);  // Unregister device number
    printk(KERN_INFO "MYCHARDEV: Module unloaded\n");  // Log message indicating module unloaded
}

module_init(mychardev_init);    // Specify initialization function
module_exit(mychardev_exit);    // Specify cleanup function

MODULE_LICENSE("GPL");          // Specify module license
MODULE_AUTHOR("Your Name");     // Specify module author
MODULE_DESCRIPTION("A simple character device driver");  // Specify module description
