#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *MojaFunkcjaDlaWatku(void *arg) {
        int i;
        for ( i=0; i<20; i++ ) {
                printf("Watek mowi czesc!\n");
                sleep(1);
        }
        return NULL;
}

int main(void) {

  pthread_t mojwatek;

  if ( pthread_create( &mojwatek, NULL, MojaFunkcjaDlaWatku, NULL) ) {
        printf("blad przy tworzeniu watku\n"); abort();
  }

  if ( pthread_join ( mojwatek, NULL ) ) {
        printf("blad przy tworzeniu watku\n");
        abort();
  }
  exit(0);

}
