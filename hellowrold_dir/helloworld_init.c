#include <linux/init.h>
#include <linux/module.h>   /*init module*/
#include <linux/kernel.h>   /*init printk*/
#include <linux/fs.h>       /*dev_t*/
#include <linux/cdev.h>     /*struct cdev*/
#include <linux/slab.h>     /*kfree*/

#define DEVICE_AUTHOR   "xkwei  <kwxia@hbgk.net>"
#define DEVICE_DESCRIPTIN "for helloworld test"
#define HELLOWORLD_MAX_DEVICE 1
#define DEVICE_REGISTER_NAME "helloworld v0.5"

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DEVICE_AUTHOR);
MODULE_DESCRIPTION(DEVICE_DESCRIPTIN);
MODULE_SUPPORTED_DEVICE("helloworld");
MODULE_VERSION("version v0.2");


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

int helloworld_minor = 0;
int helloworld_major = 0;
struct cdev *cdev_p;


static void printf_param(void)
{
    printk(KERN_ALERT "\nprintf_param.\n");
    printk(KERN_ALERT "myshort = %d.\n", myshort);
    printk(KERN_ALERT "myint = %d.\n", myint);
    printk(KERN_ALERT "mylong = %ld.\n", mylong);
    printk(KERN_ALERT "mystring :%s.\n", mystring);
    printk(KERN_ALERT "myarray : %d , %d , %d , %d.\n",\
                            myarray[0], myarray[1], myarray[2], myarray[3]);
}

/* File operations struct for character device */
static const struct file_operations helloworld_fops = {
	.owner		= THIS_MODULE,
 };


static int char_reg_setup_cdev (void)
{
    int err;
    dev_t devid = MKDEV (helloworld_major, helloworld_minor);

	cdev_p= cdev_alloc();
	if (!cdev_p) {
		printk(KERN_WARNING "cdev_alloc failed\n");
		goto out;
	}

    cdev_p->owner = THIS_MODULE;
	cdev_p->ops = &helloworld_fops;

    err = cdev_add(cdev_p, devid, HELLOWORLD_MAX_DEVICE);
    if (err < 0){
        printk (KERN_WARNING "cdev_add fialed.\n");
        goto err_cdev_add;
    }

    return 0;
    
err_cdev_add:
    kfree (cdev_p);
    cdev_p = NULL;
out:
    return -1;
}

static int __init hello_init(void)
{
    int err;
    dev_t devid = 0;
    
    printk(KERN_ALERT "hello world.\n");
    printf_param();
    
    err = alloc_chrdev_region(&devid, 0, HELLOWORLD_MAX_DEVICE, DEVICE_REGISTER_NAME);
    if (err < 0){
        printk (KERN_ALERT "ERR alloc_chrdev_region.\n");
        goto err_alloc_chrdev_region;
    }
    
    helloworld_major = MAJOR (devid);
    helloworld_minor= MINOR(devid);

    err = char_reg_setup_cdev();
    if (err < 0){
        printk (KERN_WARNING "err_char_reg_setup_cdev.\n");
        goto err_char_reg_setup_cdev;
    }

    return 0;
    
err_char_reg_setup_cdev:
    unregister_chrdev_region(devid, HELLOWORLD_MAX_DEVICE);
err_alloc_chrdev_region:
    return -1;
}


module_init(hello_init);
