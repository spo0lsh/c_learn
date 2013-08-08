/* przywracanie poprzedniego dzia³ania
 */
#include <signal.h>
#include <stdio.h>

void catchint(int signo) {
  printf("*");
}

main() {
  static struct sigaction act, oact;

  // zachowaj dotychczasowe dzia³anie SIGINT
  sigaction(SIGINT, NULL, &oact);

  // ustaw nowe dzia³anie
  act.sa_handler = catchint;

  sigaction(SIGINT, &act, NULL);

  printf("\nNowe dzia³anie: .");
  sleep(1);
  printf(" .");
  sleep(1);
  printf(" .");
  sleep(1);
  printf(" .\n");
  sleep(1);

  // przywracamy stare dzia³anie
  sigaction(SIGINT, &oact, NULL);

  printf("\nPonownie stare dzia³anie: .");
  sleep(1);
  printf(" .");
  sleep(1);
  printf(" .");
  sleep(1);
  printf(" .\n");
  sleep(1);
  
  printf(" --- KONIEC --- \n");
  exit(0);
}
