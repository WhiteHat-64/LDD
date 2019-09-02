obj-m := my_driver.o

my_driver.ko: my_driver.c my_driver.h
	make -C /usr/src/linux-source-4.18.0/linux-source-4.18.0 M=`pwd` modules


.PHONY=clean

clean:
	rm modules.order  Module.symvers  my_driver.ko  my_driver.mod.c  my_driver.mod.o  my_driver.o
