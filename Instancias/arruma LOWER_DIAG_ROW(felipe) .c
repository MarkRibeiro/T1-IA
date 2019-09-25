#include<stdio.h>

struct infoArquivo {
	char *name;
	char *type;
	char *comment;
	int dimension;
	char *edgeType;
	char *edgeFormat;
	int **edgeSection;
} typedef struct infoArquivo infArq;

int main ()
{
	FILE *f = fopen("gr24.tsp", "r");
	char linha[50];

	// Alocando estrutura com infos do arq inserido
	infArq *cmds;
	cmds =  (char*) malloc(sizeof(infoArquivo));
	cmds.name = (char*) malloc(sizeof(char)*20);
	cmds.type = (char*) malloc(sizeof(char)*20);
	cmds.comment = (char*) malloc(sizeof(char)*50);
	cmds.edgeType = (char*) malloc(sizeof(char)*30);
	cmds.edgeFormat = (char*) malloc(sizeof(char)*20);

	//Atribuindo infos do arquivo
	for(int aux = 0; aux < 7; aux++) {
		fgets(linha, 50, f);
		if( aux = 0 ) {
			linh
		} else if( aux == 1 ) {

		} else if( aux == 2 ) {
			
		} else if( aux == 3 ) {
			
		} else if( aux == 4 ) {
			
		} else if( aux == 5 ) {
			
		} else if( aux == 6 ) {

		}
	}
	// Criando matriz para armazenar distancias//
	// matriz alocada tem dimensoes Dimension x Dimension (campo do arquivo)
	cmds.edgeSection = (int**) malloc(cmds.dimension*sizeof(int));
	for(aux = 0; aux < cmds.dimension; aux++) {
		cmds.edgeSection[aux] = (int*) malloc( cmds.dimension*sizeof(int));
	}
	////////////////////
	for(int j=0;fgets(linha, 50, f)!=NULL;j++){
		for(int i=0;linha[i]!='\0';i++)
		{
			printf("%c", linha[i]);
			if(linha[i]=='0' && linha[i-1]==' ')
			{
				printf("\n");
			}
			if(linha[i+1]=='\n')
			{
				printf("\t");
				i++;
			}
			if(linha[i+1]==' ')
			{
				printf("\t");
				i++;
			}
		}
	}

	fclose(f);
	return 0;
}