#include "simulatedAnnealing.h"

/* 
* algoritmoGenetico
*  Função que efetua o algoritmo genetico
* 
*  método:
*       Primeiro geramos uma população inicial, em seguida realizamos o crossover de
*       dois pais dessa população gerando uma nova geração. Esses filhos da nova geração
*       passam por uma mutação para que os resultados não permanecem em máximos locais.
*       Esse procedimento se repete até que a condição de parada seja atingida.
* 
*  Parametros:
*       int **edgeSection -> matriz que armazena as distancias de cada cidade para cada cidade
*       int dimesion -> inteiro que representa o número de elementos em p1
*  
*  Retorno:
*       retorna um ponteiro para a estrutura que representa a melhor solução encontrada, após
*       o algoritmo genético ser executado.
*/

Solucao *algoritmoGenetico( int **edgeSection, int dimension );

/* 
* populacaoInicial
*  Responsável por gerar a populacao Inicial do algoritmo genetico
* 
*  método:
*       O método de geração da primeira população inicial é a 50% aleatoria e
*       50% tendo escolhas gulosas. A intenção é que existam elementos de melhores
*       fitness para que as futuras gerações possam ser melhoradas
* 
*  Parametros:
*       int **edgeSection -> matriz que armazena as distancias de cada cidade para cada cidade
*       int dimesion -> inteiro que representa o número de elementos em p1
*       int tamPopulacao -> inteiro que representa o numero de elementos da populacao
*  
*  Retorno:
*       retorna um vetor de estruturas do tipo Solucao que representam a população inicial do
*       algoritmo
*/

Solucao *populacaoInicial( int dimension, int **edgeSection, int tamPopulacao );

/* 
*mutacao
*  Responsável pela mutação dos cromossomos da população.
* 
*  método:
*       Dois tipos de mutação diferente:
*       1)Geramos um número x que representa uma posição aleatoria e 
*       no intervalo [ x , dimension - x ] e invertemos esse intervalo
*       no intuito de efetuar uma mutação e evitar maximos locais.
*       2)Geramos um intervalo aleatorio no e reorganizamos esse intervalo de uma maneira
*       que segue o algoritmo guloso.
* 
*  Parametros:
*       int *p1 -> ponteiro para vetor que representa um cromossomo da população para sofrer mutação
*       int dimesion -> inteiro que representa o número de elementos em p1
*       int **edgeSection -> matriz que armazena as distancias de cada cidade para cada cidade
*/

void mutacao( int *p1, int dimension, int **edgeSection );

/* 
* crossover
*  Responsável efetuar o crossover de dois elementos
* 
*  método:
*       recebe dois pais da populacao escolhidos levando em conta seu fitness e a partir da geração
*       de dois números aleatorios define um intervalo para que seja efetuado um crossover.
* 
*  Parametros:
*       int *p1 -> ponteiro para vetor 1 que representa um cromossomo da população para sofrerá crossover
*       int *p2 -> ponteiro para vetor 2 que representa um cromossomo da população para sofrerá crossover
*       int dimesion -> inteiro que representa o número de elementos em p1 e p2       
*/

void crossover( int *p1, int *p2, int dimension );

/* 
*buscaMelhoresFitness
*  Responsável escolha de melhores fitness 
* 
*  método:
*       Escolhemos os pais que irão passar por crossover levando em conta o seu fitness, porém sem tirar a
*       possibilidade de um elemento da populacao ser escolhido, mas ao mesmo tempo favorencendo os elementos
*       de melhores fitness.
* 
*  Parametros:
*       Solucao *sol -> Vetor de soluções possíveis
*       int tamPopulacao -> inteiro que representa o tamanho do vetor de soluções
* 
*  Retorna:
*       Vetor de dois elementos que com os valores de index das duas soluções enecontradas
*/

int *buscaMelhoresFitness( Solucao *sol, int tamPopulacao );

/* 
*fitnessFunction
*  Responsável para atribuir um fitness para uma Solucao 
* 
*  método:
*       Para calcular o fitness fizemos a conta 1/x para que quanto menor a distancia, maior o fitness
* 
*  Parametros:
        int distancia -> valor da distancia da solução a ser avaliada.
* 
*  Retorna:
*       valor de fitness da solução
*/

double fitnessFunction( int distancia );

/* 
*organizaPorFitness
*  Responsável por organizar o vetor de soluções levando em conta o fitness 
* 
*  método:
*       Coloca os melhores fitness nas posições mais altas(maior index) do vetor
* 
*  Parametros:
*       Solucao *sol -> Vetor de soluções possíveis
*       int tamPopulacao -> inteiro que representa o tamanho do vetor de soluções
* 
*  Retorna:
*       valor de fitness da solução
*/

void organizaPorFitness( Solucao *sol, int tamPopulacao );

/* 
*escolheCidadeAleatoria
*  Responsável por escolher uma cidade de destino aleaoria.
* 
*  método:
*       Roda um valor de número aleatório e checa se é uma cidade que ainda nao foi percorrida.
*       Caso sim, retorna a cidade. Caso contrário, repete o processo.
* 
*  Parametros:
*       int *cidadesDisponiveis -> Vetor de inteiros que representa as cidades que ainda não foram
*                                  escolhidas para essa solução.
*       int tam -> inteiro que representa o tamanho do vetor de cidadesDisponiveis
* 
*  Retorna:
*       inteiro que representa cidade.
*/

int escolheCidadeAleatoria( int *cidadesDisponiveis, int tam );

/* 
*escolheCidadeGulosa
*  Responsável por escolher uma cidade de destino levando em conta um resultado otimizado.
* 
*  método:
*       Escolhe o melhor caminho para cidade a ser escolhida.
* 
*  Parametros:
*       int *cidadesDisponiveis -> Vetor de inteiros que representa as cidades que ainda não foram
*                                  escolhidas para essa solução.
*       int cidadeAtual -> inteiro que representa a cidade que o caxeiro está no momento.
*       int tam -> inteiro que representa o tamanho do vetor de cidadesDisponiveis
*       int **edgeSection -> matriz que armazena as distancias de cada cidade para cada cidade
*       int dimension -> inteiro que representa dimensão da matriz de distancias
* 
*  Retorna:
*       inteiro que representa cidade.
*/

int escolheCidadeGulosa( int *cidadesDisponiveis, int cidadeAtual, int tam, int **edgeSection, int dimension ); 

/* 
*calculaDistancia
*  Responsável por calcular a distancia da Solucao inserida
* 
*  método:
*       A partir da solução inserida e das distancias do problema, geramos quanto o caxeiro percorreu
*       nessa solução
* 
*  Parametros:
*       int *v-> Vetor de inteiros que representa o trajeto da solução
*       int **edgeSection -> matriz que armazena as distancias de cada cidade para cada cidade
*       int dimension -> inteiro que representa dimensão da matriz de distancias
* 
*  Retorna:
*       inteiro que representa a distancia percorrida nesse trajeto
*/

int calculaDistancia( int *v, int **edgeSection, int dimension );

/* 
*criaVetorCidadesDisponiveis
*  Responsável por criar vetor de cidades disponíveis para escolha.
* 
*  método:
*       A partir da dimensão inserida, um vetor é gerado com todas as cidades possíveis para escolha
*       no estado inicial, ou seja, todas as dimension cidades.
* 
*  Parametros:
*       int dimension -> inteiro que representa dimensão da matriz de distancias
* 
*  Retorna:
*       vetor de inteiros que representa o trajeto da solução
*/

int *criaVetorCidadesDisponiveis( int dimension );
