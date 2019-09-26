#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct infoArquivo {
	char *name;
	char *type;
	char *comment;
	int dimension;
	char *edgeType;
	char *edgeFormat;
	int **edgeSection;
}; typedef struct infoArquivo infArq;


void printaMatriz(int **mat);


int main ()
{
	FILE *f;
    if( (f = fopen("../Instancias/gr24.tsp", "r") ) == NULL) {
        printf("Erro na abertura do arquivo\n");
        return 0;
    }
	char linha[50];

	// Alocando estrutura com infos do arq inserido
	infArq *cmds;
	cmds =  (infArq*) malloc(sizeof(infArq));
	cmds->name = (char*) malloc(sizeof(char)*20);
	cmds->type = (char*) malloc(sizeof(char)*20);
	cmds->comment = (char*) malloc(sizeof(char)*50);
	cmds->edgeType = (char*) malloc(sizeof(char)*30);
	cmds->edgeFormat = (char*) malloc(sizeof(char)*20);
	//Atribuindo infos do arquivo
	for(int aux = 0; aux < 7; aux++) {
		fgets(linha, 50, f);
        int it = 0;
		int aux2 = 0;
        // Pega a posição que é o final do nome da tag da linha
        for(; linha[aux2] != ':'; aux2++) {}
		aux2++;
        // Atribui o valor da tag ao campo da estrutura
		if( aux == 0 ) {
			for(; linha[aux2] != '\0'; aux2++) {
                cmds->name[it] = linha[aux2];
                it++;
            }
		} else if( aux == 1 ) {
			for(; linha[aux2] != '\0'; aux2++) {
                cmds->type[it] = linha[aux2];
                it++;
            }
		} else if( aux == 2 ) {
            for(; linha[aux2] != '\0'; aux2++) {
                cmds->comment[it] = linha[aux2];
                it++;
            }
		} else if( aux == 3 ) {
            for(; linha[aux2] != '\0'; aux2++) {
                cmds->edgeType[it] = linha[aux2];
                it++;
            }
            cmds->dimension = atoi(cmds->edgeType);
		} else if( aux == 4 ) {
            for(; linha[aux2] != '\0'; aux2++) {
                cmds->edgeType[it] = linha[aux2];
                it++;
            }
		} else if( aux == 5 ) {
            for(; linha[aux2] != '\0'; aux2++) {
                cmds->edgeFormat[it] = linha[aux2];
                it++;
            }
        }
	}
    cmds->edgeSection = (int**) malloc(cmds->dimension*sizeof(int*));
    for(int aux = 0; aux < cmds->dimension; aux++) {
        cmds->edgeSection[aux] = (int*) malloc( cmds->dimension*sizeof(int) );
    }
    int l = 0;
    int c = 0;
    for(int i=0;i<24;i++)
	{
		for(int j=0;j<24;j++)
		{
			cmds->edgeSection[i][j] = 0;
		}
	}
	
	for(int j=0;fscanf(f, "%d", &cmds->edgeSection[l][c])!=0;j++)
	{
		if(cmds->edgeSection[l][c]==0)
		{
			l++;
			c=0;
		}
		else
		{
			c++;
		}
	}
	printf("nome: %s\n", cmds->name);
    printf("type: %s\n", cmds->type);
    printf("dimension: %d\n", cmds->dimension);
    printf("comment: %s\n", cmds->comment);
    printf("edgeType: %s\n", cmds->edgeType);
    printf("edgeFormat: %s\n", cmds->edgeFormat);
    printaMatriz(cmds->edgeSection);

	fclose(f);
	return 0;
}


void printaMatriz( int **mat ) {
    	for(int i=0;i<24;i++)
	{
		for(int j=0;j<24;j++)
		{
			printf("%d ", mat[i][j]);
		}
		printf("\n");

	}
}
