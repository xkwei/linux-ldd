#Makefile for hellowold.
ifneq ($(KERNELRELEASE),)
# call from kernel build system

obj-m	:= helloworld.o

else
#当然这里也可以是你自己的Linux的解压目录
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD       := $(shell pwd)

modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.order *.symvers

.PHONY: modules modules_install clean

endif


