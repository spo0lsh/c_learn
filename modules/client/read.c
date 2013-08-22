#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>  /* for signal() */

int global;
int killpids(char *,int );
void catch_signal(int );
void catch_usr1(int );
void catch_usr2(int );

int main()
{
	char *name="write";
	char output[256+1];
	char ch;
	//int fd = -1;
	FILE *file;	
	
	while(1)
	{
		signal(SIGUSR1, catch_usr1);
		signal(SIGUSR2, catch_usr2);
		printf("(R)ead\n");
		printf("(Q)uit\n");
		scanf("%s", &ch);
		switch(ch)
		{
			case 'R':
				killpids(name,1);
				file = fopen("/dev/ringbuffor","r");
				if (file == NULL)
				{
					printf("Error opening file!\n");
					exit(1);
				}
				printf("The string:\n%s", output);
				while(fscanf(file, "%s", output)!=EOF)
				{
					printf("%s",output);
				}
				printf("\n");
				fclose(file);
				killpids(name,2);
			break;
			
			case 'Q':
				printf("Bye..\n");
				killpids(name,2);
				return(0);
			break;
			
			default:
				printf("What?\n");
			break;
		}
		
	}
	return 0;
}

void catch_signal(int signal_number)
{
	printf("Catch signal: %d\n",signal_number);
}

void catch_usr1(int num)
{
	global=1;
	printf("Stop ...\n");
	while(global)
	{
		
	}
}

void catch_usr2(int num)
{
	printf("Star after stop ...\n");
	global=0;
}

int killpids(char * name,int num)
{
	//printf("name %s %d\n",  name, num);
	
	const char*	directory = "/proc";
	size_t		taskNameSize = 1024; 
	char*		taskName = calloc(1, taskNameSize); // ?!
	
	DIR*		dir = opendir(directory);
	
	
	if(dir) {
		
		struct dirent* de = 0; //?
		
		while ((de = readdir(dir)) != 0)
		{
			if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
			{
				continue;
			}
			int pid = -1;
			int res = sscanf(de->d_name, "%d", &pid);
			if (res == 1)
			{
				char cmdline_file[1024] = {0};
				sprintf(cmdline_file, "%s/%d/cmdline", directory, pid);
				FILE* cmdline = fopen(cmdline_file, "r"); // open file (from sprintf)
				if (getline(&taskName, &taskNameSize, cmdline) > 0)
				{
					if (strstr(taskName, name) != 0)
					{
						fprintf(stdout, "A %s process, with PID %d, has been detected.\n", name, pid);
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
						//kill(pid,SIGUSR1);
						//kill(pid,SIGUSR2);
					}
				}
				fclose(cmdline);
			}
		}
		
		closedir(dir);
	}

	return 0;
}
