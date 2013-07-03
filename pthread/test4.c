#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int mojazmiennaglobalna;
pthread_mutex_t mojmuteks=PTHREAD_MUTEX_INITIALIZER;

void *MojaFunkcjaDlaWatku(void *arg) {
  int i,j;
  for ( i=0; i<20; i++ ) {
    pthread_mutex_lock(&mojmuteks);
    j=mojazmiennaglobalna;
    j=j+1;
    printf(".");
    fflush(stdout);
   sleep(1);
    mojazmiennaglobalna=j;
    pthread_mutex_unlock(&mojmuteks);
  }
  return NULL;
}

int main(void) {

  pthread_t mojwatek;
  int i;

  if ( pthread_create( &mojwatek, NULL, MojaFunkcjaDlaWatku, NULL) ) {
    printf("błąd przy tworzeniu Watka.");
    abort();
  }

  for ( i=0; i<20; i++) {
    pthread_mutex_lock(&mojmuteks);
    mojazmiennaglobalna=mojazmiennaglobalna+1;
    pthread_mutex_unlock(&mojmuteks);
    printf("o");
    fflush(stdout);
    sleep(1);
  }

  if ( pthread_join ( mojwatek, NULL ) ) {
    printf("błąd przy kończeniu Watka.");
    abort();
  }

  printf("\nWartość mojej zmiennej globalnej to %d\n",mojazmiennaglobalna);

  exit(0);

}
