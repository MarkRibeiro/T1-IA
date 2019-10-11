#include"simulatedAnnealing.h"

int jaPassou(int cidade, int *vetor, int tam){
    for(int i=0;i<tam;i++){
        if(vetor[i] == cidade)
            return 1; //ja pasosu
    } 
    return 0;//Não passou
}

int getMenorCaminho(int **matriz, int cidadeAtual, int *v, int tam){    
    int menor = 9999;
    int cidade;
    int aux = 0;

    for(;aux<tam;aux++){
        if(menor>matriz[cidadeAtual][aux] && matriz[cidadeAtual][aux]!=0 && jaPassou(aux, v, tam)==0){
            menor = matriz[cidadeAtual][aux];
            cidade = aux;
        }
    }

    return cidade;
}

Solucao *simulatedAnnealing( int **matriz, int tam ){
    Solucao *sol = (Solucao*)malloc(sizeof(Solucao));
    Solucao *melhor = (Solucao*)malloc(sizeof(Solucao));
    sol->cidades = (int*)malloc(sizeof(int)*tam);
    melhor->cidades = (int*)malloc(sizeof(int)*tam);
    int cidadeAtual;
    int cidadeDestino;
    //int distancia = matriz[cidadeAtual][cidadeDestino];
    int dado;
    int novoDestino;
    int aux=1;
    int mult = 100/tam;
    int cont = 0;

    sol->cidades[0] = 0;
    
    printf("inicio: matriz[0][1] = %d\n", matriz[0][1]);

    while(cont<99999999){
        cidadeAtual = 0;
        cidadeDestino = 1;
        iniciaVetorCidadesPercorridas (sol->cidades, tam);
        sol->cidades[0] = 0;
        aux = 1;
        while(aux<tam){
            srand(time(0));
            dado = rand() % 100;
            if(dado<=mult*(tam-aux)){
                novoDestino = rand() % tam;
                while(jaPassou(novoDestino, sol->cidades, tam)==1){
                    novoDestino = rand() % tam;
                }
            }else{
                novoDestino = getMenorCaminho(matriz, cidadeAtual, sol->cidades, tam);
            }
            sol->cidades[aux] = novoDestino;
            aux++;
            //printf("[%d][%d][%d][%d]\n", sol->cidades[0], sol->cidades[1], sol->cidades[2], sol->cidades[3]);
            cidadeAtual = novoDestino;
        }
        sol->distancia = somaCaminhos( matriz, sol->cidades, tam );
        if( melhor->distancia > sol->distancia || cont==0 ){
            printaCidades (sol->cidades, tam);
            copiaVetor(melhor->cidades, sol->cidades, tam);
            melhor->distancia = somaCaminhos( matriz, melhor->cidades, tam );
            printf("Melhor: %d\n", melhor->distancia);
            printf("em %ds\n", cont/26473);
        }
        cont++;
    }
    return melhor;
}

void iniciaVetorCidadesPercorridas (int *cidadesPercorridas, int tam){
    for(int i=0;i<tam;i++){
        cidadesPercorridas[i] = -1;
    }
}

int somaCaminhos( int **matriz, int *cidadesPercorridas, int tam ){
    int total = 0;

    for(int i=0;i<tam-1;i++){
        total += matriz[cidadesPercorridas[i]][cidadesPercorridas[i+1]];
    }
    total += matriz[cidadesPercorridas[tam-1]][cidadesPercorridas[0]];

    return total;
}

void copiaVetor(int *destino, int *origem, int tam ){
    for(int i=0;i<tam;i++){
        destino[i] = origem[i];
    }
}

void printaCidades (int *cidades, int tam){
    printf(" Cidades: ");
    for( int i = 0; i < tam; i++ ) {
       printf(" %d ", cidades[i]);
    }
    printf("\n");
}

// int main ()
// {
//     int **matriz;
//     int *cidadesPercorridas;
//     srand(time(NULL));

//     cidadesPercorridas = (int*) malloc (sizeof(int)*TAM);
//     iniciaVetorCidadesPercorridas(cidadesPercorridas, TAM);

//     matriz = (int**) malloc (sizeof(int*)*TAM);
//     matriz[0] = (int*) malloc (sizeof(int)*TAM);
//     matriz[1] = (int*) malloc (sizeof(int)*TAM);
//     matriz[2] = (int*) malloc (sizeof(int)*TAM);
//     matriz[3] = (int*) malloc (sizeof(int)*TAM);

//     /**/matriz[0][0] = 0;
//         matriz[0][1] = 2;
//         matriz[0][2] = 3;
//         matriz[0][3] = 1;

//         matriz[1][0] = 3;
//     /**/matriz[1][1] = 0;
//         matriz[1][2] = 2;
//         matriz[1][3] = 1;

//         matriz[2][0] = 2;
//         matriz[2][1] = 2;
//     /**/matriz[2][2] = 0;
//         matriz[2][3] = 2;

//         matriz[3][0] = 1;
//         matriz[3][1] = 1;
//         matriz[3][2] = 2;
//     /**/matriz[3][3] = 0;

//     Solucao *sol = simulatedAnnealing( matriz, TAM );
//     printf("total: %d\n", sol->distancia);

// }