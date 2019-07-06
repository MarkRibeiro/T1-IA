#include "simulatedAnnealing.h"

Solucao *populacaoInicial( int dimension, int **edgeSection );
Solucao *algoritmoGenetico( int **edgeSection, int dimension );
void mutacao( int *p1, int dimension );
void crossover( int *p1, int *p2, int dimension );
double fitnessFunction( int distancia );

int *buscaMelhoresFitness( Solucao *sol, int tamPopulacao );
int *criaVetorCidadesDisponiveis( int dimension );
int escolheCidadeAleatoria( int *cidadesDisponiveis, int tam );
int calculaDistancia( int *v, int **edgeSection, int dimension );
