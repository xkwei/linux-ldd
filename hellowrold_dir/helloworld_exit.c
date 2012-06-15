#if 1
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/cdev.h>     /*struct cdev*/
#include <linux/slab.h>     /*kfree*/
#include <linux/device.h>   /*class device*/
#endif

#include "main.h"



static void __exit hello_exit (void)
{
    dev_t devid;
    int temp;
    devid = MKDEV (helloworld_major, helloworld_minor);

	for (temp = 0; temp < helloworld_nr_device; ++temp)
		device_destroy(helloworld_class, MKDEV(helloworld_major, temp));

    class_destroy(helloworld_class);

    for (temp = 0; temp < helloworld_nr_device; temp++){
        cdev_del(&scull_devices[temp].cdev);
        scull_trim(&scull_devices[temp]);
    }
    kfree(scull_devices);
    scull_devices = NULL;
    
    unregister_chrdev_region(devid, helloworld_nr_device);
    DEBUG(1, "say goodbay!!.\n");
}


module_exit(hello_exit);

