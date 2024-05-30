#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

#define DEVICE_NAME "add_buffer"
#define DEVICE_MEMORY_SIZE 4096  // 4KB

static char *device_memory;
static int major_number;

static int my_device_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "my_device: open\n");
    return 0;
}

static int my_device_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "my_device: release\n");
    return 0;
}

static ssize_t my_device_read(struct file *file, char __user *buffer, size_t length, loff_t *offset) {
    if (copy_to_user(buffer, device_memory, length)) {
        return -EFAULT;
    }
    return length;
}

static ssize_t my_device_write(struct file *file, const char __user *buffer, size_t length, loff_t *offset) {
    int num1, num2, sum;
    char *temp_buffer;

    temp_buffer = kmalloc(length, GFP_KERNEL);
    if (!temp_buffer) {
        return -ENOMEM;
    }

    if (copy_from_user(temp_buffer, buffer, length)) {
        kfree(temp_buffer);
        return -EFAULT;
    }

    sscanf(temp_buffer, "%d %d", &num1, &num2);
    sum = num1 + num2;
    sprintf(device_memory, "%d", sum);

    kfree(temp_buffer);
    return length;
}

static const struct file_operations my_device_fops = {
    .owner = THIS_MODULE,
    .open = my_device_open,
    .release = my_device_release,
    .read = my_device_read,
    .write = my_device_write,
};

static int __init my_device_init(void) {
    major_number = register_chrdev(0, DEVICE_NAME, &my_device_fops);
    if (major_number < 0) {
        printk(KERN_ALERT "Registering char device failed with %d\n", major_number);
        return major_number;
    }

    device_memory = kmalloc(DEVICE_MEMORY_SIZE, GFP_KERNEL);
    if (!device_memory) {
        unregister_chrdev(major_number, DEVICE_NAME);
        return -ENOMEM;
    }

    printk(KERN_INFO "my_device: registered with major number %d\n", major_number);
    printk(KERN_INFO "my_device: memory allocated at %p\n", device_memory);
    return 0;
}

static void __exit my_device_exit(void) {
    kfree(device_memory);
    unregister_chrdev(major_number, DEVICE_NAME);
    printk(KERN_INFO "my_device: unregistered\n");
}

module_init(my_device_init);
module_exit(my_device_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Example Device Driver without mmap for Adding Two Numbers");
