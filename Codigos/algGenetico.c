#include "algGenetico.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
//#include <unistd.h>

Solucao *algoritmoGenetico( int **edgeSection, int dimension ) {
    //int *v = (int*)malloc(sizeof(int)*dimension);
    int distancia;
//     for(int i = 0; i < dimension; i++) {
//         v[i] = i;
//         distancia = distancia + i;
//     }
    int tamPopulacao = dimension / 5;
    Solucao *sol = populacaoInicial( dimension, edgeSection );

    int numMutacoes = 0;
    int cont = 0;
    int melhor = 9999999;
    while( cont < 99999999 ) {
        int *paisIndx = buscaMelhoresFitness( sol, tamPopulacao );
        int indxP1 = paisIndx[0];
        int indxP2 = paisIndx[1];
        crossover( sol[indxP1].cidades, sol[indxP2].cidades, dimension);
        mutacao( sol[indxP1].cidades, dimension );
        mutacao( sol[indxP2].cidades, dimension );
        sol[indxP1].distancia = calculaDistancia(sol[indxP1].cidades, edgeSection, dimension);
        sol[indxP2].distancia = calculaDistancia(sol[indxP2].cidades, edgeSection, dimension);
        if( melhor > sol[indxP1].distancia ) {
            melhor = sol[indxP1].distancia;
            printf("\nDistancia: %d\n", melhor);
        }
        if( melhor > sol[indxP2].distancia ) {
            melhor = sol[indxP2].distancia;
            printf("\nDistancia: %d\n", melhor);
        }
        cont++;
    }
    return sol;
}

double fitnessFunction( int distancia ) { 
    return 1/distancia;
}

void crossover( int *p1, int *p2, int dimension ) {  
    srand(time(0));
    int crossoverPoint = rand() % dimension/5;
    int *intervaloP1 = (int*)malloc(sizeof(int)*crossoverPoint);
    int *intervaloP2 = (int*)malloc(sizeof(int)*crossoverPoint);
    for( int i = 0; i < crossoverPoint; i++ ) {
        intervaloP1[i] =  p1[i];
        intervaloP2[i] =  p2[i];
    }
//     printf("Iniciando crossover( crossoverPoint = %d)\n", crossoverPoint);
//     printf("p1: ");
//     for( int t = 0; t < dimension; t++ ) {
//         printf("%d ", p1[t]); 
//     }
//     printf("\nIntervalorP1: ");
//     for( int i = 0; i < crossoverPoint; i++ ) {
//         printf("%d ", intervaloP1[i]);
//     }
//     printf("\np2: ");
//     for( int t = 0; t < dimension; t++ ) {
//         printf("%d ", p2[t]); 
//     }
//     printf("\nIntervalorP2: ");
//     for( int i = 0; i < crossoverPoint; i++ ) {
//         printf("%d ", intervaloP2[i]);
//     }
//     printf("\n\n\n");
    for( int i = 0; i < crossoverPoint; i++ ) {
        int pos;
        for( int t = 0; t < dimension; t++ ) {
            if( p1[t] == intervaloP2[i] ) {
                p1[t] = p1[i];
            }
            if( p2[t] == intervaloP1[i] ) {
                p2[t] = p2[i];
            }
        }
        p1[i] = intervaloP2[i];
        p2[i] = intervaloP1[i];
    }
    free(intervaloP1);
    free(intervaloP2);
}
// Reverse Sequence Mutation
void mutacao( int *p1, int dimension ) {
    srand(time(0));
    int mutationPoint1 = rand() % (dimension/2);
    int mutationPoint2 = (dimension-1) - mutationPoint1;
    int auxMutation1 = mutationPoint1;
    int auxMutation2 = mutationPoint2;
    for( int i = 0; i <= (mutationPoint2 - mutationPoint1)/2 ; i++ ) {
        int aux = p1[auxMutation1];
        p1[auxMutation1] = p1[auxMutation2];
        p1[auxMutation2] = aux;
        auxMutation1++;
        auxMutation2--;
    }

}


int *buscaMelhoresFitness( Solucao *sol, int tamPopulacao ) {
    int *melhorFitness = (int*)malloc(sizeof(int)*2);//sol[0].distancia;
    int primeiroJaFoi = 0;
    melhorFitness[0] = 4;
    int dist1 = 9999999;
    int dist2 = 9999999;
    for( int i = 0; i < tamPopulacao; i++ ) {
        if( dist1 > sol[i].distancia && primeiroJaFoi == 0) {
            dist1 = sol[i].distancia;
            melhorFitness[0] = i;
            primeiroJaFoi = 1;
        } else if( dist2 > sol[i].distancia ) {
            dist2 = sol[i].distancia;
            melhorFitness[1] = i;
        }
    }
    
    return melhorFitness;
}

Solucao *populacaoInicial( int dimension, int **edgeSection ) {
    int tamPopulacao = dimension / 5;
    //int *v = (int*)malloc(sizeof(int)*dimension);
    Solucao *sol = (Solucao*)malloc(sizeof(Solucao)*tamPopulacao);
    for( int i = 0; i < tamPopulacao; i++ ) {
        int *cidadesDisponiveis = criaVetorCidadesDisponiveis( dimension);
        int tamVetorCidadesDisponiveis = dimension;
        sol[i].cidades = (int*)malloc(sizeof(int)*dimension);
        for( int t = 0; t < dimension; t++ ) {
            sol[i].cidades[t] = escolheCidadeAleatoria( cidadesDisponiveis, tamVetorCidadesDisponiveis );
            tamVetorCidadesDisponiveis--;
        }
        sol[i].distancia = calculaDistancia( sol[i].cidades, edgeSection, dimension );
        //sleep(1);
    }
    return sol;
}

int calculaDistancia( int *v, int **edgeSection, int dimension ) {
    int distancia = 0;
    for( int i = 0; i+1 < dimension; i++ ) {
        //printf("edgeSection[%d][%d] = %d\n", v[i], v[i+1], edgeSection[v[i]][v[i+1]]); 
        distancia += edgeSection[v[i]][v[i+1]];
    }
    return distancia;
}   

// Gerando cidade aleaotoria baseada em cidades disponíveis. 
int escolheCidadeAleatoria( int *cidadesDisponiveis, int tam ) {  
    int aux;
    srand(rand());                                                 // Utilizamos uma geração aleaotoria.
    int indexCidade = ( rand() % tam );
    int cidade = cidadesDisponiveis[indexCidade];
    
    cidadesDisponiveis[indexCidade] = -1;
    
    for( int i = indexCidade; i < tam; i++ ) {
        if( cidadesDisponiveis[i] == -1 && i != tam-1) {
            aux = cidadesDisponiveis[i+1];
            cidadesDisponiveis[i+1] = cidadesDisponiveis[i];
            cidadesDisponiveis[i] = aux;
        }
    }    
    
    return cidade;
}

int *criaVetorCidadesDisponiveis( int dimension ) {
    int *v = (int*)malloc(sizeof(int)*dimension);
    for( int i = 0; i < dimension; i++ ) {
        v[i] = i;
    }
    return v;
}
