#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>  /* for signal() */

int killpids(char *,int );
void catch_signal(int );



int main()
{
	char *name="write";
	//char *
	killpids(name,1);
	signal(SIGUSR1, catch_signal);
	signal(SIGUSR2, catch_signal);
	return 0;
}

void catch_signal(int signal_number)
{
	printf("Catch signal: %d\n",signal_number);
}

int killpids(char * name,int num)
{
	printf("name %s %d\n",  name, num);
	
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
