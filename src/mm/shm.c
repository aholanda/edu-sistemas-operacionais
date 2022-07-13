#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>



/**
 * Programa para testar a diferenca entre o acesso via mmap
 * e via arquivo.
 * Criar um arquivo com tamanho len:
 * $ fallocate -l 300-1000M /tmp/file.img
 *
 * Testar usando time
 */

static const char *fn = "/tmp/file.img" ;
static int i;

static void readmmap();
static void readfile();

int main(int argc, char*argv[])
{
  int i;
  int opt;

  if (argc!=2) {
  error:    printf("usage: %s 1 | 2 # 1 => mmap, 2 => file\n", argv[0]);
    exit(-1);
  }
  opt = atoi(argv[1]); /* converte para inteiro */
  
  if (opt==1)
    readmmap();
  else if (opt==2)
    readfile();
  else
    goto error;

    return 0;

}

static void readmmap()
{
  off_t len; /* tamanho da regiao de memoria */
  int fd; /* file descriptor */
  char *addr; /* ponteiro para a memoria mapeada */
  struct stat sb;

  fd = open(fn, O_RDONLY);
  if (fd==-1) {
    fprintf(stderr, "Could not open %s\n", fn);
    exit(-1);
  }

  /* extrai informacoes do arquivo */
  if (fstat(fd, &sb)==-1) {
    perror("fstat");
    exit(-1);
  }

  addr = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
  if (addr==MAP_FAILED) {
    perror("mmap");
    exit(-1);
  }

  madvise(addr, sb.st_size, MADV_SEQUENTIAL);
  
  printf("reading mapped memory %s...", fn);
  for (i=0; i<sb.st_size; i++) {
    printf("%c", addr[i]);
  }

  printf("done");

  if (close(fd)==-1) {
    perror("close");
    exit(-1);
  }
  
  /* encerra o mapeamento */
  if (munmap(addr, sb.st_size)==-1) {
    perror("munmap");
    exit(-1);
  }
}

static void readfile()
{
  FILE *fp;
  char c;

  fp = fopen(fn, "rb");
  if (fp==NULL) {
    fprintf(stderr, "Could not open %s\n", fn);
    exit(-1);
  }
  
  printf("reading file %s...", fn);
  while((c=fgetc(fp))!=EOF)
    printf("%c", c);
  
  printf("done.\n");

  fclose(fp);
}
    
  
