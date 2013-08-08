/* tml -- program "tell-me-later
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>


#define BELL      '\007' /* sygna³ d¼wiêkowy ASCII */
#define TRUE       1
#define FALSE      0

int alarm_flag = FALSE;

// procedura obs³ugi SIGALRM
void setflag(int sig) {
  alarm_flag = TRUE;
}

main(int argc, char **argv) {
  int nsecs, j;
  pid_t pid;
  static struct sigaction act;

  if( argc<=2 ) {
    fprintf(stderr, "U¿ycie: tml #sekund tekst\n");
    exit(1);
  }
  if( (nsecs = atoi(argv[1])) <=0 ) {
    fprintf(stderr, "tml: nieprawid³owy czas\n");
    exit(2);
  }
  // utwórz proces w tle
  switch(pid = fork()) {
  case -1: // b³±d
    perror("tml: *(%^$#^&#*$(%");
    exit(1);
  case 0: // potomek
    break;
  default:
    printf("tml: PID %d\n", pid);
    exit(0);
  }
  // ustaw dzia³anie alarmu
  act.sa_handler = setflag;
  sigaction(SIGALRM, &act, NULL);

  // w³±cz zegar alarmu
  alarm(nsecs);
  
  // pauza do sygna³u
  pause();

  // je¿eli SIGALRM, to drukuj komunikat
  if(alarm_flag == TRUE) {
    printf("%c",BELL);
    for(j=2; j < argc; j++)
      printf("%s", argv[j]);
    printf("\n");
  }
  exit(0);
}
