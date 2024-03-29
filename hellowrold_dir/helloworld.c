#include <linux/init.h>
#include <linux/module.h>

#define DEVICE_AUTHOR   "xkwei  <kwxia@hbgk.net>"
#define DEVICE_DESCRIPTIN "for helloworld test"

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


static int hello_init(void)
{
    printk(KERN_ALERT "hello world.\n");
    printf_param();
    return 0;
}

static void hello_exit(void)
{
    printk (KERN_ALERT "say goodbay!!.\n");
}


module_init(hello_init);
module_exit(hello_exit);

