obj-m += mygpio.o


all:
	$(MAKE) -C $(KERNEL_SRC) M=$(shell pwd) modules

modules_install:
	$(MAKE) -C $(KERNEL_SRC) M=$(shell pwd) modules_install

clean:
	$(MAKE) -C $(KERNEL_SRC) M=$(shell pwd) clean




