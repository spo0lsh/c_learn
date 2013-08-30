#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include "ioctl.h"

/*
 * 
 * Simple ioctl() testing program
 *  
*/



int main(){
	/* menu */
	char menu;
	/* file descriptor */
	int fd = -1;

	/* infinity loop */
	while(1)
	{
		/* menu */
		printf("e - Check for Empty\n");
		printf("f - Check for Full\n");
		printf("c - Clear buffor\n");
		printf("s - Check buffor size\n");
		printf("q - quit\n");
		scanf("%s", &menu);
		/* opening module char device */
		if ((fd = open("/dev/ringbuffor", O_RDWR)) < 0) {
			perror("open");
			return -1;
		}
		/* switch for menu */
		switch(menu)
		{
			/* empty buffor */
			case 'e':
				if(ioctl(fd, EMPTY_IOCTL) < 0) {
					printf("Empty\n");
				}
			break;
			/* full buffor */
			case 'f':
				if(ioctl(fd, FULL_IOCTL) < 0) {
					printf("Full\n");
				}
			break;
			/* clear buffor */
			case 'c':
				if(ioctl(fd, CLEAR_IOCTL) < 0) {
					perror("Clear\n");
				}
			break;
			/* using size buffor */
			case 's':
				if(ioctl(fd, SIZE_IOCTL) < 0) {
					printf("Size: %d\n",ioctl(fd, SIZE_IOCTL));
				} else {
					printf("Size: %d\n",ioctl(fd, SIZE_IOCTL));
				}
			break;
			/* exit */
			case 'q':
				printf("Bye..\n");
				/* closing file */
				close(fd);
				return(0);
			break;
			/* default case */
			default:
				printf("Wrong choice\n");
			break;
		}
		/* closing file */
		close(fd);
	}

	return 0;

}

