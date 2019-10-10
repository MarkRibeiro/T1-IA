#include"main.h"
   
int main( int argc, char *argv[ ] ) {
    FILE *f;
    if( argc == 1 ) {
        if( (f = fopen("../Instancias/gr24.tsp", "r") ) == NULL) {
            printf("Erro na abertura do arquivo\n");
            return 0;
        }
    } else {
        if( (f = fopen(argv[1], "r") ) == NULL) {
            printf("Erro na abertura do arquivo\n");
            return 0;
        }
    }
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
    printaInfoArquivo(&cmds);
    gulosa(&cmds);

    fclose(f);
    return 0;
}