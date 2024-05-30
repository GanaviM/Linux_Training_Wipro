# Define kernel source directory (replace with your actual path)
KERNEL_DIR = /lib/modules/$(shell uname -r)/build

# Name of the module
MODULE_NAME = kernel

# C compiler flags (adjust as needed)
CC = gcc

# Object files
obj-m := $(MODULE_NAME).o

# Include kernel headers from the defined directory
$(KERNEL_DIR)/.config:
	make -C $(KERNEL_DIR) M=$(PWD) headers_install

all:
	make -C $(KERNEL_DIR) M=$(PWD) modules

clean:
	make -C $(KERNEL_DIR) M=$(PWD) clean

# Load the module (requires root)
load:
	insmod $(MODULE_NAME).ko

# Unload the module (requires root)
unload:
	rmmod $(MODULE_NAME)
