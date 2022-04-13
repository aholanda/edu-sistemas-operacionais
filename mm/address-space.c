#include <stdlib.h>

#define N 2048 /* tamanho do vetor */ 
int glob[N];
int *gloc = NULL;

int loop()
{
	int i;
	int loc[N];

	for (i = 0; i< N; i++) {
		glob[i] = i, gloc[i] = i; loc[i] = i;
	}

	loc[0] = 1; /* para acalmar o compilador */

	while(1) ;

	return loc[0];
}

int main(int argc, char**argv)
{
	gloc = malloc(N*sizeof(int));

	loop();

	free(gloc);
	
	return 0;
}
