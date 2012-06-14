#include <linux/init.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/cdev.h>     /*struct cdev*/
#include <linux/slab.h>     /*kfree*/


#define HELLOWORLD_MAX_DEVICE 1


extern int helloworld_minor;
extern int helloworld_major;
extern struct cdev *cdev_p;
static void __exit hello_exit(void)
{
    dev_t devid;

    devid = MKDEV (helloworld_major, helloworld_minor);
    /*cdev_del (cdev_p);
        kfree(cdev_p);
       */
    cdev_del(cdev_p);
    cdev_p = NULL;
    unregister_chrdev_region(devid, HELLOWORLD_MAX_DEVICE);
    printk (KERN_ALERT "say goodbay!!.\n");
}


module_exit(hello_exit);

