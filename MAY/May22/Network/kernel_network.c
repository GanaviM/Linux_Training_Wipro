#include <linux/module.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>

#define DRIVER_NAME "simple_network"

static struct net_device *net_dev;

static int simple_net_open(struct net_device *dev) {
    netif_start_queue(dev);
    printk(KERN_INFO "%s: device opened\n", dev->name);
    return 0;
}

static int simple_stop(struct net_device *dev) {
    netif_stop_queue(dev);
    printk(KERN_INFO "%s: device closed\n", dev->name);
    return 0;
}

static netdev_tx_t simple_start_xmit(struct sk_buff *skb, struct net_device *dev) {
    printk(KERN_INFO "%s: start_xmit called\n", dev->name);
    dev_kfree_skb(skb);
    return NETDEV_TX_OK;
}

static const struct net_device_ops netdev_ops = {
    .ndo_open = simple_net_open,
    .ndo_stop = simple_stop,
    .ndo_start_xmit = simple_start_xmit,
};

static void setup(struct net_device *dev) {
    ether_setup(dev);
    dev->netdev_ops = &netdev_ops;
    dev->flags |= IFF_NOARP;
    dev->features |= NETIF_F_HW_CSUM;
}

static int __init simple_init(void) {
    int result;

    net_dev = alloc_etherdev(0);
    if (!net_dev) {
        printk(KERN_ERR "alloc_netdev failed\n");
        return -ENOMEM;
    }

    strncpy(net_dev->name, "simple%d", IFNAMSIZ);

    setup(net_dev);

    result = register_netdev(net_dev);
    if (result) {
        printk(KERN_ERR "register_netdev failed: %d\n", result);
        free_netdev(net_dev);
        return result;
    }

    printk(KERN_INFO "%s: module loaded\n", DRIVER_NAME);
    return 0;
}

static void __exit simple_exit(void) {
    unregister_netdev(net_dev);
    free_netdev(net_dev);
    printk(KERN_INFO "%s: module unloaded\n", DRIVER_NAME);
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("techdhaba");
MODULE_DESCRIPTION("A simple network driver example");
MODULE_VERSION("0.1");
