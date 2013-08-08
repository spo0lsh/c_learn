/* zastosowanie alarmu do wymuszania odpowiedzi od u¿ytkownika
 */

#include <stdio.h>
#include <signal.h>

#define TIMEOUT    5  /* w sekundach */
#define MAXTRIES   5
#define LINESIZE   100
#define CTRL_G     '\007' /* sygna³ d¼wiêkowy ASCII */
#define TRUE       1
#define FALSE      0

// sprawdza czy min±³ czas oczekiwania
static int timed_out;

// zawiera liniê wej¶ciow± 
static char answer[LINESIZE];

char *quickreplay(char *prompt) {
  void catch(int);
  int  ntries;
  static struct sigaction act, oact;

  // przychwyæ SIGALRM + zachowaj poprzednie dzia³ania
  act.sa_handler = catch;
  sigaction(SIGALRM, &act, &oact);

  for(ntries=0; ntries<MAXTRIES; ntries++) {
    timed_out = FALSE;
    printf("\n%s > ", prompt);
    
    // ustaw zegar alarmu
    alarm(TIMEOUT);
    
    // pobierz liniê
    gets(answer);
    
    // wy³±cz alarm
    alarm(0);
    // je¿eli time_out==TRUE, to nie ma odpowiedzi
    if(!timed_out) 
      break;
  }
  //przywróæ stare dzia³anie
  sigaction(SIGALRM, &oact, NULL);

  // zwróæ odpowiedni± warto¶æ
  return (ntries == MAXTRIES ? ((char *)0) : answer);
}

// wykonaj SIGALRM, gdy odebrany
void catch(int sig) {
  timed_out = TRUE; // przekroczenie czasu
  putchar(CTRL_G);   // piszcz
}

main () {
  // testujemy
  printf("\n\n%s\n\n", quickreplay("podaj co¶"));

}
