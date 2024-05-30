#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "reverse_dev"

static dev_t dev_number;
static struct cdev cdev;

static char message[100] = {0}; // Stores the received string
static int message_len = 0;     // Keeps track of string length

// Function to reverse a string
static void reverse_string(char *str, int len) {
  int start = 0;
  int end = len - 1;
  while (start < end) {
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    start++;
    end--;
  }
}

// Open operation
static int reverse_dev_open(struct inode *inode, struct file *filp) {
  printk(KERN_INFO "Device opened\n");
  message_len = 0; // Reset message for new data
  return 0;
}

// Write operation
static ssize_t reverse_dev_write(struct file *filp, const char __user *user_buf,
                                size_t count, loff_t *f_pos) {
    if (count >= sizeof(message)) {
        printk(KERN_WARNING "String too long\n");
        return -EINVAL;
    }

    if (copy_from_user(message, user_buf, count)) {
        return -EFAULT;
    }

    message[count] = '\0'; // Null-terminate the string

    message_len = strlen(message);
    
    reverse_string(message, message_len);

    printk(KERN_INFO "Received string(before reverse): %s\n", message);
    printk(KERN_INFO "Reversed string: %s\n", message);
    printk(KERN_INFO "Received string length: %d\n", message_len);

    return count;
}

// Close operation
static int reverse_dev_release(struct inode *inode, struct file *filp) {
  printk(KERN_INFO "Device closed\n");
  return 0;
}

static const struct file_operations reverse_dev_fops = {
  .owner = THIS_MODULE,
  .open = reverse_dev_open,
  .write = reverse_dev_write,
  .release = reverse_dev_release,
};

static int __init reverse_dev_init(void) {
  int ret;
  ret = alloc_chrdev_region(&dev_number, 0, 1, DEVICE_NAME);
  if (ret < 0) {
    return ret;
  }

  cdev_init(&cdev, &reverse_dev_fops);
  ret = cdev_add(&cdev, dev_number, 1);
  if (ret < 0) {
    goto free_dev_num;
  }

  printk(KERN_INFO "Reverse device registered\n");
  return 0;

free_dev_num:
  unregister_chrdev_region(dev_number, 1);
  return ret;
}

static void __exit reverse_dev_exit(void) {
  cdev_del(&cdev);
  unregister_chrdev_region(dev_number, 1);
  printk(KERN_INFO "Reverse device unregistered\n");
}

module_init(reverse_dev_init);
module_exit(reverse_dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ganavi");
MODULE_DESCRIPTION("Simple character driver for reversing strings");
