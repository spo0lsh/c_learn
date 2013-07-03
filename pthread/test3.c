#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int mojazmiennaglobalna=0;

void *MojaFunkcjaDlaWatku(void *arg) {
        int i,j;
        for ( i=0; i<20; i++ ) {
                j=mojazmiennaglobalna;
                j=j+1;
                printf(".");
                fflush(stdout);
                sleep(1);
                mojazmiennaglobalna=j;
        }
        return NULL;
}

int main(void) {

  pthread_t mojwatek;
  int i;

  if ( pthread_create( &mojwatek, NULL, MojaFunkcjaDlaWatku, NULL) ) {
        printf("błąd przy tworzeniu Watku.");
        abort();
  }

  for ( i=0; i<20; i++) {
        mojazmiennaglobalna=mojazmiennaglobalna+1;
        printf("o");
        fflush(stdout);
        sleep(1);
  }

  if ( pthread_join ( mojwatek, NULL ) ) {
        printf("błąd przy kończeniu Watku.");
        abort();
  }

  printf("\nMoja zmienna globalna wynosi %d\n",mojazmiennaglobalna);

  exit(0);

}
