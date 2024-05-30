#include <linux/cdev.h> //Include character device header
#include <linux/init.h>  // Include the initialization header
#include <linux/module.h>  // Include the module header
#include <linux/kernel.h>  // Include the kernel header
#include <linux/fs.h>  // Include the file system header
#include <linux/ioctl.h>  // Include the ioctl header
#include <linux/uaccess.h>  // Include the user access header

#define DEVICE_NAME "reverse_ioctl_dev"  // Define the device name
#define REVERSE_STRING _IOR('q', 1, char *)  // Define an ioctl command for reversing a string

static struct cdev cdev; //Declare character device structure
static int major_num;  // Variable to store the major number obtained during device registration

// Function to handle ioctl commands
static long reverse_string_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    char *string;  // Pointer to store the user-provided string
    char tmp;  // Temporary variable for swapping characters
    int len, i;  // Variables to store string length and loop index

    switch (cmd) {  // Check the ioctl command
        case REVERSE_STRING:  // If the command is to reverse a string
            string = (char *)arg;  // Get the string from the user space
            len = strlen(string);  // Get the length of the string

            // Reverse the string
            for (i = 0; i < len / 2; ++i) {
                tmp = string[i];
                string[i] = string[len - i - 1];
                string[len - i - 1] = tmp;
            }
            break;

        default:  // If the command is not recognized
            return -EINVAL;  // Return an error
    }

    return 0;  // Return 0 to indicate success
}

// Define the file operations structure
static const struct file_operations reverse_fops = {
    .unlocked_ioctl = reverse_string_ioctl,  // Specify the ioctl handler function
};

// Initialization function
static int __init reverse_ioctl_init(void) {
    // Allocate a range of char device numbers
    if (alloc_chrdev_region(&major_num, 0, 1, DEVICE_NAME) < 0) {
        printk(KERN_ERR "Failed to allocate device numbers\n");
        return -EBUSY;  // Return an error if allocation fails
    }

    // Register the character device
    cdev_init(&cdev, &reverse_fops);  // Initialize the character device
    if (cdev_add(&cdev, major_num, 1) < 0) {  // Add the character device
        unregister_chrdev_region(major_num, 1);  // Unregister device numbers if adding fails
        printk(KERN_ERR "Failed to register device\n");  // Print error message
        return -EBUSY;  // Return an error
    }

    printk(KERN_INFO "Reverse IOCTL device registered\n");  // Print registration success message
    return 0;  // Return 0 to indicate success
}

// Exit function
static void __exit reverse_ioctl_exit(void) {
    // Unregister the character device
    cdev_del(&cdev);  // Delete the character device
    unregister_chrdev_region(major_num, 1);  // Unregister the device numbers
    printk(KERN_INFO "Reverse IOCTL device unregistered\n");  // Print unregistration message
}

module_init(reverse_ioctl_init);  // Specify the initialization function
module_exit(reverse_ioctl_exit);  // Specify the exit function

MODULE_LICENSE("GPL");  // Specify the module license
MODULE_AUTHOR("Ganavi");  // Specify the module author
MODULE_DESCRIPTION("Simple character driver for reversing strings using IOCTL");  // Specify the module description
