#include <linux/init.h>
#include <linux/fs.h>
#include <linux/module.h>

#define HELLOWORLD_MAX_DEVICE 1


extern int helloworld_minor;
extern int helloworld_major;
static void hello_exit(void)
{
    dev_t devid;

    devid = MKDEV (helloworld_major, helloworld_minor);
    unregister_chrdev_region(devid, HELLOWORLD_MAX_DEVICE);
    printk (KERN_ALERT "say goodbay!!.\n");
}


module_exit(hello_exit);

