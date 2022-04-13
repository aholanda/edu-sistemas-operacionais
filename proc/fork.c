/**
 * Programa adaptado do livro "Sistemas Operacionais com
 * Java" (7ed, pg 72) de Silberschatz, Galvin e Gagne.
 */
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char**argv) {
	pid_t pid;

	/* fork para o processo filho */
	pid = fork();
	if (pid < 0) { /* erro */
	  fprintf(stderr, "Fork falhou\n");
	  exit(1);
	} else if (pid == 0) { /* processo filho */
		printf("Eu sou o processo filho com pid=%d\n",pid);
		execlp("/bin/ls","ls",NULL);
	} else { /* processo pai */
		/* papai espera o filho terminar o servico */
		printf("Eu sou o pai com pid=%d\n",pid);
		wait(NULL);
		printf("O filho terminou o servico\n");
	}
	return 0;
}
