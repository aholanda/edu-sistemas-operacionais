#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int n=0;
int spin=0;

#define LOCK
#ifdef LOCK
// Não evita concorrência de processadores
#define BLOQUEIA() do {			\
    while (spin != 0) ;			\
    spin = 1; 				\
} while(0)

#define LIBERA() spin=0
#else
#define BLOQUEIA() ;
#define LIBERA() ;
#endif

void *fn() {
  int i;

  BLOQUEIA();
  for (i=0; i<100000000; i++) {
    n++; 
  }
  printf("%d\n", n);
  LIBERA();
}

int main(int argc, char**argv) {
  pthread_t t1, t2;

  if (pthread_create(&t1, NULL, &fn, NULL) != 0)
    exit(1);

  if (pthread_create(&t2, NULL, &fn, NULL) != 0)
    exit(2);

  if (pthread_join(t1, NULL) != 0)
    exit(3);

  if (pthread_join(t2, NULL) != 0)
    exit(4);
  
  return 0;
}
