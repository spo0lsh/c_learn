
// int kill(pid_t pid, int sig);

#include <unistd.h>
#include <stdio.h>

int main(void)
{
   printf("My process ID : %d\n", getpid());
   printf("My parent's ID: %d\n", getppid());

   return 0;
}

