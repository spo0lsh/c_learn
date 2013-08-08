/* przechwytywanie sygna³u SIGINT
 */
#include <signal.h>
#include <stdio.h>

/* trywialna funkcja do obs³ugi SIGINT
 */
void catchint(int signo) {
  printf("\n Obs³uga sygna³u o numerze: %d\n", signo);
}

main() {
  static struct sigaction act;

  // ustaw dzia³anie podejmowane po odebraniu SIGINT 
  act.sa_handler = catchint;

  // utwórz pe³n± maskê
  sigfillset(&(act.sa_mask));

  // nowa obs³uga sygna³u SIGINT dopiero po 
  // wywo³aniu nastêpuj±cej funkcji
  sigaction(SIGINT, &act, NULL);
  // po otrzymaniu SIGINT sterowanie bêdzie przekazane do catchint

  printf("\n¦piê: .");
  sleep(1);
  printf(" .");
  sleep(1);
  printf(" .");
  sleep(1);
  printf(" .");
  sleep(1);

  printf("\n");
  
  printf(" --- KONIEC --- \n");
  exit(0);
}
