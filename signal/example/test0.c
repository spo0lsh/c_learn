
#include <stdio.h>           /* standardowe funkcje wejścia/wyjścia */
#include <unistd.h>        /* standardowe funkcje Unixowe, jak getpid() */
#include <sys/types.h> /* różne typy definicji, jak np. pid_t */
#include <signal.h>        /* nazwy sygnałów, makra i prototyp funkcji signal() */
/* na początek, tutaj znajduje sie funkcja uchwytu sygnału */
void zlapalem(int sig_num)
{
/* ponowne ustawienie uchwytu sygnału na 'zlapalem' */
 signal(SIGINT, zlapalem);
/* wypisanie wiadomości */
 printf("Nie dam sie zamknąć !");
 fflush(stdout);
}


int main() {
/* Troszke niżej w kodzie.... */
/* Ustaw uchwyt sygnału INT ( Ctrl + C ) do funkcji 'zlapalem' */
signal(SIGINT, zlapalem);
/* Wskakuje do nieskończonej pętli, by nic nei robic- czekac na Ctrl + C */
for ( ;; )
pause();

return(0);
}
