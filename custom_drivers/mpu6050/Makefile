obj-m := mpu6050.o
KERNELDIR ?= ../../linux-stable/ 
PWD := $(shell pwd)
CROSS_COMPILE := /home/goldeneagle/Documents/BBB/build/gcc-linaro-7.4.1-2019.02-x86_64_armv8l-linux-gnueabihf/bin/armv8l-linux-gnueabihf-
all:
	make ARCH=arm   CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERNELDIR)  M=$(PWD) modules

