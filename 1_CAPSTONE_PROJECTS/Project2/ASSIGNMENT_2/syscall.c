#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/module.h>

// Module metadata
MODULE_AUTHOR("Your Name");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A simple module to add a custom system call for logging messages to the kernel log");
MODULE_VERSION("1.0");

// System call to log a message from user space to the kernel log
SYSCALL_DEFINE1(log_message, const char __user *, message)
{
    char buf[256];  // Buffer to hold the message from user space

    // Copy the message from user space to kernel space
    if (copy_from_user(buf, message, sizeof(buf))) {
        return -EFAULT;  // Return error if copy fails
    }

    buf[sizeof(buf) - 1] = '\0';  // Ensure the buffer is null-terminated

    // Log the message to the kernel log
    printk(KERN_INFO "User Message: %s\n", buf);
    
    return 0;  // Return success
}

// Module initialization function
static int __init log_message_init(void)
{
    printk(KERN_INFO "Custom log_message system call module loaded\n");
    return 0;
}

// Module exit function
static void __exit log_message_exit(void)
{
    printk(KERN_INFO "Custom log_message system call module unloaded\n");
}

module_init(log_message_init);
module_exit(log_message_exit);
