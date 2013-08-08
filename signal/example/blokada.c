/* blokowanie sygna³ów
 */
#include <signal.h>
#include <stdio.h>

main() {
  sigset_t set1, set2;

  // wype³nij ca³kowicie zestaw sygna³ów
  sigfillset(&set1);

  // zbiór bez SIGINT i SIGQUIT
  sigfillset(&set2);
  sigdelset(&set2, SIGINT);
  sigdelset(&set2, SIGQUIT);

  printf("\nWykonanie kodu NIEkrytycznego\n");
  sleep(2);

  // ustaw blokadê
  sigprocmask(SIG_SETMASK, &set1, NULL);

  printf("\nWykonanie WYJ¡TKOWO krytycznego kodu\n");
  sleep(2);

  // ustaw mniejsz± blokadê 
  // odbierane wszystkie sygna³y bez SIGINT i SIGQUIT
  sigprocmask(SIG_UNBLOCK, &set2, NULL);

  printf("\nWykonanie MNIEJ krytycznego kodu\n");
  sleep(2);

  // usuñ wszystkie blokady
  sigprocmask(SIG_UNBLOCK, &set1, NULL);

}
