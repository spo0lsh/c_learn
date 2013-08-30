#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include "read.h"

int main()
{
	char *name="write";
	char ch;
	signal(SIGUSR1, catch_usr1);

	/* infinity loop */
	while(1)
	{
		/* menu */
		printf("(Q)uit\n");
		scanf("%s", &ch);
		switch(ch)
		{
			/* hidden options for tests */
			case 't': // send "stop" signal, read 256 chars, write it do /dev/
				found_pids_by_name_send_signal(name,1); // writing finished
			break;
			/* quit */
			case 'Q':
				printf("Bye..\n");
				return(0);
			break;
			
			default:
				printf("What?\n");
			break;
		}
		
	}

	return 0;
}

/* catch signal SIGUSR1 */
void catch_usr1(int num)
{
	char *name="write";
	FILE *readfile;	
	readfile=NULL; // fixed
	FILE *writefile;
	writefile=NULL;
	char *line = NULL;
	size_t len = 0;
	ssize_t s_read;	
	readfile = fopen("/dev/ringbuffor","r");
	writefile = fopen("/tmp/rinbuffor","w");
	/* opening files */
	if (readfile == NULL || writefile == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	} else {
		/* reading data from driver and write it to file */
		while ((s_read = getline(&line, &len, readfile)) != -1) 
		{
			printf("%s",line);
			fprintf(writefile,"%s",line);
		}
		printf("\n");
		printf("Closing files\n");
		fclose(readfile);
		fclose(writefile);
	}
	/* send SIGUSR1 - done reading */
	printf("Send pids\n");
	found_pids_by_name_send_signal(name,1);
}



// found pids by name and send signal
int found_pids_by_name_send_signal(char * name,int num)
{
	const char*	directory = "/proc";
	size_t		taskNameSize = 1024; 
	char*		taskName = calloc(1, taskNameSize); // ?!
	DIR*		dir = opendir(directory);
	/* searching pid(s) by name in /proc directory */
	if(dir) {
		struct dirent* de = 0; //?
		while ((de = readdir(dir)) != 0)
		{
			if (strcmp(de->d_name, ".") == 0 
								|| strcmp(de->d_name, "..") == 0)
			{
				continue;
			}
			int pid = -1;
			int res = sscanf(de->d_name, "%d", &pid);
			if (res == 1)
			{
				char cmdline_file[1024] = {0};
				sprintf(cmdline_file, "%s/%d/cmdline", directory, pid);
				FILE* cmdline = fopen(cmdline_file, "r");
				if (getline(&taskName, &taskNameSize, cmdline) > 0)
				{
					if (strstr(taskName, name) != 0)
					{
						printf("Send signal to pid = %d\n",pid);
						switch(num)
						{
							case 1:
								kill(pid,SIGUSR1);
							break;
							case 2:
								kill(pid,SIGUSR2);
							break;
							default:
								printf("Something wrong\n");
							break;
						}
					}
				}
				fclose(cmdline);
			}
		}
		closedir(dir);
	}
	return 0;
}
