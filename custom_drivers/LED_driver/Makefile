obj-m := led_driver.o
KERNELDIR ?= ../../linux-stable/ 
PWD := $(shell pwd)
CROSS_COMPILE := /home/goldeneagle/Documents/BBB/build/gcc-arm-8.3-2019.03-x86_64-arm-linux-gnueabihf/bin/arm-linux-gnueabihf-

all:
	make ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERNELDIR)  M=$(PWD) modules

