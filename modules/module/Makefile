NAME = ringbuffor

obj-m += $(NAME).o

all:
	make $(NAME)

$(NAME):
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
