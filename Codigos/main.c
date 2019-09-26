#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	int **edgeSection;
}; typedef struct infoArquivo infArq;


void printaInfoArquivo( infArq **cmds);
void atribuindoInfosArquivo( infArq **cmds, FILE *f);
void alocaMatrizDistancias( int ***edgeSection, int dimension );
void zeraMatrizDistancias( int ***edgeSection );

    
int main( int argc, char *argv[ ] ) {
	FILE *f;
    if( argc < 0 ) {
        if( (f = fopen("../Instancias/gr24.tsp", "r") ) == NULL) {
            printf("Erro na abertura do arquivo\n");
            return 0;
        }
    } else {
        if( (f = fopen(argv[1], "r") ) == NULL) {
            printf("Erro na abertura do arquivo\n");
            return 0;
        }
    }
	// Alocando estrutura com infos do arq inserido
	infArq *cmds;
	cmds =  (infArq*) malloc(sizeof(infArq));
	cmds->name = (char*) malloc(sizeof(char)*20);
	cmds->type = (char*) malloc(sizeof(char)*20);
	cmds->comment = (char*) malloc(sizeof(char)*50);
	cmds->edgeType = (char*) malloc(sizeof(char)*30);
	cmds->edgeFormat = (char*) malloc(sizeof(char)*20);
	//Atribuindo infos do arquivo
    atribuindoInfosArquivo(&cmds, f);
	
    // Imprimir Dados de estrutura
    printaInfoArquivo(&cmds);

	fclose(f);
	return 0;
}

void atribuindoInfosArquivo( infArq **cmds, FILE *f ) {
    char linha[50];
    
    for(int aux = 0; aux < 7; aux++) {
		fgets(linha, 50, f);
        int it = 0;
		int aux2 = 0;
        // Pega a posição que é o final do nome da tag da linha
        for(; linha[aux2] != ':'; aux2++) {}
		aux2 = aux2 + 2;
        // Atribui o valor da tag para cada campo da estrutura
		if( aux == 0 ) { // Campo NAME
			for(; linha[aux2] != '\0'; aux2++) {
                (*cmds)->name[it] = linha[aux2];
                it++;
            }
		} else if( aux == 1 ) { // Campo TYPE
			for(; linha[aux2] != '\0'; aux2++) {
                (*cmds)->type[it] = linha[aux2];
                it++;
            }
		} else if( aux == 2 ) {// Campo COMMENT
            for(; linha[aux2] != '\0'; aux2++) {
                (*cmds)->comment[it] = linha[aux2];
                it++;
            }
		} else if( aux == 3 ) { // Campo DIMENSION
            for(; linha[aux2] != '\0'; aux2++) {
                (*cmds)->edgeType[it] = linha[aux2];
                it++;
            }
            (*cmds)->dimension = atoi((*cmds)->edgeType);
		} else if( aux == 4 ) { // Campo EDGETYPE
            for(; linha[aux2] != '\0'; aux2++) {
                (*cmds)->edgeType[it] = linha[aux2];
                it++;
            }
		} else if( aux == 5 ) { // Campo EDGEFORMAT
            for(; linha[aux2] != '\0'; aux2++) {
                (*cmds)->edgeFormat[it] = linha[aux2];
                it++;
            }
        }
	}
	// Alocando espaço de memória de matriz de distâncias e zerando seus campos
	alocaMatrizDistancias(&(*cmds)->edgeSection, (*cmds)->dimension);
    zeraMatrizDistancias(&(*cmds)->edgeSection);
    int l = 0;
    int c = 0;
    
    //Atribuindo informação de distancia à matriz de distancias
	for(int j=0;fscanf(f, "%d", &(*cmds)->edgeSection[l][c])!=0;j++)
	{
		if((*cmds)->edgeSection[l][c]==0)
		{
			l++;
			c=0;
		}
		else
		{
			c++;
		}
	}
}

void alocaMatrizDistancias( int ***edgeSection, int dimension ) {
    (*edgeSection) = (int**) malloc( dimension*sizeof(int*) );
    for( int aux = 0; aux < dimension; aux++ ) {
        (*edgeSection)[aux] = (int*) malloc( dimension*sizeof(int) );
    }
}

void zeraMatrizDistancias( int ***edgeSection ) {
    int l = 0;
    int c = 0;
    for(int i=0;i<24;i++)
	{
		for(int j=0;j<24;j++)
		{
			(*edgeSection)[i][j] = 0;
		}
	}    
}


void printaInfoArquivo( infArq **cmds ) {
    printf("nome:%s\n", (*cmds)->name);
    printf("type:%s\n", (*cmds)->type);
    printf("dimension:%d\n", (*cmds)->dimension);
    printf("comment:%s\n", (*cmds)->comment);
    printf("edgeType:%s\n", (*cmds)->edgeType);
    printf("edgeFormat:%s\n", (*cmds)->edgeFormat);
    for(int i=0;i<24;i++)
    {
		for(int j=0;j<24;j++)
		{
			printf("%d ", (*cmds)->edgeSection[i][j]);
		}
		printf("\n");
	}
}
