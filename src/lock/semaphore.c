#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int N=20000000; // limit
int n=0; // global counter
int sema=0; // semaphore variable
int locked = 0; // use semaphore?

// LOCK() must be executed without interruption
#define LOCK() do {					\
  if (!locked) break;					\
  while (sema <= 0) /* wait => P() */;			\
  sema--;						\
} while(0)
#define UNLOCK() sema++

void *fn() {
  int i;

  LOCK();
  for (i=0; i<N; i++) {
    n++; 
  }
  UNLOCK();
  printf("%d\n", n);
}

int main(int argc, char *argv[]) {
  pthread_t t1, t2;

  if (argc > 1)
    locked = atoi(argv[1]);
  else {
    printf("help: %s 0 | 1\n 0 - not locked\n 1 - locked\n",
	   argv[0]);
    exit(1);
  }
  
  if (pthread_create(&t1, NULL, &fn, NULL) != 0)
    exit(2);

  if (pthread_create(&t2, NULL, &fn, NULL) != 0)
    exit(3);

  if (pthread_join(t1, NULL) != 0)
    exit(4);

  if (pthread_join(t2, NULL) != 0)
    exit(5);
  
  return 0;
}
