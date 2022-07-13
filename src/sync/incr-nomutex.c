#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/**
 * Incrementa de modo incorreto a variável global a partir de 2 threads.
 * Fonte: "The Linux Programming Interface". Michael Kerrisk. O'Reilly, 2010,
 */

static int glob=0;

static void *incr(void*);

int main(int argc, char *argv[])
{
  pthread_t t1, t2;
  int loops, ret;
  
  loops = (argc>1) ? atoi(argv[1]) : 10000000;
  
  ret = pthread_create(&t1, NULL, incr, &loops);
  if (ret!=0) {
    perror("pthread_create");
    exit(-1);
  }
  
  ret = pthread_create(&t2, NULL, incr, &loops);
  if (ret!=0) {
    perror("pthread_create");
    exit(-1);
  }

  ret = pthread_join(t1, NULL);
  if (ret!=0) {
    perror("pthread_join");
    exit(-1);
  }

  ret = pthread_join(t2, NULL);
  if (ret!=0) {
    perror("pthread_join");
    exit(-1);
  }
  
  printf("glob=%d\n", glob);
  exit(EXIT_SUCCESS);
}


static void *incr(void *arg)
{
  int loops = *((int *)arg);
  int loc, i;

  for (i=0; i<loops; i++) {
    loc = glob;
    loc++;
    glob = loc;
  }
  return NULL;
}
