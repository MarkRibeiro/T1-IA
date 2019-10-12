#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <signal.h>
#include <unistd.h>
#include <sys/signal.h>

#include "Solucao.h"

int jaPassou(int cidade, int *vetor, int tam);
int getMenorCaminho(int **matriz, int cidadeAtual, int *v, int tam);
Solucao *simulatedAnnealing( int **matriz, int tam );
void iniciaVetorCidadesPercorridas (int *cidadesPercorridas, int tam);
int somaCaminhos( int **matriz, int *cidadesPercorridas, int tam );
void copiaVetor(int *destino, int *origem, int tam );
void printaCidades (int *cidades, int tam);
void alarm_handler(int signum);