#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int N=20000000; // limit
int n=0; // global counter
int spin=0; // loop or not to loop?
int locked = 0; // use spin lock?

int test_and_set(int *m);

#define LOCK() do {				\
  if (!locked) break;				\
  while (test_and_set(&spin) != 0) /* spin */;	\
} while(0)
#define UNLOCK() spin=0

// A hardware instruction must be used to implement test-and-set
// mechanism. Here test-and-set is emulated for educational
// purposes. Sometimes in the execution the halt will not occur.
int test_and_set(int *m) {
  int old = *m;
  *m = 1;
  printf("%c", 0); // add some delay
  return old;
}

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
