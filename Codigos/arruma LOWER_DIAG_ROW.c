#include<stdio.h>
int main ()
{
	FILE *f = fopen("gr24.tsp", "r");
	char linha[50];

	
	fgets(linha, 50, f);
	fgets(linha, 50, f);
	fgets(linha, 50, f);
	fgets(linha, 50, f);
	fgets(linha, 50, f);
	fgets(linha, 50, f);
	fgets(linha, 50, f);

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