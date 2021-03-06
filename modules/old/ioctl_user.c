#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#define MY_MACIG 'G'
#define READ_IOCTL _IOR(MY_MACIG, 0, int)
#define WRITE_IOCTL _IOW(MY_MACIG, 1, int)
#define EMPTY_IOCTL _IO(MY_MACIG, 2) // defines our ioctl call
#define FULL_IOCTL _IO(MY_MACIG, 3) // defines our ioctl call
#define CLEAR_IOCTL _IO(MY_MACIG, 4) // defines our ioctl call
#define SIZE_IOCTL _IO(MY_MACIG, 5) // defines our ioctl call

int main(){
	char buf[256];
	int fd = -1;
	if ((fd = open("/dev/ringbuffor", O_RDWR)) < 0) {
		perror("open");
		return -1;
	}
	if(ioctl(fd, WRITE_IOCTL, "hello world") < 0)
		perror("WRITE ioctl");
	if(ioctl(fd, READ_IOCTL, buf) < 0)
		perror("READ ioctl");
	if(ioctl(fd, EMPTY_IOCTL) < 0) {
		printf("Empty\n");
	}
	if(ioctl(fd, WRITE_IOCTL, "hello world") < 0)
		perror("WRITE ioctl");
	if(ioctl(fd, FULL_IOCTL) < 0) {
		printf("Full\n");
	}
	if(ioctl(fd, SIZE_IOCTL) < 0) {
		printf("Size: %d\n",ioctl(fd, SIZE_IOCTL));
	} else {
		printf("Size: %d\n",ioctl(fd, SIZE_IOCTL));
	}
	if(ioctl(fd, CLEAR_IOCTL) < 0) {
		perror("Clear\n");
	}
	if(ioctl(fd, EMPTY_IOCTL) < 0) {
		printf("Empty\n");
	}
	if(ioctl(fd, SIZE_IOCTL) < 0) {
		printf("Size: %d\n",ioctl(fd, SIZE_IOCTL));
	} else {
		printf("Size: %d\n",ioctl(fd, SIZE_IOCTL));
	}
	printf("\n");
	printf("message: %s\n", buf);
	close(fd);
	return 0;

}

