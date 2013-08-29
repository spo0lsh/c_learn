#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>  /* for signal() */
#include <string.h>

int killpids(char *,int ); // send signal to name
void catch_usr1(int ); // for SIGUSR1
char userstring[256+1];

int main()
{
	char *name="read";
	char input[256+1];
	char ch;
	FILE *file;	

	while(1)
	{
		signal(SIGUSR1, catch_usr1);
		printf("(W)rite\n");
		printf("(Q)uit\n");
		scanf("%s", &ch);
		switch(ch)
		{
			case 'W': // send "stop" signal, read 256 chars, write it do /dev/
				printf("Input string: ");
				scanf("%256s", input);
				file = fopen("/dev/ringbuffor","w");
				if (file == NULL)
				{
					printf("Error opening file!\n");
					exit(1);
				}
				fprintf(file,"%s",input);
				fclose(file);
				strcpy(userstring,input);
				killpids(name,1); // writing finished
			break;
			
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

void catch_usr1(int num)
{
	char string[256+1];
	FILE *readfile;	
	readfile=NULL; // fixed
	char *line = NULL;
	size_t len = 0;
	ssize_t s_read;	
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
		strcpy(string,line);
		if (strcmp (userstring,string) == 0)
		{
			printf("Jupi!\n");
		}
		else
		{
			printf("WTF? \"%s\" != \"%s\"\n",userstring,line);
		}
		
		
		printf("Closing files\n");
		fclose(readfile);
	}
}

// found pids by name and send signal
int killpids(char * name,int num)
{
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
					}
				}
				fclose(cmdline);
			}
		}
		
		closedir(dir);
	}

	return 0;
}
