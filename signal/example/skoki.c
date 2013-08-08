/* przyk³ad u¿ycia sigsetjmp i siglongjmp
 */

#include <sys/types.h>
#include <signal.h>
#include <setjmp.h>
#include <stdio.h>

sigjmp_buf pozycja;

void goback(int signo) {
  fprintf(stderr, "\nPRZERWANIE\n");
  // powrót do zachowanej pozycji
  siglongjmp(pozycja, 1);
}

main() {
  static struct sigaction act;
  
  printf("Przed zachowaniem pozycji\n");

  // zachowaj pozycjê
  if(sigsetjmp(pozycja, 1) == 0)  { // je¿eli powrót nie z siglongjmp
    act.sa_handler = goback;
    sigaction(SIGINT, &act, NULL);
  }

  printf("Ju¿ po ... \n");
  sleep(5);
  printf("--- KONIEC ---\n");  
}
