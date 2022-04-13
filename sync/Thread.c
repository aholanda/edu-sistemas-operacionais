/**
 * This program creates a separate thread using the CreateThread() system call.
 *
 * Figure 4.10
 *
 * @author Gagne, Galvin, Silberschatz
 * Operating System Concepts with Java - Eighth Edition
 * Copyright John Wiley & Sons - 2010.
 */

#include <stdio.h>
#include <windows.h>


DWORD Soma; /* dados compartilhados pela(s) thread(s) */

/* a thread executa nesta funcao separada */
DWORD WINAPI Somatorio(PVOID Param)
{
	DWORD Upper = *(DWORD *)Param;

    DWORD i;
    
	for (i = 0; i <= Upper; i++)
		Soma += i;



	return 0;
}


int main(int argc, char *argv[])
{
	DWORD ThreadId;
	HANDLE ThreadHandle;
	int Param;
    char line[128]; // usado somente para segurar a saida padrao

	// do some basic error checking
	if (argc != 2) {
		fprintf(stderr,"Um parametro inteiro e requisitado\n");
		return -1;
	}

	Param = atoi(argv[1]);

	if (Param < 0) {
		fprintf(stderr, "um inteiro >= 0 e requisitado \n");
		return -1;
	}

	// create the thread
	ThreadHandle = CreateThread(
                 NULL, // atributos de segurança default
                 0, // tamanho de pilha default
                 Somatorio, // funcao thread
                 &Param, // parametro para a funcao thread
                 0, // flag de criacao default
                 &ThreadId // retorna o identificador da thread
                 );

	if (ThreadHandle != NULL) {
		WaitForSingleObject(ThreadHandle, INFINITE);
		CloseHandle(ThreadHandle);
		printf("Soma = %d\n",Soma);
	}
	gets(line); // adicionado para ver o resultado
}
