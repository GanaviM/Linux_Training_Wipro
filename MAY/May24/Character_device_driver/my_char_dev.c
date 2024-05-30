#include <linux/module.h>    // Needed by all modules
#include <linux/fs.h>        // Needed for the file operations structure
#include <linux/uaccess.h>   // Needed for copy_to_user and copy_from_user
#include <linux/cdev.h>      // Needed for character device structures
#include <linux/slab.h>      // Needed for kmalloc and kfree

#define DEVICE_NAME "mychardev" // Name of our device
#define BUFFER_SIZE 1024        // Size of the buffer to store data

static int major_number;        // Major number for our device
static char *device_buffer;     // Buffer to store data written to the device
static struct cdev my_cdev;     // Character device structure

// This function is called when the device is opened
static int my_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "mychardev: Device opened\n");
    return 0; // Always succeed
}

// This function is called when the device is closed
static int my_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "mychardev: Device closed\n");
    return 0; // Always succeed
}

// This function is called when data is read from the device
static ssize_t my_read(struct file *file, char __user *buf, size_t len, loff_t *offset) {
    size_t to_read;

    if (*offset >= BUFFER_SIZE) // Check if offset is beyond the buffer
        return 0; // Nothing more to read

    to_read = min(len, (size_t)(BUFFER_SIZE - *offset)); // Calculate how much to read

    if (copy_to_user(buf, device_buffer + *offset, to_read)) // Copy data to user space
        return -EFAULT; // Failed to copy data

    *offset += to_read; // Update offset
    return to_read; // Return number of bytes read
}

// This function is called when data is written to the device
static ssize_t my_write(struct file *file, const char __user *buf, size_t len, loff_t *offset) {
    size_t to_write;

    if (*offset >= BUFFER_SIZE) // Check if offset is beyond the buffer
        return -ENOSPC; // No space left to write data

    to_write = min(len, (size_t)(BUFFER_SIZE - *offset)); // Calculate how much to write

    if (copy_from_user(device_buffer + *offset, buf, to_write)) // Copy data from user space
        return -EFAULT; // Failed to copy data

    *offset += to_write; // Update offset
    return to_write; // Return number of bytes written
}

// File operations structure, tells the kernel which functions to call for various operations
static struct file_operations fops = {
    .owner = THIS_MODULE,  // Owner of the module
    .open = my_open,       // Open function
    .release = my_release, // Release function
    .read = my_read,       // Read function
    .write = my_write,     // Write function
};

// This function is called when the module is loaded
static int __init my_init(void) {
    dev_t dev;
    int ret;

    // Allocate a major number dynamically
    ret = alloc_chrdev_region(&dev, 0, 1, DEVICE_NAME);
    if (ret < 0) {
        printk(KERN_ERR "mychardev: Failed to allocate major number\n");
        return ret;
    }

    major_number = MAJOR(dev); // Extract major number
    printk(KERN_INFO "mychardev: Registered with major number %d\n", major_number);

    // Allocate memory for the buffer
    device_buffer = kmalloc(BUFFER_SIZE, GFP_KERNEL);
    if (!device_buffer) {
        unregister_chrdev_region(dev, 1); // Clean up if allocation fails
        return -ENOMEM; // No memory error
    }

    // Initialize the character device
    cdev_init(&my_cdev, &fops);
    my_cdev.owner = THIS_MODULE;

    // Add the character device to the system
    ret = cdev_add(&my_cdev, dev, 1);
    if (ret < 0) {
        kfree(device_buffer); // Clean up if addition fails
        unregister_chrdev_region(dev, 1);
        return ret;
    }

    printk(KERN_INFO "char_dev: Device initialized\n");
    return 0;
}

// This function is called when the module is unloaded
static void __exit my_exit(void) {
    dev_t dev = MKDEV(major_number, 0); // Create device number

    cdev_del(&my_cdev); // Remove the character device
    kfree(device_buffer); // Free the allocated buffer
    unregister_chrdev_region(dev, 1); // Unregister the device number

    printk(KERN_INFO "char_dev: Device unregistered\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ganavi");
MODULE_DESCRIPTION("A simple character device driver");
MODULE_VERSION("1.0");
