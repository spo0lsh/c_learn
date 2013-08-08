/* ignorowanie sygna³u SIGINT
 */
#include <signal.h>
#include <stdio.h>

main() {
  static struct sigaction act;

  // ustaw dzia³anie podejmowane po odebraniu SIGINT 
  // tym razem ignorujemy sygna³
  act.sa_handler = SIG_IGN;

  sigaction(SIGINT, &act, NULL);

  printf("\nCtrl+c nie dzia³a: .");
  sleep(1);
  printf(" .");
  sleep(1);
  printf(" .");
  sleep(1);
  printf(" .\n");
  sleep(1);

  // przywracamy standardowe dzia³anie
  act.sa_handler = SIG_DFL;

  sigaction(SIGINT, &act, NULL);

  printf("\nCtrl+c dzia³a ponownie\n");
  
  printf(" --- KONIEC --- \n");
  exit(0);
}
