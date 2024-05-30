#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "my_data_transfer"
#define DATA_SIZE sizeof(struct user_data)

struct user_data {
  int value;
  char message[20];
};

static dev_t dev_num;
static struct cdev my_cdev;

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

  // Ensure data size matches expected structure
  if (count != DATA_SIZE) {
    pr_err("Invalid data size: %zu, expected %zu\n", count, DATA_SIZE);
    return -EINVAL;
  }

  // Check if user provided a valid buffer
  if (copy_from_user(&data, user_buf, count)) {
    pr_err("Error copying data from user\n");
    return -EFAULT;
  }

  // Process data from user space
  pr_info("Received data: value = %d, message = %s\n", data.value, data.message);

  return count;
}

static const struct file_operations my_fops = {
  .owner = THIS_MODULE,
  .open = my_open,
  .release = my_release,
  .write = my_write,
};

static int __init data_transfer_init(void) {
  int ret;

  ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
  if (ret < 0) {
    return ret;
  }

  cdev_init(&my_cdev, &my_fops);
  ret = cdev_add(&my_cdev, dev_num, 1);
  if (ret < 0) {
    goto free_chrdev;
  }

  pr_info("Device %s created\n", DEVICE_NAME);
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
MODULE_AUTHOR("GANAVI");
MODULE_DESCRIPTION("Character device for data transfer");
