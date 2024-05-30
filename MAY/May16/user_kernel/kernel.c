#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

static char kernel_buffer[50];

static ssize_t my_device_read(struct device *dev, struct device_attribute *attr,
                             char *user_buf, size_t count) {
  int ret;

  // Check if user space buffer is accessible for writing
  if (!access_ok(VERIFY_WRITE, user_buf, count)) {
    return -EFAULT; // User space buffer is invalid
  }

  // Copy data from kernel to user space (up to count bytes)
  ret = copy_to_user(user_buf, kernel_buffer, min(count, strlen(kernel_buffer)));

  if (ret) {
    return -EFAULT; // Error during copy
  }

  return strlen(kernel_buffer); // Return the size of data copied
}

static ssize_t my_device_write(struct device *dev, struct device_attribute *attr,
                              const char *user_buf, size_t count) {
  int ret;

  // Check if user space buffer is accessible for reading
  if (!access_ok(VERIFY_READ, user_buf, count)) {
    return -EFAULT; // User space buffer is invalid
  }

  // Copy data from user space to kernel (up to count bytes)
  ret = copy_from_user(kernel_buffer, user_device_write, min(count, sizeof(kernel_buffer) - 1));

  if (ret) {
    return -EFAULT; // Error during copy
  }

  // Ensure the buffer is null-terminated
  kernel_buffer[ret] = '\0';

  return ret; // Return the size of data copied
}

static const struct device_attribute files[] = {
  __ATTR(data, S_IRUGO | S_IWUGO, my_device_read, my_device_write),
};

// ... (device driver registration code)

module_exit(my_device_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ganavi");
MODULE_DESCRIPTION("A simple device driver example");
