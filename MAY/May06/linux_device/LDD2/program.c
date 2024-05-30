#include <linux/init.h>
#include <linux/module.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/uaccess.h>

// Define data structure to store the value
static int data;

// Define kobject and attribute name for sysfs entry
static struct kobject *kobj;
static char *data_name = "my_data";

// Function to show the value of data in sysfs
static ssize_t data_show(struct kobject *kobj, struct kobj_attribute *attr,
                          char *buf) {
  return sprintf(buf, "%d\n", data);
}

// Function to write to data through sysfs
static ssize_t data_store(struct kobject *kobj, struct kobj_attribute *attr,
                           const char __user *user_buf, size_t count) {
  long tmp;
  int res;

  res = kstrtol(user_buf, 0, &tmp);
  if (res < 0)
    return res;

  data = tmp;
  return count;
}

// Define attribute for data
static struct kobj_attribute data_attr =
    __ATTR(my_data, 0664, data_show, data_store);

static struct attribute *default_attrs[] = {
    &data_attr.attr,
    NULL,
};

static struct attribute_group attr_group = {
    .name = "my_data_group",
    .attrs = default_attrs,
};

static int __init data_module_init(void) {
  int ret;

  // Create kobject for sysfs entry
  kobj = kobject_create_and_add("my_data_module", NULL);
  if (!kobj)
    return -ENOMEM;

  // Create sysfs entry for data
  ret = sysfs_create_group(kobj, &attr_group);
  if (ret) {
    kobject_put(kobj);
    return ret;
  }

  printk(KERN_INFO "Data module loaded!\n");
  return 0;
}

static void __exit data_module_exit(void) {
  // Remove sysfs entry
  sysfs_remove_group(kobj, &attr_group);
  kobject_put(kobj);

  printk(KERN_INFO "Data module unloaded!\n");
}

module_init(data_module_init);
module_exit(data_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("TechDhaba");
MODULE_DESCRIPTION("A simple kernel module for data access through sysfs");
