#include <linux/init.h>
#include <linux/module.h>

#define DEVICE_AUTHOR   "xkwei  <kwxia@hbgk.net>"
#define DEVICE_DESCRIPTIN "for helloworld test"

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DEVICE_AUTHOR);
MODULE_DESCRIPTION(DEVICE_DESCRIPTIN);
MODULE_SUPPORTED_DEVICE("helloworld");
MODULE_VERSION("version v0.2");

static int hello_init(void)
{
    printk(KERN_ALERT "hello world.\n");
    return 0;
}

static void hello_exit(void)
{
    printk (KERN_ALERT "say goodbay!!.\n");
}


module_init(hello_init);
module_exit(hello_exit);

