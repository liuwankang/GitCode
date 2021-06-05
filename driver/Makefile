ifneq ($(KERNELRELEASE),)
obj-m :=hellodev.o
else
PWD := $(shell pwd)

KDIR := /lib/modules/`uname -r`/build

all: 
	make -C $(KDIR) M=$(PWD)
	
clean:
	rm -rf *.o *.ko *.mod.c *.systemer *.c~ *~
endif
