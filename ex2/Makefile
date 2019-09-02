driver_name = my_driver
obj-m := $(driver_name).o

$(driver_name).ko: $(driver_name).c
	make -C /usr/src/linux-source-4.18.0/linux-source-4.18.0 M=`pwd` modules


.PHONY=clean

clean:
	rm -r modules.order  Module.symvers  *.ko  *.mod.?  $(driver_name).o .$(driver_name).* .tmp_versions
