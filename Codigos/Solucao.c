#include "Solucao.h"
#include <stdlib.h>

Solucao **criarSolucao( int *cidades, int distancia, int dimension ) {
    Solucao **sol = (Solucao**)malloc(sizeof(Solucao));
    (*sol)->cidades = (int*)malloc(sizeof(int)*dimension);
    (*sol)->distancia = distancia;
    return sol;
}
