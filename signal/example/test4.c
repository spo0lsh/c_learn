#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
   if (argc < 2)
   {
      fprintf(stderr, "Usage: %s <process name>\n", argv[0]);
      return 1;
   }

   const char* directory = "/proc";
   size_t      taskNameSize = 1024;
   char*       taskName = calloc(1, taskNameSize);

   DIR* dir = opendir(directory);

   if (dir)
   {
      struct dirent* de = 0;

      while ((de = readdir(dir)) != 0)
      {
         if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
            continue;

         int pid = -1;
         int res = sscanf(de->d_name, "%d", &pid);

         if (res == 1)
         {
            // we have a valid pid

            // open the cmdline file to determine what's the name of the process running
            char cmdline_file[1024] = {0};
            sprintf(cmdline_file, "%s/%d/cmdline", directory, pid);

            FILE* cmdline = fopen(cmdline_file, "r");

            if (getline(&taskName, &taskNameSize, cmdline) > 0)
            {
               // is it the process we care about?
               if (strstr(taskName, argv[1]) != 0)
               {
                  fprintf(stdout, "A %s process, with PID %d, has been detected.\n", argv[1], pid);
               }
            }

            fclose(cmdline);
         }
      }

      closedir(dir);
   }

   // just let the OS free this process' memory!
   //free(taskName);

   return 0;
}
