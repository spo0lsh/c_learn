/* blokowanie sygna��w
 */
#include <signal.h>
#include <stdio.h>

main() {
  sigset_t set1, set2;

  // wype�nij ca�kowicie zestaw sygna��w
  sigfillset(&set1);

  // zbi�r bez SIGINT i SIGQUIT
  sigfillset(&set2);
  sigdelset(&set2, SIGINT);
  sigdelset(&set2, SIGQUIT);

  printf("\nWykonanie kodu NIEkrytycznego\n");
  sleep(2);

  // ustaw blokad�
  sigprocmask(SIG_SETMASK, &set1, NULL);

  printf("\nWykonanie WYJ�TKOWO krytycznego kodu\n");
  sleep(2);

  // ustaw mniejsz� blokad� 
  // odbierane wszystkie sygna�y bez SIGINT i SIGQUIT
  sigprocmask(SIG_UNBLOCK, &set2, NULL);

  printf("\nWykonanie MNIEJ krytycznego kodu\n");
  sleep(2);

  // usu� wszystkie blokady
  sigprocmask(SIG_UNBLOCK, &set1, NULL);

}
