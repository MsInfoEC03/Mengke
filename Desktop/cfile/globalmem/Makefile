KVERS = $(shell uname -r)

obj-m += globalmem.o

build: kernel_modules

EXTRA_CFLAGS=-g -O2

kernel_modules:
	make -C /lib/modules/$(KVERS)/build M=$(CURDIR) modules

clean:
	make -C /lib/modules/$(KVERS)/build M=$(CURDIR) clean
