/* przyk�ad u�ycia funkcji kill do synchronizacji proces�w
 */
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int ntimes = 0;

void p_action(int sig) {
  printf("(%d) Rodzic  otrzyma� sygna� #%d\n", ++ntimes, sig);
}

void c_action(int sig) {
  printf("(%d) Potomek otrzyma� sygna� #%d\n", ++ntimes, sig);
}

main() {
  pid_t pid, ppid;
  
  static struct sigaction pact, cact;

  // ustaw dzia�anie SIGUSR1 dla rodzica
  pact.sa_handler = p_action;
  sigaction(SIGUSR1, &pact, NULL);

  switch(pid = fork()) {
  case -1: // b��d
    perror("*(%^$#^&#*$(%");
    exit(1);
  case 0: // potomek
    // ustaw dzia�anie SIGUSR1 dla potomka
    cact.sa_handler = c_action;
    sigaction(SIGUSR1, &cact, NULL);

    // pobierz PID rodzica
    ppid = getppid();

    // p�tla bez ko�ca
    for( ; ; ) {
      sleep(1);
      kill(ppid, SIGUSR1);
      pause();
    }
  default: // rodzic
    // tylko p�tla
    for( ; ; ) {
      pause();
      sleep(1);
      kill(pid, SIGUSR1);
    }
  }
}
