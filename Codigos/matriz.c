#include<stdio.h>
#include<stdlib.h>
int main ()
{
	FILE *f = fopen("../Instancias/gr24.tsp", "r");
	char *linha = (char*) malloc(sizeof(char));
	size_t size = 0;
	int l=0, c=0;
	int mat[24][24];

	//fgets(linha, 50, f);
	getline(&linha, &size, f);
	printf("%s\n", linha);
	getline(&linha, &size, f);
	printf("%s\n", linha);
	getline(&linha, &size, f);
	printf("%s\n", linha);
	getline(&linha, &size, f);
	printf("%s\n", linha);
	getline(&linha, &size, f);
	printf("%s\n", linha);
	getline(&linha, &size, f);
	printf("%s\n", linha);
	getline(&linha, &size, f);
	printf("%s\n", linha);

	for(int i=0;i<24;i++)
	{
		for(int j=0;j<24;j++)
		{
			mat[i][j] = 0;
		}
	}
	
	for(int j=0;fscanf(f, "%d", &mat[l][c])!=0;j++)
	{
		if(mat[l][c]==0)
		{
			l++;
			c=0;
		}
		else
		{
			c++;
		}
	}

	for(int i=0;i<24;i++)
	{
		for(int j=0;j<24;j++)
		{
			printf("%d ", mat[i][j]);
		}
		printf("\n");

	}

	printf("\n");
	printf("\n");
	printf("\n");
	printf("%d", mat[1][0] + mat[2][0]); 

	fclose(f);
	return 0;
}