#include "simulatedAnnealing.h"

Solucao *algoritmoGenetico( int **edgeSection, int dimension );

// Funcões de algoritmo genetico
Solucao *populacaoInicial( int dimension, int **edgeSection, int tamPopulacao );
void mutacao( int *p1, int dimension );
void crossover( int *p1, int *p2, int dimension );
int *buscaMelhoresFitness( Solucao *sol, int tamPopulacao );
double fitnessFunction( int distancia );
void organizaPorFitness( Solucao *sol, int tamPopulacao );
/////


// algoritmo de escolha de proxima cidade para criação de populacaoInicial
int escolheCidadeAleatoria( int *cidadesDisponiveis, int tam );
int escolheCidadeGulosa( int *cidadesDisponiveis, int cidadeAtual, int tam, int **edgeSection ); 

// uteis
int calculaDistancia( int *v, int **edgeSection, int dimension );
int *criaVetorCidadesDisponiveis( int dimension );
