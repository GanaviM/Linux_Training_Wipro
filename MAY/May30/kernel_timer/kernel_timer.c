#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/uaccess.h>
#include <linux/fs.h>

#define DEVICE_NAME "timer_device"
#define TIMER_INTERVAL_SEC 5

static struct timer_list my_timer;
static int major_number;
static int is_open = 0;

static void timer_callback(struct timer_list *timer) {
    pr_info("Timer expired and callback executed!\n");
    mod_timer(&my_timer, jiffies + TIMER_INTERVAL_SEC * HZ);
}

static int device_open(struct inode *inode, struct file *file) {
    if (is_open)
        return -EBUSY;
    is_open++;
    try_module_get(THIS_MODULE);
    return 0;
}

static int device_release(struct inode *inode, struct file *file) {
    is_open--;
    module_put(THIS_MODULE);
    return 0;
}

static struct file_operations fops = {
    .open = device_open,
    .release = device_release,
};

static int __init timer_module_init(void) {
    pr_info("Initializing timer module\n");

    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        pr_alert("Registering char device failed with %d\n", major_number);
        return major_number;
    }

    timer_setup(&my_timer, timer_callback, 0);
    mod_timer(&my_timer, jiffies + TIMER_INTERVAL_SEC * HZ);

    pr_info("Timer module loaded with device major number %d\n", major_number);
    return 0;
}

static void __exit timer_module_exit(void) {
    pr_info("Exiting timer module\n");
    del_timer(&my_timer);
    unregister_chrdev(major_number, DEVICE_NAME);
    pr_info("Timer module unloaded\n");
}

module_init(timer_module_init);
module_exit(timer_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ganavi");
MODULE_DESCRIPTION("A simple Linux driver with a kernel timer");
