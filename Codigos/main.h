#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************
* >>>>>>>>>>>  (Para desenvolvedores) <<<<<<<<<<<
*   Mark, coloquei a possibilidade da gente inserir novos arquivos para agilizar
*   o teste de outros problemas. A forma de executar é:
*   ./main <nome do arquivo> 
* 
*   Se nenhum arquivo for apontado, assumirei que é o gr24.tsp no intuito de não
*   tomar muito tempo nosso. Fogoo!
* >>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<
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

struct solucao {
    int *cidades;
    int distancia;
} typedef struct solucao Solucao;

void atribuindoInfosArquivo( infArq **cmds, FILE *f );
void lowerDiagRow( int ***edgeSection, int dimension , FILE *f );
void upperDiagRow( int ***edgeSection, int dimension , FILE *f );
void upperRow( int ***edgeSection, int dimension , FILE *f );
void alocaMatrizDistancias( int ***edgeSection, int dimension );
void zeraMatrizDistancias( int ***edgeSection, int dimension ) ;
void printaInfoArquivo( infArq **cmds );
int contains( char *string, char *substring ); 
void completaMatriz( int ***edgeSection, char *edgeFormat, int dimension );
void gulosa( infArq **cmds );

