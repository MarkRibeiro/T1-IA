struct solucao {
    int *cidades;
    int distancia;
    double tempo;
}; typedef struct solucao Solucao;


// Funções para solução.
Solucao **criarSolucao( int *cidades, int distancia, int dimension );
