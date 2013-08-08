/* przywracanie poprzedniego dzia�ania
 */
#include <signal.h>
#include <stdio.h>

void catchint(int signo) {
  printf("*");
}

main() {
  static struct sigaction act, oact;

  // zachowaj dotychczasowe dzia�anie SIGINT
  sigaction(SIGINT, NULL, &oact);

  // ustaw nowe dzia�anie
  act.sa_handler = catchint;

  sigaction(SIGINT, &act, NULL);

  printf("\nNowe dzia�anie: .");
  sleep(1);
  printf(" .");
  sleep(1);
  printf(" .");
  sleep(1);
  printf(" .\n");
  sleep(1);

  // przywracamy stare dzia�anie
  sigaction(SIGINT, &oact, NULL);

  printf("\nPonownie stare dzia�anie: .");
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
