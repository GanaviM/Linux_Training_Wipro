#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/spinlock.h>

#define DEVICE_NAME "spinlock_dev"
#define DATA_SIZE sizeof(struct user_data)

struct user_data {
  int value;
  char message[20];
};

static dev_t dev_num;
static struct cdev my_cdev;
static spinlock_t my_lock;

static int my_open(struct inode *inode, struct file *filp) {
  pr_info("Device opened\n");
  return 0;
}

static int my_release(struct inode *inode, struct file *filp) {
  pr_info("Device closed\n");
  return 0;
}

static ssize_t my_write(struct file *filp, const char __user *user_buf,
                       size_t count, loff_t *f_pos) {
  struct user_data data;
  unsigned long flags;

  // Ensure data size matches expected structure
  if (count != DATA_SIZE) {
    pr_err("Invalid data size: %zu, expected %zu\n", count, DATA_SIZE);
    return -EINVAL;
  }

  // Acquire spinlock to protect critical section
  spin_lock_irqsave(&my_lock, flags);

  // Check if user provided a valid buffer
  if (copy_from_user(&data, user_buf, count)) {
    spin_unlock_irqrestore(&my_lock, flags);
    pr_err("Error copying data from user\n");
    return -EFAULT;
  }

  // Process data from user space (replace with your actual logic)
  pr_info("Received data: value = %d, message = %s\n", data.value, data.message);

  // Copy data back to user space
  if (copy_to_user(user_buf, &data, count)) {
    spin_unlock_irqrestore(&my_lock, flags);
    pr_err("Error copying data to user\n");
    return -EFAULT;
  }

  // Release spinlock after critical section
  spin_unlock_irqrestore(&my_lock, flags);

  return count;
}

static ssize_t my_read(struct file *filp, char __user *user_buf,
                      size_t count, loff_t *f_pos) {
  struct user_data data;
  unsigned long flags;

  // Ensure data size matches expected structure
  if (count != DATA_SIZE) {
    pr_err("Invalid data size: %zu, expected %zu\n", count, DATA_SIZE);
    return -EINVAL;
  }

  // Acquire spinlock to protect critical section
  spin_lock_irqsave(&my_lock, flags);

  // Simulate reading data from some source (replace with your actual logic)
  data.value = 123;
  strcpy(data.message, "Sample message");

  // Copy data to user space
  if (copy_to_user(user_buf, &data, count)) {
    spin_unlock_irqrestore(&my_lock, flags);
    pr_err("Error copying data to user\n");
    return -EFAULT;
  }

  // Release spinlock after critical section
  spin_unlock_irqrestore(&my_lock, flags);

  return count;
}

static const struct file_operations my_fops = {
  .owner = THIS_MODULE,
  .open = my_open,
  .release = my_release,
  .read = my_read,
  .write = my_write,
};

static int __init data_transfer_init(void) {
  int ret;

  // Allocate a dynamic major number for the character device
  ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
  if (ret < 0) {
    pr_err("Failed to allocate character device region\n");
    return ret;
  }

  // Initialize the spinlock
  spin_lock_init(&my_lock);

  // Initialize the cdev structure
  cdev_init(&my_cdev, &my_fops);

  // Add the character device to the kernel
  ret = cdev_add(&my_cdev, dev_num, 1);
  if (ret < 0) {
    goto free_chrdev;
  }

  pr_info("Device %s created with major number: %u\n", DEVICE_NAME, MAJOR(dev_num));
  return 0;

free_chrdev:
  unregister_chrdev_region(dev_num, 1);
  return ret;
}

static void __exit data_transfer_exit(void) {
  cdev_del(&my_cdev);
  unregister_chrdev_region(dev_num, 1);
  pr_info("Device %s removed\n", DEVICE_NAME);
}

module_init(data_transfer_init);
module_exit(data_transfer_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ganavi");
MODULE_DESCRIPTION("Character device for data transfer with spinlock");
