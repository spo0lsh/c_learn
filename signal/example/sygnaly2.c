/* ignorowanie sygna�u SIGINT
 */
#include <signal.h>
#include <stdio.h>

main() {
  static struct sigaction act;

  // ustaw dzia�anie podejmowane po odebraniu SIGINT 
  // tym razem ignorujemy sygna�
  act.sa_handler = SIG_IGN;

  sigaction(SIGINT, &act, NULL);

  printf("\nCtrl+c nie dzia�a: .");
  sleep(1);
  printf(" .");
  sleep(1);
  printf(" .");
  sleep(1);
  printf(" .\n");
  sleep(1);

  // przywracamy standardowe dzia�anie
  act.sa_handler = SIG_DFL;

  sigaction(SIGINT, &act, NULL);

  printf("\nCtrl+c dzia�a ponownie\n");
  
  printf(" --- KONIEC --- \n");
  exit(0);
}
