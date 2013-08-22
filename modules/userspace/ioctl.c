#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#define MY_MACIG 'G'
#define READ_IOCTL _IOR(MY_MACIG, 0, int)  // not needed
#define WRITE_IOCTL _IOW(MY_MACIG, 1, int) // not needed
#define EMPTY_IOCTL _IO(MY_MACIG, 2) // defines our ioctl call
#define FULL_IOCTL _IO(MY_MACIG, 3) // defines our ioctl call
#define CLEAR_IOCTL _IO(MY_MACIG, 4) // defines our ioctl call
#define SIZE_IOCTL _IO(MY_MACIG, 5) // defines our ioctl call

int main(){
	char ch;
	int fd = -1;

	while(1)
	{
		printf("e - Check for Empty\n");
		printf("f - Check for Full\n");
		printf("c - Clear buffor\n");
		printf("s - Check buffor size\n");
		printf("q - quit\n");
		scanf("%s", &ch);
		if ((fd = open("/dev/ringbuffor", O_RDWR)) < 0) {
			perror("open");
			return -1;
		}
		switch(ch)
		{
			case 'e':
				if(ioctl(fd, EMPTY_IOCTL) < 0) {
					printf("Empty\n");
				}
			break;
			case 'f':
				if(ioctl(fd, FULL_IOCTL) < 0) {
					printf("Full\n");
				}
			break;
			case 'c':
				if(ioctl(fd, CLEAR_IOCTL) < 0) {
					perror("Clear\n");
				}
			break;
			case 's':
				if(ioctl(fd, SIZE_IOCTL) < 0) {
					printf("Size: %d\n",ioctl(fd, SIZE_IOCTL));
				} else {
					printf("Size: %d\n",ioctl(fd, SIZE_IOCTL));
				}
			break;
			case 'q':
				printf("Bye..\n");
				return(0);
			break;
		}
		close(fd);
	}

	return 0;

}

