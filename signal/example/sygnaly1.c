/* przechwytywanie sygna�u SIGINT
 */
#include <signal.h>
#include <stdio.h>

/* trywialna funkcja do obs�ugi SIGINT
 */
void catchint(int signo) {
  printf("\n Obs�uga sygna�u o numerze: %d\n", signo);
}

main() {
  static struct sigaction act;

  // ustaw dzia�anie podejmowane po odebraniu SIGINT 
  act.sa_handler = catchint;

  // utw�rz pe�n� mask�
  sigfillset(&(act.sa_mask));

  // nowa obs�uga sygna�u SIGINT dopiero po 
  // wywo�aniu nast�puj�cej funkcji
  sigaction(SIGINT, &act, NULL);
  // po otrzymaniu SIGINT sterowanie b�dzie przekazane do catchint

  printf("\n�pi�: .");
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
