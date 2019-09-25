#include<stdio.h>
#include<stdlib.h>

int** iniciaMatrix(int coluna, int linha)
{
	/*
	0
	1	0
	2	3	0
	4   5   6	0
	7	8	9	1	0
	2	3	4	5	6	0
	*/
	int **f;

	f = malloc(coluna * sizeof *f);
	for (int i=0; i<linha; i++)
  	{
    	f[i] = malloc(coluna * sizeof *f[i]);
  	}

	//f[coluna][linha]
	f[0][0] = 0;
	f[0][1] = 1;
	f[0][2] = 2;
	f[0][3] = 4;
	f[0][4] = 7;
	f[0][5] = 2;

	f[1][0] = 0;
	f[1][1] = 0;
	f[1][2] = 3;
	f[1][3] = 5;
	f[1][4] = 8;
	f[1][5] = 3;

	f[2][0] = 0;
	f[2][1] = 0;
	f[2][2] = 0;
	f[2][3] = 6;
	f[2][4] = 9;
	f[2][5] = 4;

	f[3][0] = 0;
	f[3][1] = 0;
	f[3][2] = 0;
	f[3][3] = 0;
	f[3][4] = 1;
	f[3][5] = 5;

	f[4][0] = 0;
	f[4][1] = 0;
	f[4][2] = 0;
	f[4][3] = 0;
	f[4][4] = 0;
	f[4][5] = 6;

	f[5][0] = 0;
	f[5][1] = 0;
	f[5][2] = 0;
	f[5][3] = 0;
	f[5][4] = 0;
	f[5][5] = 0;

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
  	f = iniciaMatrix(6, 6);
	upperRow(f);
	imprimeMatrix(f);

	return 0;

}

