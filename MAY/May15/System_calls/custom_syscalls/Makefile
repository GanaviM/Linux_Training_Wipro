# Makefile

obj-m += custom_syscall.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc test_custom_syscall.c -o test_custom_syscall

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f test_custom_syscall
