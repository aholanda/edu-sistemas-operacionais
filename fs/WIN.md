# Windows: sistema de arquivos NTFS

Para entender os conceitos apresentados ao longo do texto precisaremos 
do seguinte programa:

* [WinObj](https://download.sysinternals.com/files/WinObj.zip);
* [Sysinternals suite](https://download.sysinternals.com/files/SysinternalsSuite.zip).

## Lista de sistemas de arquivos registrados

Para visualizar os sistemas de arquivos registrados:

* Executar o `WinObj` localizar o diretório `\FileSystem`.  Executar o
* `Msinfo32` na caixa de diálogo `Iniciar->Executar`, e localizar o
  diretório `Ambiente de software->Drivers do sistema` e filtrar por
  `Driver do sistema de arquivo` na coluna `Tipo`.

## Múltiplos fluxos (*streams*) de dados

O NTFS permite múltiplos *streams* de dados, como podemos através da
série de comandos a seguir executados no prompt de comandos:

`````
C:\>echo hello >foo:stream0
C:\>echo alo >foo:stream1
C:\>more <foo:stream0
hello

C:\>more <foo:stream1
alo

````

Se for feita uma listagem do conteúdo do diretório, o espaço ocupado
pelos *streams* não será mostrado, pois o NTFS só lista o espaço
ocupados pelos *streams* sem nome. 

````
C:\>dir foo
````

Para visualizá-los, o comando `streams` da suite *Sysinternals* ou
`dir /r` deverão ser executados:

````
C:\>streams foo
````

Os múltiplos *streams* podem ser usados, por exemplo, por uma
aplicação de backup que em um *stream* armazena os arquivos
compactados e em outro armazena informações de data e hora das
operações de backup.

## *Hard link*

Um *hard link* permite que vários caminhos apontem para o mesmo
arquivo, não diretórios. Através da série de comandos a seguir,
criamos um arquivo chamado `mar.txt` com a string `hello` como
conteúdo e criamos um *hard link* chamado `lar.txt` apontando para
`bar.txt` usando o comando `fsutil hardlink`:

````
C:\>echo hello >mar.txt
C:\>fsutil hardlink create lar.txt mar.txt
````

Ao listar o conteúdo do diretório, os dois arquivos vai possuir 
a mesma quantidade de bytes, atributos e permissões.

## Cota de disco

O NTFS permite o gerenciamento de limitação de espaço em disco
acessado via `Propriedades->Cota` do volume que se deseja ativar o
gerenciamento de cotas.

## Estrutura do NTFS

Um **volume** é uma partição lógica no disco e é criado quando o disco
é formatado. Um volume é dividido em **clusters** que é formado por
setores físicos, sempre em potência de 2. O **fator** de *cluster* é
um número expresso em bytes, como por exemplo, 512 bytes, 1KB, 2KB, e
assim por diante.

O NTFS refere-se à localização física no disco por meio do **número
lógico do cluster** (LCN-*logical cluster number*). Para saber o
endereço físico no disco o NTFS multiplica o LCN pelo fator do
*cluster*. O NTFS refere-se ao dado dentro do arquivo por meio do
**número virtual do cluster** (VCN-*virtual cluster number*). Os 
VCNs não precisar estar localizados de forma contígua.

### Tabela mestre de arquivos

A **tabela mestre de arquivos** (MFT-*Master File Table*) armazena os
metadados dos arquivos no volume, sendo implementada como um vetor de
registros de arquivos de 1K cada. Os atributos armazenados na MFT
começam com `$`, e normalmente, cada MFT corresponde a um arquivo
diferente.

As informações sobre o NTFS do volume `C:` podem ser visualizadas pelo
comando:

````
C\:>fsutil fsinfo ntfsinfo C:
````
## Arquivo de registro de alterações

O arquivo de registro de alterações (*change journal file*) é um
 arquivo disperso em que o NTFS armazena as alterações nos arquivos e
 diretórios. Se este arquivo ainda não existir, pode ser criado usando o 
 comando

````
C\:>fsutil usn createjournal m=1000 a=100 c:
````

onde `m` é o número máximo de entradas e `a` a tolerância após `m` ser
atingido.

As informações sobre os registros podem ser obtidas usando o comando

````
C\:>fsutil usn queryjournal c:
````

As entradas do registro de alterações pode ser visualizada usando o
 programa
 [`Usndump.exe`](http://www.winsiderss.com/tools/usndump/usndump.htm). No
 exemplo a seguir, é criado um arquivo chamado `usn.txt`, e este mesmo
 arquivo renomeado para `usn-1.txt`, e executando `Usndump.exe`, as
 alterações podem ser visualizadas:

````
C\:>echo foobar >usn.txt
C\:>ren usn.txt usn-1.txt
C:\>Usndump.exe
````

## Referência

1. [Windows Internals, Part 2 (6th Edition) (Developer Reference)](http://goo.gl/HIar8d). Microsoft Press, 2012.
