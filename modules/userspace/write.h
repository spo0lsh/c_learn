#ifndef __write_H
#define __write_H

#define BUFFORSIZE 256

/* found pids by name and send signal */
int found_pids_by_name_send_signal(char *,int );
/* catch signal SIGUSR1 */
void catch_usr1(int );

#endif /* __write_H */
