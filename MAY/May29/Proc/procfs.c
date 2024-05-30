#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#define PROC_NAME "example_proc"
#define BUFFER_SIZE 128

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple Linux procfs driver");
MODULE_VERSION("0.1");

static struct proc_dir_entry *proc_entry;
static char proc_buffer[BUFFER_SIZE];
static unsigned long proc_buffer_size = 0;

static ssize_t proc_read(struct file *file, char __user *buf, size_t count, loff_t *pos)
{
    if (*pos > 0 || count < proc_buffer_size)
        return 0;

    if (copy_to_user(buf, proc_buffer, proc_buffer_size))
        return -EFAULT;

    *pos = proc_buffer_size;
    return proc_buffer_size;
}

static ssize_t proc_write(struct file *file, const char __user *buf, size_t count, loff_t *pos)
{
    if (count > BUFFER_SIZE)
        proc_buffer_size = BUFFER_SIZE;
    else
        proc_buffer_size = count;

    if (copy_from_user(proc_buffer, buf, proc_buffer_size))
        return -EFAULT;

    return proc_buffer_size;
}

static const struct proc_ops proc_file_ops = {
    .proc_read = proc_read,
    .proc_write = proc_write,
};

static int __init example_init(void)
{
    proc_entry = proc_create(PROC_NAME, 0666, NULL, &proc_file_ops);
    if (!proc_entry) {
        pr_alert("Error: Could not initialize /proc/%s\n", PROC_NAME);
        return -ENOMEM;
    }

    pr_info("/proc/%s created\n", PROC_NAME);
    return 0;
}

static void __exit example_exit(void)
{
    remove_proc_entry(PROC_NAME, NULL);
    pr_info("/proc/%s removed\n", PROC_NAME);
}

module_init(example_init);
module_exit(example_exit);
