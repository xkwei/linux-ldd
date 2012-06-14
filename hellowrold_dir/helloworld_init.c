#include <linux/init.h>
#include <linux/module.h>   /*init module*/
#include <linux/kernel.h>   /*init printk*/
#include <linux/fs.h>       /*dev_t*/
#include <linux/cdev.h>     /*struct cdev*/
#include <linux/slab.h>     /*kfree*/


#include "main.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DEVICE_AUTHOR);
MODULE_DESCRIPTION(DEVICE_DESCRIPTIN);
MODULE_SUPPORTED_DEVICE("helloworld");
MODULE_VERSION("version v0.2");


#if 0
static short myshort = 2;
static int  myint = 4;
static long int mylong = 8;
/*static char mychar = '1';*/
static char *mystring = "kwxia@hbgk.net";
static int myarray [4] = {1, 2, 3, 4};


module_param(myshort, short, S_IRUGO);
MODULE_PARM_DESC(myshort, "short test array.");

module_param(myint, int, S_IRUGO);
MODULE_PARM_DESC(myint, "myint test array.");

module_param(mylong, long, S_IRUGO);
MODULE_PARM_DESC(mylong, "mylong test array.");

/*
module_param(mychar, char, S_IRUGO);
MODULE_PARM_DESC(mychar, "mychar test array.");
*/

module_param(mystring, charp, S_IRUGO);
MODULE_PARM_DESC(mystring, "mysrting test array.");

module_param_array(myarray, int, NULL, 0);
MODULE_PARM_DESC(myarray, "myarray test array.");
#endif



int helloworld_minor = 0;
int helloworld_major = 0;
int helloworld_nr_device = HELLOWORLD_MAX_DEVICE;
int quantum = SCULL_QUANTUM;
int qset = SCULL_QSET;
struct scull_dev *scull_devices = NULL;

module_param(helloworld_minor, int, S_IRUGO);
MODULE_PARM_DESC(helloworld_minor, "devid : minor.");

module_param(helloworld_major, int, S_IRUGO);
MODULE_PARM_DESC(helloworld_major, "devid : major.");

module_param(helloworld_nr_device, int, S_IRUGO);
MODULE_PARM_DESC(helloworld_nr_device, "max devices .");

module_param(quantum, int, S_IRUGO);
MODULE_PARM_DESC(quantum, "quantum size.");

module_param(qset, int, S_IRUGO);
MODULE_PARM_DESC(qset, "qset size.");



static void printf_param(void)
{
    DEBUG(1, "\nprintf_param.\n");
    DEBUG(1, "minor = %d.\n", helloworld_minor);
    DEBUG(1, "major = %d.\n", helloworld_major);
    DEBUG(1, "nr_devices = %d.\n", helloworld_nr_device);
    DEBUG(1, "quantum :%d.\n", quantum);
    DEBUG(1, "qset :%d.\n", qset);
}

void scull_trim (struct scull_dev *dev)
{
    struct scull_qset *current, *next;
    current = dev->qset;

    for (;current;next){
        
    }
}

/* open release*/
static int hello_open(struct inode *inode, struct file *filp)
{
    DEBUG (7, "hello_open.\n");
    struct scull_dev *dev;
    
    dev = container_of(inode->i_cdev, struct scull_dev, cdev);
    filp->private_data = dev;

	if ( (filp->f_flags & O_ACCMODE) == O_WRONLY) {
		scull_trim(dev); /* ignore errors */
	}

	return 0;
}

int hello_release(struct inode *inode, struct file *filp)
{
    DEBUG (7, "hello_release.\n");

    return 0;
}

ssize_t hello_read(struct file *filp, char __user *buf, size_t count , loff_t *f_ops)
{
    DEBUG (7, "hello_read.\n");

    return 0;
}

loff_t hello_lseek(struct file *filp, loff_t off, int whence)
{
    DEBUG (7, "hello_lseek.\n");

    return 0;
}


/* File operations struct for character device */
static const struct file_operations helloworld_fops = {
	.open = hello_open,
	.read = hello_read,
	.llseek = hello_lseek,
	.release = hello_release,
	.owner		= THIS_MODULE,
 };


static int char_reg_setup_cdev (void)
{
    int err;
    int temp = 0;
    dev_t devid = MKDEV (helloworld_major, helloworld_minor);

    scull_devices = kmalloc(helloworld_nr_device * sizeof (struct scull_dev),\
                                    GFP_KERNEL);
	memset((char *)scull_devices, 0,\
	            helloworld_nr_device * sizeof(struct scull_dev));

    for (;temp < helloworld_nr_device; temp++){
        scull_devices[temp].quantum = quantum;
        scull_devices[temp].qset = qset;
        scull_devices[temp].size = 0;
        cdev_init(&scull_devices[temp].cdev, &helloworld_fops);
        scull_devices[temp].cdev.ops = &helloworld_fops;
        scull_devices[temp].cdev.owner = THIS_MODULE;
    }

    err = cdev_add(&scull_devices[temp].cdev, devid, helloworld_nr_device);
    if (err < 0){
        DEBUG (1, "err_cdev_add.");
        goto err_cdev_add;
    }
    #if 0
    cdev_p= cdev_alloc();
	if (!cdev_p) {
		DEBUG(1, "cdev_alloc failed\n");
		goto out;
	}

    cdev_p->owner = THIS_MODULE;
	cdev_p->ops = &helloworld_fops;

    err = cdev_add(cdev_p, devid, HELLOWORLD_MAX_DEVICE);
    if (err < 0){
        DEBUG (1, "cdev_add fialed.\n");
        goto err_cdev_add;
    }
    #endif
    

    return 0;

err_cdev_add:
    kfree (scull_devices);
    scull_devices = NULL;

    return err;
}

static int __init hello_init(void)
{
    int err;
    dev_t devid = 0;
    
    DEBUG(1, "hello world.\n");
    printf_param();

    if (helloworld_major){
        err = register_chrdev_region(MKDEV(helloworld_major, helloworld_minor),\
            helloworld_nr_device, DEVICE_REGISTER_NAME);
    }else{
        err = alloc_chrdev_region(&devid, 0, helloworld_nr_device, DEVICE_REGISTER_NAME);
        helloworld_major = MAJOR (devid);
        helloworld_minor = MINOR(devid);
    }
    if (err < 0){
        DEBUG (1, "ERR alloc_chrdev_region(or register_chrdev_region).\n");
        goto err_alloc_chrdev_region;
    }
    

    err = char_reg_setup_cdev();
    if (err < 0){
        DEBUG (1, "err_char_reg_setup_cdev.\n");
        goto err_char_reg_setup_cdev;
    }

    return 0;
    
err_char_reg_setup_cdev:
    unregister_chrdev_region(devid, helloworld_nr_device);
err_alloc_chrdev_region:
    return err;
}


module_init(hello_init);
