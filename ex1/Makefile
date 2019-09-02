obj-m := my_driver.o

my_driver.ko: my_driver.c
	make -C /usr/src/linux-headers-`uname -r` M=`pwd` modules


.PHONY=clean

clean:
	rm modules.order  Module.symvers  my_driver.ko  my_driver.mod.c  my_driver.mod.o  my_driver.o
