#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include "Solucao.h"

/*
*simulatedAnnealing
*	Funcao responsavel por executar o algorito do simulated annealing
*	Parametros:
*		int **matriz: matriz composta por todas as distancias entre as cidades
*		int tam: tamanho da dimensão da matriz
*
*	Retorno:
*		Retorna um ponteiro para estrutura que represenda a melhor solução encontrada no simuleted annealing
*
*/
Solucao *simulatedAnnealing( int **matriz, int tam );

/*
*jaPassou
*	Funçao que confere se uma cidade já foi percorida pelo algoritmo
*	Parametros:
*		int cidade: cidade para onde o algoritmo pretende ir
*		int *vetor: Vetor com todas as cidades por onde o algoritmo já passou
*		int tam: Tamanho do vetor com todas as cidades já visitadas
*
*	Retorno:
*		Retorna um entre dois inteiros:
*			1 se a cidade está dentro do vetor de cidades percorridas
*			0 se a cidade não está dentro do vetor de cidades percorridas 
*
*/
int jaPassou(int cidade, int *vetor, int tam);

/*
*iniciaVetorCidadesPercorridas
*	Função responsavel pela inicialização do vetor cidadesPercorridas, atribuindo o valor -1 para todas as suas posiçoes
*	Parametros:
*		int *cidadesPercorridas: vetor que sera iniciado pela função
*		int tam: tamanho do vetor que será iniciado
*
*	Retorno:
*
*/
void iniciaVetorCidadesPercorridas (int *cidadesPercorridas, int tam);

/*
*somaCaminhos
*	Função responsavel pelo calculo da distancia total percorrida pelo algoritmo em uma iteração
*	Parametros:
*		int **matriz: matriz com todas as distancias entre as cidades
*		int *cidadesPercorridas: vetor com todas as cidades percorridas pelo algoritmo em uma iteração
*		int tam: tamanho do vetor com as cidades percorridas
*
*	Retorno:
*		Retorna um inteiro que representa a distancia total percorrida telo algoritmo em uma iteração
*/
int somaCaminhos( int **matriz, int *cidadesPercorridas, int tam );

/*
*copiaVetor
*	Função que copia um vetor
*	Parametros:
*		int *destino: vetor para onde as informaçoes serao copiadas
*		int *origem: vetor de onde as informaçoes sairao
*		int tam: tamanho do vetor a ser copiado
*
*	Retorno:
*
*/
void copiaVetor(int *destino, int *origem, int tam );

/*
*printaCidades
*	Função responsavel por imprimir todas as cidades percorridas pelo algoritmo até dado momento
*	Parametros:
*		int *cidades:Vetor com todas as cidades por onde o algoritmo já passou
*		int tam: Tamanho do vetor com todas as cidades já visitadas
*
*	Retorno:
*
*/
void printaCidades (int *cidades, int tam);

/*
*getMenorCaminho
*	Função que analisa detre todos os caminhos que o algoritmo pode seguir qual o menor
*	Parametros:
*		int **matriz: matriz composta por todas as distancias entre as cidades
*		int cidadeAtual: cidade onde o algoritmo se encontra atualmente
*		int *v: vetor com todas as cidades percorridas pelo algoritmo ate dado momento
*		int tam: tamanho do vetor com todas as cidades já visitadas
*
*	Retorno:
*		retorna um inteiro que representa o menor caminho a ser sequido a partir da cidade atual, sem repetir cidades.
*/
int getMenorCaminho(int **matriz, int cidadeAtual, int *v, int tam);