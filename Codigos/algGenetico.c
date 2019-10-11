#include "algGenetico.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <unistd.h>

Solucao *algoritmoGenetico( int **edgeSection, int dimension ) {
    int *v = (int*)malloc(sizeof(int)*dimension);
    int distancia;
    for(int i = 0; i < dimension; i++) {
        v[i] = i;
        distancia = distancia + i;
    }
    int tamPopulacao = dimension / 5;
    Solucao *sol = populacaoInicial( dimension, edgeSection );

    int numMutacoes = 0;
    
    
    while( numMutacoes == 3000 ) {
        int *paisIndx = buscaMelhoresFitness( sol, tamPopulacao );
        int indxP1 = paisIndx[0];
        int indxP2 = paisIndx[1];
        int *p1 = sol[indxP1].cidades;
        int *p2 = sol[indxP2].cidades;
        mutacao( p1, p2);
        
        
        
        numMutacoes++;
    }
    
    for( int i = 0; i < tamPopulacao; i++ ) {
        printf("Elemento %d\n=>Cidades: ", i); 
        for( int t = 0; t < dimension; t++ ) {
            printf("%d ", sol[i].cidades[t]); 
        }
        printf("\nDistancia: %d\n\n", sol[i].distancia);
    }    

    return sol;
}

void mutacao( int *p1, int *p2 ) {
    
}

int *buscaMelhoresFitness( Solucao *sol, int tamPopulacao ) {
    int *melhorFitness = (int*)malloc(sizeof(int)*2);//sol[0].distancia;
    for( int i = 0; i < tamPopulacao; i++ ) {
        if( melhorFitness[0] > sol[i].distancia ) {
            melhorFitness[0] = sol[i].distancia;
        } else if( melhorFitness[1] > sol[i].distancia ) {
            melhorFitness[1] = sol[i].distancia;
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
