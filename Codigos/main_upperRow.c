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


void printaInfoArquivo( infArq **cmds);
void atribuindoInfosArquivo( infArq **cmds, FILE *f);
void alocaMatrizDistancias( int ***edgeSection, int dimension );
void zeraMatrizDistancias( int ***edgeSection, int dimension ) ;
int contains( char *string, char *substring ); 
void gulosa( infArq **cmds );
void lowerDiagRow( int ***edgeSection, int dimension , FILE *f);
void upperRow( int ***edgeSection, int dimension , FILE *f);

    
int main( int argc, char *argv[ ] ) {
	FILE *f;
    if( argc == 1 ) {
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
    strcpy(cmds->name, " ");
	cmds->type = (char*) malloc(sizeof(char)*20);
    strcpy(cmds->type, " ");
	cmds->comment = (char*) malloc(sizeof(char)*50);
    strcpy(cmds->comment, " ");
	cmds->edgeType = (char*) malloc(sizeof(char)*30);
    strcpy(cmds->edgeType, " ");
    cmds->dataType = (char*) malloc(sizeof(char)*30);
    strcpy(cmds->dataType, " ");
	cmds->edgeFormat = (char*) malloc(sizeof(char)*20);
    strcpy(cmds->edgeFormat, " ");

	//Atribuindo infos do arquivo
    atribuindoInfosArquivo(&cmds, f);
    // Imprimir Dados de estrutura
    printaInfoArquivo(&cmds);
    //gulosa(&cmds);

	fclose(f);
	return 0;
}

void atribuindoInfosArquivo( infArq **cmds, FILE *f ) {
    char linha[50];
    
    for(int aux = 0; !contains(linha, "EDGE_WEIGHT_SECTION"); aux++) {
		fgets(linha, 50, f);
        int it = 0;
		int aux2 = 0;
        // Pega a posição que é o final do nome da tag da linha
        for(; linha[aux2] != ':'; aux2++) {}
		aux2 = aux2 + 2;
        // Atribui o valor da tag para cada campo da estrutura
		if( contains(linha, "NAME") ) { // Campo NAME
			for(; linha[aux2] != '\0'; aux2++) {
                (*cmds)->name[it] = linha[aux2];
                it++;
            }
		} else if( contains(linha, "TYPE") ) { // Campo TYPE
			for(; linha[aux2] != '\0'; aux2++) {
                (*cmds)->type[it] = linha[aux2];
                it++;
            }
		} else if( contains(linha, "COMMENT") ) {// Campo COMMENT
            for(; linha[aux2] != '\0'; aux2++) {
                (*cmds)->comment[it] = linha[aux2];
                it++;
            }
		} else if( contains(linha, "DIMENSION") ) { // Campo DIMENSION
            for(; linha[aux2] != '\0'; aux2++) {
                (*cmds)->edgeType[it] = linha[aux2];
                it++;
            }
            (*cmds)->dimension = atoi((*cmds)->edgeType);
		} else if( contains(linha, "EDGE_WEIGHT_TYPE") ) { // Campo EDGE_WEIGHT_TYPE
            for(; linha[aux2] != '\0'; aux2++) {
                (*cmds)->edgeType[it] = linha[aux2];
                it++;
            }
		} else if( contains(linha, "EDGE_WEIGHT_FORMAT") ) { // Campo EDGEFORMAT
            for(; linha[aux2] != '\0'; aux2++) {
                (*cmds)->edgeFormat[it] = linha[aux2];
                it++;
            }
        } else if( contains(linha, "DISPLAY_DATA_TYPE") ) {
            for(; linha[aux2] != '\0'; aux2++) {
                (*cmds)->dataType[it] = linha[aux2];
                it++;
            }
        }
	}
	// Alocando espaço de memória de matriz de distâncias e zerando seus campos
	alocaMatrizDistancias(&(*cmds)->edgeSection, (*cmds)->dimension);
    zeraMatrizDistancias(&(*cmds)->edgeSection, (*cmds)->dimension);  
    //Atribuindo informação de distancia à matriz de distancias
    if( contains((*cmds)->edgeFormat, "LOWER_DIAG_ROW") ) {
        lowerDiagRow(&(*cmds)->edgeSection, (*cmds)->dimension, f);
    } else if( contains((*cmds)->edgeFormat, "UPPER_ROW") ) {
        upperRow(&(*cmds)->edgeSection, (*cmds)->dimension, f);
    }

    if(strcmp((*cmds)->edgeFormat, "UPPER_DIAG_ROW\n") == 0){
        printf("UPPER_DIAG_ROW\n"); 
    }

    if(strcmp((*cmds)->edgeFormat, "UPPER_ROW \n") == 0){
        printf("UPPER_ROW \n");
    }
}

void lowerDiagRow( int ***edgeSection, int dimension , FILE *f) {
    int l = 0;
    int c = 0;
    for(int j=0;fscanf(f, "%d", &(*edgeSection)[l][c])!=0;j++) {
		if((*edgeSection)[l][c]==0) {
			l++;
			c=0;
		}
		else {
			c++;
		}
	}
}

void upperRow( int ***edgeSection, int dimension , FILE *f) {
    int l = 0;
    int c = 0;
    (*edgeSection)[l][c] = 0;
    c++;
    for(int j=0;fscanf(f, "%d", &(*edgeSection)[l][c])!=0;j++) {
		int aux = 0;
        if( c == 0 ) {
            int lastInserted = (*edgeSection)[l][c];
            while( aux < l + 1 ) {
                (*edgeSection)[l][c] = 0;
                c++;
                aux++;
            }
            (*edgeSection)[l][c] = lastInserted;
        }
        printf("coloquei %d na posicao [%d] [%d]\n", (*edgeSection)[l][c],l,c);
        if( c == dimension - 1 ) {
            l++;
            c=0;
        } else {
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

void zeraMatrizDistancias( int ***edgeSection, int dimension ) {
    for( int i=0; i < dimension; i++ )
	{
		for( int j=0; j < dimension; j++ )
		{
			(*edgeSection)[i][j] = 0;
		}
	}    
}


void printaInfoArquivo( infArq **cmds ) {
    if( strcmp((*cmds)->name," ") ) {
        printf("nome:%s\n", (*cmds)->name);
    }
    if( strcmp((*cmds)->type," ") ) {
        printf("type:%s\n", (*cmds)->type);
    }
    printf("dimension:%d\n", (*cmds)->dimension);
    if( strcmp((*cmds)->comment," ") ) {
        printf("comment:%s\n", (*cmds)->comment);
    }
    if( strcmp((*cmds)->edgeType," ") ) {
        printf("edgeType:%s\n", (*cmds)->edgeType);
    }
    if( strcmp((*cmds)->edgeFormat," ") ) {
        printf("edgeFormat:%s\n", (*cmds)->edgeFormat);
    }
    if( strcmp((*cmds)->dataType," ") ) {
        printf("dataType:%s\n", (*cmds)->dataType);
    }
    for( int i=0; i < (*cmds)->dimension; i++ )
    {
		for( int j=0; j < (*cmds)->dimension;j++ )
		{
			printf("%d ", (*cmds)->edgeSection[i][j]);
		}
		printf("\n");
	}
}

int contains( char *string, char *substring ) {
    if(strstr(string, substring) != NULL) {
        return 1;
    } else {
        return 0;
    }
}

void gulosa( infArq **cmds ){
    int total = 0, menor;

    menor = (*cmds)->edgeSection[1][0];
    for(int i=1;i<24;i++){
        for(int j=0;(*cmds)->edgeSection[i][j]!=0;j++){
            if((*cmds)->edgeSection[i][j]<menor){
                menor = (*cmds)->edgeSection[i][j];
            }
        }
        printf("%d\n", menor);
        total = total + menor;
        menor = 999;
    }
    printf("****\n");
    printf("%d %d\n", total, menor);
    printf("****\n");
}
