#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include "write.h"

/* global variable */
char user_string[BUFFORSIZE+1];

int main()
{
	char *name="read";
	char input[BUFFORSIZE+1];
	char ch;
	FILE *file;	

	/* infinity loop */
	while(1)
	{
		/* register signal SIGUSR1 */
		signal(SIGUSR1, catch_usr1);
		/* menu */
		printf("(W)rite\n");
		printf("(Q)uit\n");
		scanf("%s", &ch);
		switch(ch)
		{
			/* write 256 chars to driver and send SIGUSR1 to read task */
			case 'W':
				printf("Input string: ");
				scanf("%256s", input);
				/* try open file in write mode */
				file = fopen("/dev/ringbuffor","w");
				if (file == NULL)
				{
					printf("Error opening file!\n");
					exit(1);
				}
				fprintf(file,"%s",input);
				fclose(file);
				/* copy user input to global variable */
				strcpy(user_string,input);
				/* send SIGUSR1 to task "name" */
				found_pids_by_name_send_signal(name,1);
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

/* catch SIGUSR1 */
void catch_usr1(int num)
{
	char string[BUFFORSIZE+1];
	FILE *readfile;	
	readfile=NULL;
	char *line = NULL;
	size_t len = 0;
	ssize_t s_read;	
	/* reading lines from "name" task */
	readfile = fopen("/tmp/rinbuffor","r");
	if (readfile == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	} else {
		while ((s_read = getline(&line, &len, readfile)) != -1) 
		{
			//printf("%s",line);
		}
		printf("\n");
		/* compare readed data with input data */
		strcpy(string,line);
		if (strcmp (user_string,string) == 0)
		{
			printf("Jupi!\n");
		}
		else
		{
			printf("WTF? \"%s\" != \"%s\"\n",user_string,line);
		}
		
		
		printf("Closing files\n");
		fclose(readfile);
	}
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
