#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algGenetico.h"

/************************************
*       Estrutura infoArquivo
*   -> Implementada para armazenar em memória as informações provenientes do arquivo.
* 
*   Campos:
*       1. name          =>   NAME: gr24
*       2. type          =>   TYPE: TSP
*       3. comment       =>   COMMENT: 24-city problem (Groetschel)
*       4. dimension     =>   DIMENSION: 24
*       5. edgeType      =>   EDGE_WEIGHT_TYPE: EXPLICIT
*       6. edgeFormat    =>   EDGE_WEIGHT_FORMAT: LOWER_DIAG_ROW 
*       7. edgeSection   =>   EDGE_WEIGHT_SECTION
* 
*   Estrutura escolhida para o armazenamento das distancias foi uma matriz.
* 
*************************************/

struct infoArquivo {
    char *name;
    char *type;
    char *comment;
    int dimension;
    char *edgeType;
    char *edgeFormat;
    char *dataType;
    int **edgeSection;
}; typedef struct infoArquivo infArq;

/************************************
*       Enum Algoritmo
*   -> Implementada no intuito de numerar os possíveis algoritmos, e assim facilitar o entendimento do código.
* 
*   Valores:
*       ALGORITMO_GENETICO = 0,
*       SIMULATED_ANNEALING = 1 
* 
*************************************/

enum Algoritmo {
    ALGORITMO_GENETICO,
    SIMULATED_ANNEALING
};

/* 
* escreveArquivo
*  Responsável por gerar o log de saída do programa
* 
*  método:
*       Escreve um arquivo com nome "arquivo_saida.txt", caso já existe, o arquivo
*       é sobreescrito. Ou seja, caso execute o programa na pasta de que tenha
*       o último log, o resultado do algoritmo será escrito em cima do anterior.
* 
*  Parametros:
*       Solucao *sol -> Ponteiro para a solucao encontrada
*       infArq **cmds -> Ponteiro para estrutura de informações do arquivo 
*       de entrada
*       int algoritmo -> inteiro que representa o algoritmo escolhido pelo usuario
*  
*/

void escreveArquivo( Solucao *sol, infArq **cmds, int algoritmo );

/* 
* atribuindoInfosArquivo
*  Responsável por armazenar em memória as informações do arquivo de entrada
* 
*  método:
*       Recebe o arquivo inputado pelo usuário, e em seguida aloca uma estrutura
*       infArq para guardar toda as informações fornecidas pelo arquivo.
* 
*  Parametros:
*       infArq **cmds -> Ponteiro para estrutura de informações do arquivo 
*       de entrada
*       FILE *f -> Ponteiro para arquivo de entrada enviado pelo usuário
*  
*/

void atribuindoInfosArquivo( infArq **cmds, FILE *f );

/* 
* lowerDiagRow
*  Responsável pelo armazenamento da matriz de distancias em arquivos 
*  de entrada, nos qual os dados do setor edgeSection estão disponibilizados
*  no formato LOWER_DIAG_ROW.
* 
*  método:
*       Recebe um ponteiro para a matriz de distancias a ser preenchida, a
*       dimensão da matriz e o arquivo em que a informação está presente e
*       efetua a leitura do mesmo seguindo a lógica do LOWER_DIAG_ROW.
* 
*  Parametros:
*       int ***edgeSection -> Ponteiro para a matriz de distancias
*       int dimension -> inteiro que represeta a dimensão da matriz
*       FILE *f -> Ponteiro para arquivo de entrada enviado pelo usuário
*  
*/

void lowerDiagRow( int ***edgeSection, int dimension , FILE *f );

/* 
* upperDiagRow
*  Responsável pelo armazenamento da matriz de distancias em arquivos 
*  de entrada, nos qual os dados do setor edgeSection estão disponibilizados
*  no formato UPPER_DIAG_ROW.
* 
*  método:
*       Recebe um ponteiro para a matriz de distancias a ser preenchida, a
*       dimensão da matriz e o arquivo em que a informação está presente e
*       efetua a leitura do mesmo seguindo a lógica do UPPER_DIAG_ROW.
* 
*  Parametros:
*       int ***edgeSection -> Ponteiro para a matriz de distancias
*       int dimension -> inteiro que represeta a dimensão da matriz
*       FILE *f -> Ponteiro para arquivo de entrada enviado pelo usuário
*  
*/

void upperDiagRow( int ***edgeSection, int dimension , FILE *f );

/* 
* upperRow
*  Responsável pelo armazenamento da matriz de distancias em arquivos 
*  de entrada, nos qual os dados do setor edgeSection estão disponibilizados
*  no formato UPPER_ROW.
* 
*  método:
*       Recebe um ponteiro para a matriz de distancias a ser preenchida, a
*       dimensão da matriz e o arquivo em que a informação está presente e
*       efetua a leitura do mesmo seguindo a lógica do UPPER_ROW.
* 
*  Parametros:
*       int ***edgeSection -> Ponteiro para a matriz de distancias
*       int dimension -> inteiro que represeta a dimensão da matriz
*       FILE *f -> Ponteiro para arquivo de entrada enviado pelo usuário
*  
*/

void upperRow( int ***edgeSection, int dimension , FILE *f );

/* 
* alocaMatrizDistancias
*  Responsável por alocar a matriz de distancias
*  
* 
*  método:
*       Recebe o endereço e a dimensão da matriz a ser alocada para criar
*       dinamicamente uma matriz de tamanho específico para cada problema.
* 
*  Parametros:
*       int ***edgeSection -> Ponteiro para a matriz de distancias
*       int dimension -> inteiro que represeta a dimensão da matriz
*  
*/

void alocaMatrizDistancias( int ***edgeSection, int dimension );

/* 
* zeraMatrizDistancias
*  Responsável por zerar campos da matriz de distancias
* 
*  método:
*       Recebe o endereço e a dimensão da matriz a ser zerada e atribui zero
*       em seus dimension x dimension campos 
* 
*  Parametros:
*       int ***edgeSection -> Ponteiro para a matriz de distancias
*       int dimension -> inteiro que represeta a dimensão da matriz
*  
*/

void zeraMatrizDistancias( int ***edgeSection, int dimension ) ;

/* 
* completaMatriz
*  Responsável por completar matriz de distancias, atribuindo o mesmo valor do
*  campo matriz[a][b] para o campo matriz[b][a], por se tratar de um TSP simples.
* 
*  método:
*       Recebe o endereço, a dimensão da matriz e o formato de armazenamento
*       da mesma. A partir do formato recebido, a função irá completar os campos
*       da matriz que não estão preenchidos. 
*       
* 
*  Parametros:
*       int ***edgeSection -> Ponteiro para a matriz de distancias
*       char *edgeFormat -> String contendo o formato de armazenamento de 
*       distancias
*       int dimension -> inteiro que represeta a dimensão da matriz
*  
*/

void completaMatriz( int ***edgeSection, char *edgeFormat, int dimension );

/*  (Função utilizada para testes.)
* printaInfoArquivo
*  Responsável por printar os campos lidos do arquivo de entrada
* 
*  método:
*       Recebe a estrutura de infArq e percorre seus campos. Se não
*       forem nulos, os campos são exibidos em tela.  
* 
*  Parametros:
*       infArq **cmds -> Ponteiro para estrutura de informações do arquivo 
*       de entrada
*  
*/


void printaInfoArquivo( infArq **cmds );

/* 
* contains
*  Checa se substring está contida na string
* 
*  método:
*       Percorre string buscando por ocorrencias de substring. 
* 
*  Parametros:
*       char *string -> string principal a ser checada 
*       char *substring -> string a ser buscada na string principal
*  
*  Retorno:
*       Retorna 1 caso a substring esteja presente na string e zero
*       caso contrário.
*/

int contains( char *string, char *substring ); 
