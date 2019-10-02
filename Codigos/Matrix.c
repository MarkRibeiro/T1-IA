#include<stdio.h>
#include<stdlib.h>

int** iniciaMatrix(int coluna, int linha)
{
	int **f;
  	FILE *file = fopen("../Instancias/gr24.tsp", "r");
	char l[50];

	f = malloc(coluna * sizeof *f);

	for (int i=0; i<linha; i++)
  	{
    	f[i] = malloc(coluna * sizeof *f[i]);
  	}
	
	fgets(l, 50, file);
	fgets(l, 50, file);
	fgets(l, 50, file);
	fgets(l, 50, file);
	fgets(l, 50, file);
	fgets(l, 50, file);
	fgets(l, 50, file);

	for(int i=0;fgets(l, 50, file)!=NULL;i++){
		for(int j=0;)

	}

	//f[coluna][linha]
	return f;
}

void imprimeMatrix(int **f)
{
	for(int linha=0;linha<6;linha++)
	{
		for(int coluna=0;coluna<6;coluna++)
		{
			printf("%d\t", f[coluna][linha] );
		}
		printf("\n");
	}
}

void upperRow(int **f)
{
	for(int linha=0;linha<6;linha++)
	{
		for(int coluna=0;coluna<6;coluna++)
		{
			f[coluna][linha] = f[linha][coluna];
		}
	}
}

int main (void)
{
	int **f;
  	f = iniciaMatrix(24, 24);
	upperRow(f);
	imprimeMatrix(f);

	return 0;

}

