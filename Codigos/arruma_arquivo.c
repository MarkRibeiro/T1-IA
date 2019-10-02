#include<stdio.h>
int main ()
{
	FILE *f = fopen("../Instancias/gr24.tsp", "r");
	char *linha;
	size_t size = 0;
	int teste[50];

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
	getline(&linha, &size, f);
	printf("%s\n", linha);
	
	for(int j=0;fscanf(f, "%d", &teste[0])!=0;j++){
		if(linha[0] == 'E')
		{
			j++;
		}
		else
		{
			//fscanf(f, "%d", &teste[0]);
			printf("%d", teste[0]);
			printf("\n");
			sleep(1);
		}
	}

	fclose(f);
	return 0;
}