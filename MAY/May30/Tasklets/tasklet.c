#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>

void my_tasklet_handler(unsigned long data)
{
    printk(KERN_INFO "Tasklet handler called with data: %lu\n", data);
}

DECLARE_TASKLET_OLD(my_tasklet, my_tasklet_handler, 0);

void my_interrupt_handler(void)
{
    // Schedule the tasklet
    tasklet_schedule(&my_tasklet);
}

static int __init my_module_init(void)
{
    printk(KERN_INFO "Loading tasklet module\n");
    // Simulate scheduling the tasklet
    my_interrupt_handler();
    return 0;
}

static void __exit my_module_exit(void)
{
    // Ensure the tasklet is killed before module exit
    tasklet_kill(&my_tasklet);
    printk(KERN_INFO "Unloading tasklet module\n");
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("techdhaba");
MODULE_DESCRIPTION("A simple tasklet example");
