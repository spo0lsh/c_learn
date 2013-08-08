#include <stdio.h>   /* standard lib */
#include <signal.h>  /* for signal() */

void catch_signal(int signal_number)
{
	printf("Catch signal: SIGINT\n");
}

int main()
{
	printf("Waiting for CTRL+c\n");
	signal(SIGINT, catch_signal);
	printf("Quit\n");
	return(0);
}
