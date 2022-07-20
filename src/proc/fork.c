#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Mostra a duplicação do espaço de endereçamento
void fork1() {
  int n=0, i;
  pid_t pid; // inteiro
  char *w;

  pid = fork();
  if (pid == 0) { // filho
    w = "filho";
    printf("&n=%p,n=%d\n", &n, n);
    n = 1;
    printf("&n=%p,n=%d\n", &n, n);
  } else { // pai
    w = "pai";
    printf("&n=%p,n=%d\n", &n, n);
    n = 6;
    printf("&n=%p,n=%d\n", &n, n);
    wait(NULL);
  }

  printf("%s: ", w);
  for (i=n; i<n+5; i++)
    printf("%d ", i);
  printf("\n");
}

// Mostra os passos para a criação de um processo
void fork0() {
  pid_t pid;

  /* fork para o processo filho */
  pid = fork();
  if (pid < 0) { /* erro */
    fprintf(stderr, "Fork falhou\n");
    exit(1);
  } else if (pid == 0) { /* processo filho */
    printf("proc-filho: pid=%d\n",pid);
    execlp("/bin/ls","-l", NULL);
  } else { /* processo pai */
    /* papai espera o filho terminar o servico */
    printf("proc-pai: pid=%d\n",pid);
    wait(NULL);
    printf("proc-filho terminou\n");
  }
}

int main(int argc, char**argv) {
  if (argc == 1)
    fork0();
  else
    fork1();

  return 0;
}
