CONFIG_MODULE_SIG=n

obj-m := kmod-ipsec-extension.o
kmod-ipsec-extension-objs := module_init.o packet_handler.o message_sender.o socket_client.o

KERNELBUILD :=/lib/modules/$(shell uname -r)/build

default:
	make -C $(KERNELBUILD) M=$(shell pwd) modules
	rm *.o .*.cmd *.mod.c *.order *.symvers

clean:
	make -C $(KERNELBUILD) M=$(shell pwd) clean

in:
	/sbin/insmod kmod-ipsec-extension.ko

re:
	/sbin/rmmod kmod-ipsec-extension
