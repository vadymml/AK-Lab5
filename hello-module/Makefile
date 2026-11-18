ifneq ($(KERNELRELEASE),)

obj-m := hello1.o hello2.o

ccflags-y := -I$(src)/inc

else

KDIR ?= $(HOME)/repos/linux-stable
ARCH ?= arm

default:
	$(MAKE) -C $(KDIR) M=$(CURDIR) ARCH=$(ARCH) CROSS_COMPILE="$(CROSS_COMPILE)" modules

clean:
	$(MAKE) -C $(KDIR) M=$(CURDIR) ARCH=$(ARCH) clean

endif
