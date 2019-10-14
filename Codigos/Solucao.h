
/************************************
*       Estrutura Solucao
*   -> Implementada para armazenar em memória as soluções do problema
* 
*   Campos:
*       1. *cidades    =>   Vetor de cidades que indicam o trajeto
*       2. distancia   =>   soma das distancias do trajeto dessa solução
*       3. tempo       =>   Valor em segundos para cronometrar o tempo que 
*                             demorou para alcançar essa solucao
* 
*   Estrutura escolhida para o armazenamento das distancias foi uma matriz.
* 
*************************************/

struct solucao {
    int *cidades;
    int distancia;
    double tempo;
}; typedef struct solucao Solucao;


/* 
* criarSolucao
*  Responsável por alocar uma solução em memória
* 
*  método:
*       Recebe vetor de cidades, valor da distancia e tamanho do vetor de cidades
*       para que possa retornar um vetor de ponteiros de soluções
* 
*  Parametros:
*       int *cidade   -> Vetor de cidades  
*       int distancia -> inteiro que representa a distancia percorrida nesse
*                        trajeto
*       int dimension -> inteiro que representa tamanho do vetor cidade
*  
*/

Solucao **criarSolucao( int *cidades, int distancia, int dimension );
