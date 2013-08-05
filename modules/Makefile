obj-m += hello.o test.o

all:
	make hello test

hello:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

test:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
