#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/random.h>
#include <linux/cdev.h>
#include <linux/device.h>

#define DEVICE_NAME "temp_sensor"
#define CLASS_NAME "temp"

static int major_number;
static struct class *temp_class = NULL;
static struct device *temp_device = NULL;
static struct cdev temp_cdev;
static int device_open_count = 0;

static int dev_open(struct inode *inodep, struct file *filep) {
    if (device_open_count) {
        return -EBUSY;
    }
    device_open_count++;
    try_module_get(THIS_MODULE);
    printk(KERN_INFO "TempSensor: Device has been opened\n");
    return 0;
}

static int dev_release(struct inode *inodep, struct file *filep) {
    device_open_count--;
    module_put(THIS_MODULE);
    printk(KERN_INFO "TempSensor: Device successfully closed\n");
    return 0;
}

static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset) {
    int temperature;
    char temp_str[4];
    int error_count;

    get_random_bytes(&temperature, sizeof(int));
    temperature = temperature % 101;

    snprintf(temp_str, sizeof(temp_str), "%d", temperature);

    error_count = copy_to_user(buffer, temp_str, sizeof(temp_str));

    if (error_count == 0) {
        printk(KERN_INFO "TempSensor: Sent temperature %d to user\n", temperature);
        return 0;
    } else {
        printk(KERN_INFO "TempSensor: Failed to send temperature to user\n");
        return -EFAULT;
    }
}

static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset) {
    printk(KERN_ALERT "TempSensor: Write operation not supported\n");
    return -EINVAL;
}

static struct file_operations fops = {
    .open = dev_open,
    .read = dev_read,
    .write = dev_write,
    .release = dev_release,
};

static int __init temp_sensor_init(void) {
    printk(KERN_INFO "TempSensor: Initializing the TempSensor LKM\n");

    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        printk(KERN_ALERT "TempSensor failed to register a major number\n");
        return major_number;
    }
    printk(KERN_INFO "TempSensor: Registered with major number %d\n", major_number);

    temp_class = class_create(CLASS_NAME);
    if (IS_ERR(temp_class)) {
        unregister_chrdev(major_number, DEVICE_NAME);
        printk(KERN_ALERT "Failed to register device class\n");
        return PTR_ERR(temp_class);
    }
    printk(KERN_INFO "TempSensor: Device class registered\n");

    temp_device = device_create(temp_class, NULL, MKDEV(major_number, 0), NULL, DEVICE_NAME);
    if (IS_ERR(temp_device)) {
        class_destroy(temp_class);
        unregister_chrdev(major_number, DEVICE_NAME);
        printk(KERN_ALERT "Failed to create the device\n");
        return PTR_ERR(temp_device);
    }
    printk(KERN_INFO "TempSensor: Device class created\n");

    cdev_init(&temp_cdev, &fops);
    temp_cdev.owner = THIS_MODULE;
    if (cdev_add(&temp_cdev, MKDEV(major_number, 0), 1) < 0) {
        device_destroy(temp_class, MKDEV(major_number, 0));
        class_destroy(temp_class);
        unregister_chrdev(major_number, DEVICE_NAME);
        printk(KERN_ALERT "Failed to add cdev\n");
        return -1;
    }

    return 0;
}

static void __exit temp_sensor_exit(void) {
    cdev_del(&temp_cdev);
    device_destroy(temp_class, MKDEV(major_number, 0));
    class_unregister(temp_class);
    class_destroy(temp_class);
    unregister_chrdev(major_number, DEVICE_NAME);
    printk(KERN_INFO "TempSensor: Goodbye from the LKM!\n");
}

module_init(temp_sensor_init);
module_exit(temp_sensor_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple Linux char driver for a virtual temperature sensor");
MODULE_VERSION("0.1");
