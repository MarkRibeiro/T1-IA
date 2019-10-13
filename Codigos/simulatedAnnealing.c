#include"simulatedAnnealing.h"
#define ITERACOES 100000

Solucao *simulatedAnnealing( int **matriz, int tam ){
    Solucao *sol;
    Solucao *melhor;

    int dado;
    int novoDestino;
    int novoEstadoInicial;
    int aux;
    int mult; //Variavel responsavel pela probabilidade que o simuleted anealing tera de aceitar um caminho aleatorio
    int cont;   //Variavel responsavel pelo controle do numero de iterações

    clock_t iniciaTempo; //variavel responcavel pelo inicio da contagem do tempo
    clock_t tempoMelhor; //variavel responsavel pelo fim da contagem do tempo

    sol = (Solucao*)malloc(sizeof(Solucao));
    sol->cidades = (int*)malloc(sizeof(int)*tam);
    melhor = (Solucao*)malloc(sizeof(Solucao));
    melhor->cidades = (int*)malloc(sizeof(int)*tam);

    cont = 0;
    mult = 100/tam;

    iniciaTempo = clock(); //pega o tempo antes de começar o codigo

    while(cont < ITERACOES) {
        iniciaVetorCidadesPercorridas (sol->cidades, tam);
        aux = 0;

        while(aux<tam) {
            if( aux == 0 ) {
                novoEstadoInicial = rand() % tam;
                sol->cidades[aux] = novoEstadoInicial;
                aux++;
                continue;
            }

            srand(time(0));
            dado = rand() % 100;

            if(dado<=mult*(tam-aux)){ //caso o valor aleatorio for menor ou igual a mult*(tam-aux) o algoritmo tera liberdade para escolher uma cidade aleatoria
                novoDestino = rand() % tam;

                while(jaPassou(novoDestino, sol->cidades, tam)==1){
                    novoDestino = rand() % tam;
                }
            }else{ //caso contrario o algoritmo escolhera a cidade de menor custo
                novoDestino = getMenorCaminho(matriz, sol->cidades[aux-1], sol->cidades, tam);
            }

            sol->cidades[aux] = novoDestino;
            aux++;
        }

        sol->distancia = somaCaminhos( matriz, sol->cidades, tam );

        if( melhor->distancia > sol->distancia || cont==0 ){ //caso a melhor distancia for maior que a distancia atual uma nova melhor distancia foi encontrada
            tempoMelhor = clock(); //pega o tempo quando achar o melhor caso

            copiaVetor(melhor->cidades, sol->cidades, tam);
            melhor->distancia = somaCaminhos( matriz, melhor->cidades, tam );
            melhor->tempo = ((double) (tempoMelhor - iniciaTempo)) / CLOCKS_PER_SEC;

            printaCidades (melhor->cidades, tam);
            printf("Melhor: %d ", melhor->distancia);
            printf("em %.2fs\n", melhor->tempo);
        }

        cont++;
    }
    tempoMelhor = clock();
    printf("Fim: %.2fs\n", ((double) (tempoMelhor - iniciaTempo)) / CLOCKS_PER_SEC);
    return melhor;
}

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
    printf("Cidades: ");
    for( int i = 0; i < tam; i++ ) {
       printf(" %d ", cidades[i]);
    }
    printf("\n");
}