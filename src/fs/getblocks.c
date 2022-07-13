/**
 * Programa para ler tuplas <bloco logico, bloco fisico>
 * de um arquivo especificado pelo usuario
 * Fonte: "Linux System Programming". Robert Love. O'Reilly, 2009.
 *
 * E necessario privilegios de root para roda-lo corretamente.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/fs.h>

/*
 * retorna o endereco fisico de acordo com o logico
 */
int get_block(int fd, int logical_block)
{
  int ret;

  ret = ioctl(fd, FIBMAP, &logical_block);
  if (fd<0) {
    perror("ioctl");
    return -1;
  }
  return logical_block;
}

/*
 * retorna o numero de blocos logicos de fd
 */ 
int get_nblocks(int fd)
{
  struct stat sb;
  int ret;

  ret = fstat(fd, &sb);
  if (ret<0) {
    perror("stat");
    return -1;
  }
  return sb.st_blocks;
}

/*
 * imprime a tupla <bloco logico, bloco fisico>
 */
void print_blocks(int fd)
{
  int nblocks, i;

  nblocks = get_nblocks(fd);
  if (nblocks<0) {
    fprintf(stderr, "get_nblocks failed!\n");
    exit(-1);
  } else
    printf("%d block(s)\n\n", nblocks);

  for (i=0; i<nblocks; i++) {
    register int phys_block = get_block(fd, i);
    if (phys_block<0) {
      fprintf(stderr, "get_block failed!\n");
      exit(-1);
    }
    if (!phys_block)
      continue;

    printf("<%u,%u>\t", i, phys_block);
    putchar('\n');
  }
}

int main(int argc, char**argv)
{
  int fd; /* descritor do arquivo */
  
  if (argc<2) {
    fprintf(stderr, "usage: %s <file>\n", argv[0]);
    exit(-1);
  }
  
  fd = open(argv[1], O_RDONLY);
  if (fd<0) {
    perror("open");
    exit(-1);
  }

  print_blocks(fd);

  close(fd);
  
  return 0;
}
