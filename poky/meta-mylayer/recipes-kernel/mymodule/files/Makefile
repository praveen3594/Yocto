# # Makefile for out-of-tree Yocto kernel module

# obj-m += mymodule.o

# # # Support Yocto variables
# # ifneq ($(KERNELRELEASE),)
# # # kbuild part (called by kernel)
# # else
# # # Called directly or by bitbake
# # KDIR ?= $(KERNEL_PATH)
# # PWD  := $(shell pwd)

# # default:
# # 	$(MAKE) -C $(KDIR) M=$(PWD) modules

# # clean:
# # 	$(MAKE) -C $(KDIR) M=$(PWD) clean

# # endif

obj-m += mymodule.o
all:
	$(MAKE) -C $(KERNEL_SRC) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNEL_SRC) M=$(PWD) clean

#modules_install: 
#	$(MAKE) -C $(KERNEL_SRC) M=$(PWD) modules_install
