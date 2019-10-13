#include "algGenetico.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

Solucao *algoritmoGenetico( int **edgeSection, int dimension ) {
    int tamPopulacao = 10;
    Solucao *sol = populacaoInicial( dimension, edgeSection, tamPopulacao );
    Solucao *melhor = (Solucao*)malloc(sizeof(Solucao));
    melhor->cidades = (int*)malloc(sizeof(int)*dimension);
    int cont = 0;
    melhor->distancia = 9999999;
    
    clock_t iniciaTempo; //variavel responcavel pelo inicio da contagem do tempo
    clock_t tempoMelhor; //variavel responsavel pelo fim da contagem do tempo
    
    iniciaTempo = clock(); //pega o tempo antes de começar o codigo
    while( cont < 9999 ) {
        int *paisIndx = buscaMelhoresFitness( sol, tamPopulacao );
        int indxP1 = paisIndx[0];
        int indxP2 = paisIndx[1];
        crossover( sol[indxP1].cidades, sol[indxP2].cidades, dimension);
        mutacao( sol[indxP1].cidades, dimension );
        mutacao( sol[indxP2].cidades, dimension );
        sol[indxP1].distancia = calculaDistancia(sol[indxP1].cidades, edgeSection, dimension);
        sol[indxP2].distancia = calculaDistancia(sol[indxP2].cidades, edgeSection, dimension);
        if( melhor->distancia > sol[indxP1].distancia ) {
            tempoMelhor = clock(); //pega o tempo quando achar o melhor caso
            melhor->distancia = sol[indxP1].distancia;
            printf("\nDistancia: %d\n", melhor->distancia);
            copiaVetor(melhor->cidades, sol[indxP1].cidades, dimension);
            melhor->distancia = calculaDistancia( melhor->cidades, edgeSection, dimension);
            melhor->tempo = ((double) (tempoMelhor - iniciaTempo)) / CLOCKS_PER_SEC;
            printf("Melhor: %d ", melhor->distancia);
            printf("em %.2fs\n", melhor->tempo);
        }
        if( melhor->distancia > sol[indxP2].distancia ) {
            tempoMelhor = clock(); //pega o tempo quando achar o melhor caso
            melhor->distancia = sol[indxP2].distancia;
            printf("\nDistancia: %d\n", melhor->distancia);
            copiaVetor(melhor->cidades, sol[indxP2].cidades, dimension);
            melhor->distancia = calculaDistancia( melhor->cidades, edgeSection, dimension);
            melhor->tempo = ((double) (tempoMelhor - iniciaTempo)) / CLOCKS_PER_SEC;
            printf("Melhor: %d ", melhor->distancia);
            printf("em %.2fs\n", melhor->tempo);
        }
        cont++;
    }
    return melhor;
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
    for( int i = 0; i < crossoverPoint; i++ ) {
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

void organizaPorFitness( Solucao *sol, int tamPopulacao ) {
    Solucao aux;
    for( int i = 0; i < tamPopulacao; i++ ) {
        for( int j = 0; j < tamPopulacao - 1; j++ ) {
            if( sol[j].distancia < sol[j+1].distancia ) {
                aux = sol[j];
                sol[j] = sol[j+1];
                sol[j+1] = aux;
            }
        }
    }
}

int *buscaMelhoresFitness( Solucao *sol, int tamPopulacao ) {
    int *melhorFitness = (int*)malloc(sizeof(int)*2);
    organizaPorFitness(sol, tamPopulacao); // organiza por fitness
    int aux = 0;
    for(int i = 1; i <= tamPopulacao; i++) {
        aux += i;
    }
    double mult = 100.0/(double)aux;
    int primeiroJaFoi = 0;
    srand(time(0));
    int dado = rand() % 100;
    for( int j = 0; j < 2; j++ ) {
        int auxPorc = 100 - mult*(tamPopulacao-1);
        for( int i = (tamPopulacao-1); 0 < i; i-- ) {
            if( dado > auxPorc && primeiroJaFoi == 0) {
                melhorFitness[0] = i;
                primeiroJaFoi = 1;
                break;;
            } else if( dado > auxPorc ) {
                melhorFitness[1] = i;
                break;
            }
            auxPorc -= mult*i;
        }
        srand(dado);
        dado = rand() % 100;
    }
    return melhorFitness;
}

Solucao *populacaoInicial( int dimension, int **edgeSection, int tamPopulacao ) {
    Solucao *sol = (Solucao*)malloc(sizeof(Solucao)*tamPopulacao);
    for( int i = 0; i < tamPopulacao; i++ ) {
        int *cidadesDisponiveis = criaVetorCidadesDisponiveis( dimension);
        int tamVetorCidadesDisponiveis = dimension;
        sol[i].cidades = (int*)malloc(sizeof(int)*dimension);
        srand(time(0));
        int dado = rand() % 100;
        for( int t = 0; t < dimension; t++ ) {
            if( dado > 50 || t == 0 ) {
                sol[i].cidades[t] = escolheCidadeAleatoria( cidadesDisponiveis, tamVetorCidadesDisponiveis );
                tamVetorCidadesDisponiveis--;
            } else {
                sol[i].cidades[t] = escolheCidadeGulosa( cidadesDisponiveis, sol[i].cidades[t-1], tamVetorCidadesDisponiveis , edgeSection, dimension);
                tamVetorCidadesDisponiveis--;
            }
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
    distancia+= edgeSection[v[0]][v[dimension-1]];
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

// Gerando cidade baseada em distancia. 
int escolheCidadeGulosa( int *cidadesDisponiveis, int cidadeAtual, int tam, int **edgeSection, int dimension ) {  
    int aux;
    int melhor = 99999;
    int melhorCidade = 0;
    int melhorCidadeIndx = 0;
    for( int i = 0; i < dimension; i++ ) {
        if( melhor > edgeSection[cidadeAtual][i] && cidadeAtual != i) {
            for( int j = 0; j < tam; j++ ) {
                if( cidadesDisponiveis[j] == i ) {
                    melhor = edgeSection[cidadeAtual][i];
                    melhorCidadeIndx = j;
                    melhorCidade = i;
                }
            }
        }
    }
    cidadesDisponiveis[melhorCidadeIndx] = -1;
    for( int i = 0; i < tam-1; i++ ) {
        if( cidadesDisponiveis[i] == -1) {
            aux = cidadesDisponiveis[i+1];
            cidadesDisponiveis[i+1] = cidadesDisponiveis[i];
            cidadesDisponiveis[i] = aux;
        }
    }    
            
    return melhorCidade;
}

int *criaVetorCidadesDisponiveis( int dimension ) {
    int *v = (int*)malloc(sizeof(int)*dimension);
    for( int i = 0; i < dimension; i++ ) {
        v[i] = i;
    }
    return v;
}
