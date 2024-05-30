#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/string.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple Linux sysfs driver");
MODULE_VERSION("0.1");

static struct kobject *example_kobject;
static int foo;

static ssize_t foo_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%d\n", foo);
}

static ssize_t foo_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    sscanf(buf, "%du", &foo);
    return count;
}

static struct kobj_attribute foo_attribute = __ATTR(foo, 0660, foo_show, foo_store);

static int __init example_init(void)
{
    int error = 0;

    example_kobject = kobject_create_and_add("example_kobject", kernel_kobj);
    if (!example_kobject)
        return -ENOMEM;

    error = sysfs_create_file(example_kobject, &foo_attribute.attr);
    if (error) {
        pr_debug("failed to create the foo file in /sys/kernel/example_kobject\n");
    }

    return error;
}

static void __exit example_exit(void)
{
    kobject_put(example_kobject);
}

module_init(example_init);
module_exit(example_exit);
