#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

bool flag[2] = {false, false};
int turn;

static void *peterson(void *arg)
{
  int n = *(int *)arg;

  assert(n==0 || n==1); /* somente 2 threads */

  flag[0] = true;
  turn = n;
  while (flag[n] && turn==n) {/* espera */}
  
  /* secao critica */
  
  flag[n] = false;
  
  return NULL;
}

int main(int argc, char**argv)
{
  int thread_args[2] = {0, 1};
  pthread_t threads[2];
  int i;
  
  for (i=0; i<2; i++)
    pthread_create(&threads[i], NULL, 
		   &nop, &thread_args[i]);

  for (i=0; i<2; i++)
    pthread_join(threads[i], NULL);
  
}

