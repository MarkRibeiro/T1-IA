#include "main.h"
#include "algGenetico.h"


int main( int argc, char *argv[ ] ) {
    FILE *f;
    int algoritmo;
    if( argc == 2 ) {
        if( (f = fopen("../Instancias/gr24.tsp", "r") ) == NULL) {
            printf("Erro na abertura do arquivo\n");
            return 0;
        }
        if( contains(argv[1], "genetico" ) ) {
            algoritmo = ALGORITMO_GENETICO;
        } else if( contains(argv[1], "annealing" ) ) {
            algoritmo = SIMULATED_ANNEALING;
        } else {
            printf("Insira um algoritmo válido! genetico ou annealing\n");
            return 0;
        }
    } else if( argc != 2 ) {
        printf("Execute o programa assim:\n> ./main <nome_arquivo_tsp> <algoritmo>\n ==> algoritmo pode ser genetico ou annealing.\n ==> arquivo deverá ser um tsp proposto\nEX: ./main ../Instancias/gr24.tsp genetico\n");
        return 0;
    } else {
        if( (f = fopen(argv[1], "r") ) == NULL) {
            printf("Erro na abertura do arquivo\n");
            return 0;
        }
    }
    //printf("algoritmo inserido: %d\n", algoritmo);
    // Alocando estrutura com infos do arq inserido
    infArq *cmds;
    cmds =  (infArq*) malloc(sizeof(infArq));
    cmds->name = (char*) malloc(sizeof(char)*20);
    strcpy(cmds->name, " ");
    cmds->type = (char*) malloc(sizeof(char)*20);
    strcpy(cmds->type, " ");
    cmds->comment = (char*) malloc(sizeof(char)*50);
    strcpy(cmds->comment, " ");
    cmds->edgeType = (char*) malloc(sizeof(char)*30);
    strcpy(cmds->edgeType, " ");
    cmds->dataType = (char*) malloc(sizeof(char)*30);
    strcpy(cmds->dataType, " ");
    cmds->edgeFormat = (char*) malloc(sizeof(char)*20);
    strcpy(cmds->edgeFormat, " ");

    //Atribuindo infos do arquivo
    atribuindoInfosArquivo(&cmds, f);
    // Imprimir Dados de estrutura
//  printaInfoArquivo(&cmds);
//  gulosa(&cmds);
    Solucao *sol;
    if( algoritmo == ALGORITMO_GENETICO ) {
        sol = algoritmoGenetico(cmds->edgeSection, cmds->dimension );
    }
    
    for( int t = 0; t < cmds->dimension/5; t++ ) {
        printf("Solucao:\n=>distancia: %d\n=>cidades:", sol[t].distancia);
        for( int i = 0; i < cmds->dimension; i++ ) {
            printf(" %d ", sol[t].cidades[i]);
        }
    }
    printf("\n");
    fclose(f);
    return 0;
}

 
void atribuindoInfosArquivo( infArq **cmds, FILE *f ) {
    char linha[50];
    
    for(int aux = 0; !contains(linha, "EDGE_WEIGHT_SECTION"); aux++) {
        fgets(linha, 50, f);
        int it = 0;
        int aux2 = 0;
        // Pega a posição que é o final do nome da tag da linha
        for(; linha[aux2] != ':'; aux2++) {}
        aux2 = aux2 + 2;
        // Atribui o valor da tag para cada campo da estrutura
        if( contains(linha, "NAME") ) { // Campo NAME
            for(; linha[aux2] != '\n'; aux2++) {
                (*cmds)->name[it] = linha[aux2];
                it++;
            }
        } else if( contains(linha, "COMMENT") ) {// Campo COMMENT
            for(; linha[aux2] != '\n'; aux2++) {
                (*cmds)->comment[it] = linha[aux2];
                it++;
            }
        } else if( contains(linha, "DIMENSION") ) { // Campo DIMENSION
            for(; linha[aux2] != '\n'; aux2++) {
                (*cmds)->edgeType[it] = linha[aux2];
                it++;
            }
            (*cmds)->dimension = atoi((*cmds)->edgeType);
        } else if( contains(linha, "EDGE_WEIGHT_TYPE") ) { // Campo EDGE_WEIGHT_TYPE
            for(; linha[aux2] != '\n'; aux2++) {
                (*cmds)->edgeType[it] = linha[aux2];
                it++;
            }
        } else if( contains(linha, "EDGE_WEIGHT_FORMAT") ) { // Campo EDGEFORMAT
            for(; linha[aux2] != '\n'; aux2++) {
                (*cmds)->edgeFormat[it] = linha[aux2];
                it++;
            }
        } else if( contains(linha, "DISPLAY_DATA_TYPE") ) {
            for(; linha[aux2] != '\n'; aux2++) {
                (*cmds)->dataType[it] = linha[aux2];
                it++;
            }
        } else if( contains(linha, "TYPE") ) { // Campo TYPE
            for(; linha[aux2] != '\n'; aux2++) {
                (*cmds)->type[it] = linha[aux2];
                it++;
            }
        } 
    }
    // Alocando espaço de memória de matriz de distâncias e zerando seus campos
    alocaMatrizDistancias(&(*cmds)->edgeSection, (*cmds)->dimension);
    zeraMatrizDistancias(&(*cmds)->edgeSection, (*cmds)->dimension);  
    //Atribuindo informação de distancia à matriz de distancias
    if( contains((*cmds)->edgeFormat, "LOWER_DIAG_ROW") ) {
        lowerDiagRow(&(*cmds)->edgeSection, (*cmds)->dimension, f);
    } else if( contains((*cmds)->edgeFormat, "UPPER_ROW") ) {
        upperRow(&(*cmds)->edgeSection, (*cmds)->dimension, f);
    } else if( contains((*cmds)->edgeFormat, "UPPER_DIAG_ROW") ) {
        upperDiagRow(&(*cmds)->edgeSection, (*cmds)->dimension, f);
    }

    completaMatriz(&(*cmds)->edgeSection, (*cmds)->edgeFormat, (*cmds)->dimension);
}

void lowerDiagRow( int ***edgeSection, int dimension , FILE *f ) {
    int l = 0;
    int c = 0;
    for(int j=0;fscanf(f, "%d", &(*edgeSection)[l][c])!=0;j++) {
        if((*edgeSection)[l][c]==0) {
            l++;
            c=0;
        }
        else {
            c++;
        }
    }
}

void upperDiagRow( int ***edgeSection, int dimension , FILE *f ) {
    int l = 0;
    int c = 0;
    int aux = 0;
    for(;fscanf(f, "%d", &(*edgeSection)[l][c])!=0;c++) {
        if((*edgeSection)[l][c]==0 && aux==1) {
            l++;
            aux = 0;
        }
        if((*edgeSection)[l][c]==0){
            aux = 1;
            c = l;
        }
    }
}

void upperRow( int ***edgeSection, int dimension , FILE *f) {
    int l = 0;
    int c = 0;
    (*edgeSection)[l][c] = 0;
    c++;
    for(int j=0;fscanf(f, "%d", &(*edgeSection)[l][c])!=0;j++) {
        int aux = 0;
        if( c == 0 ) {
            int lastInserted = (*edgeSection)[l][c];
            while( aux < l + 1 ) {
                (*edgeSection)[l][c] = 0;
                c++;
                aux++;
            }
            (*edgeSection)[l][c] = lastInserted;
        }
        if( c == dimension - 1 ) {
            l++;
            c=0;
        } else {
            c++;
        }
    }
}

void alocaMatrizDistancias( int ***edgeSection, int dimension ) {
    (*edgeSection) = (int**) malloc( dimension*sizeof(int*) );
    for( int aux = 0; aux < dimension; aux++ ) {
        (*edgeSection)[aux] = (int*) malloc( dimension*sizeof(int) );
    }
}

void zeraMatrizDistancias( int ***edgeSection, int dimension ) {
    for( int i=0; i < dimension; i++ )
    {
        for( int j=0; j < dimension; j++ )
        {
            (*edgeSection)[i][j] = 0;
        }
    }    
}


void printaInfoArquivo( infArq **cmds ) {
    if( strcmp((*cmds)->name," ") ) {
        printf("nome:%s\n", (*cmds)->name);
    }
    if( strcmp((*cmds)->type," ") ) {
        printf("type:%s\n", (*cmds)->type);
    }
    printf("dimension:%d\n", (*cmds)->dimension);
    if( strcmp((*cmds)->comment," ") ) {
        printf("comment:%s\n", (*cmds)->comment);
    }
    if( strcmp((*cmds)->edgeType," ") ) {
        printf("edgeType:%s\n", (*cmds)->edgeType);
    }
    if( strcmp((*cmds)->edgeFormat," ") ) {
        printf("edgeFormat:%s\n", (*cmds)->edgeFormat);
    }
    if( strcmp((*cmds)->dataType," ") ) {
        printf("dataType:%s\n", (*cmds)->dataType);
    }
    for( int i=0; i < (*cmds)->dimension; i++ )
    {
        for( int j=0; j < (*cmds)->dimension;j++ )
        {
            printf("%d ", (*cmds)->edgeSection[i][j]);
        }
        printf("\n");
    }
}

int contains( char *string, char *substring ) {
    if(strstr(string, substring) != NULL) {
        return 1;
    } else {
        return 0;
    }
}

void completaMatriz( int ***edgeSection, char *edgeFormat, int dimension ) {
    for(int linha=0;linha<dimension;linha++) {
        for(int coluna=0;coluna<dimension;coluna++) {
            if( contains(edgeFormat, "UPPER") ) {
                (*edgeSection)[coluna][linha] = (*edgeSection)[linha][coluna];
            } else if( contains(edgeFormat, "LOWER" ) ) { 
                (*edgeSection)[linha][coluna] = (*edgeSection)[coluna][linha];
            }
        }
    }
}

void gulosa( infArq **cmds )
{
    int cidadeOrigem = 0;
    int vetAux[(*cmds)->dimension];
    int total = 0;
    int cidadeDestino =1;
    int count = 0;
    int menor = (*cmds)->edgeSection[cidadeOrigem][cidadeDestino];
    
    for(int i=0; i<(*cmds)->dimension;i++)
    {
        vetAux[i]=(*cmds)->edgeSection[i][cidadeOrigem];
        (*cmds)->edgeSection[i][cidadeOrigem] = 0;
    }
    
    while(count<(*cmds)->dimension-1)
    {
        for(int aux=0;aux<(*cmds)->dimension;aux++)
        {
            if((*cmds)->edgeSection[cidadeOrigem][aux]<menor && (*cmds)->edgeSection[cidadeOrigem][aux]!=0)
            {
                cidadeDestino = aux;
                menor = (*cmds)->edgeSection[cidadeOrigem][aux];
            }
        }
        //ao final
        total = total + menor;
         printf("cidade origem: %d cidade destino: %d gasto: %d\n", cidadeOrigem, cidadeDestino, menor);
        cidadeOrigem = cidadeDestino;
        cidadeDestino = 0;
        menor = 9999;//Tem que arrumar isso aqui 
        for(int i=0; i<(*cmds)->dimension;i++)
        {
            (*cmds)->edgeSection[i][cidadeOrigem] = 0;
        }
        count++;
        }
    total = total + vetAux[cidadeOrigem];
    printf("****\n");
    printf("%d\n", total);
    printf("****\n");
}
