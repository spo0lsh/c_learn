#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *MojaFunkcjaDlaWatku1(void *arg) {
        int i;
        for ( i=0; i<20; i++ ) {
                printf("Watek1 mowi czesc!\n");
                sleep(1);
        }
        return NULL;
}
void *MojaFunkcjaDlaWatku2(void *arg) {
        int i;
        for ( i=0; i<20; i++ ) {
                printf("Watek2 mowi czesc!\n");
                sleep(1);
        }
        return NULL;
}

int main(void) {

  pthread_t mojwatek1;
  pthread_t mojwatek2;

  if ( pthread_create( &mojwatek1, NULL, MojaFunkcjaDlaWatku1, NULL) ) {
        printf("blad przy tworzeniu watku\n"); abort();
  }
  if ( pthread_create( &mojwatek2, NULL, MojaFunkcjaDlaWatku2, NULL) ) {
        printf("blad przy tworzeniu watku\n"); abort();
  }
  if ( pthread_join ( mojwatek1, NULL ) ) {
        printf("blad przy tworzeniu watku\n");
        abort();
  }
  if ( pthread_join ( mojwatek2, NULL ) ) {
        printf("blad przy tworzeniu watku\n");
        abort();
  }
  exit(0);

}
