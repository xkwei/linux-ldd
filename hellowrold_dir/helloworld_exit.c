#if 1
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/cdev.h>     /*struct cdev*/
#include <linux/slab.h>     /*kfree*/
#endif

#include "main.h"



static void __exit hello_exit (void)
{
    dev_t devid;
    int temp;
    devid = MKDEV (helloworld_major, helloworld_minor);
    /*cdev_del (cdev_p);
        kfree(cdev_p);
       */
    for (temp = 0; temp < helloworld_nr_device; temp++){
        cdev_del(&scull_devices[temp].cdev);
    }
    kfree(scull_devices);
    scull_devices = NULL;
    
    unregister_chrdev_region(devid, helloworld_nr_device);
    DEBUG(1, "say goodbay!!.\n");
}


module_exit(hello_exit);

