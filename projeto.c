//
// IAPG - 2020/2021
// Gonçalo Brandão Paiva, 39807
//

#include "projeto.h"

PERGUNTA perguntas [NUM_PERGUNTAS];
JOGADOR jogadores [NUM_JOGADORES];

int read_file() {
    FILE *fp=NULL;
    fp=fopen("perguntas.csv","r");
    fscanf(fp,"%d",&perguntas->num_perguntas);
    if (fp!=NULL)
    {
        int i=0;
        for(i=0;i<perguntas->num_perguntas;i++)
        {
            //Categoria;Pergunta;Opcao1;Opcao2;Opcao3;Resposta
            fscanf(fp,"%s;%s;%s;%s;%s;%s",perguntas[i].categoria,perguntas[i].pergunta,perguntas[i].opcao1,perguntas[i].opcao2,perguntas[i].opcao3,perguntas[i].resposta);
        }
        fclose(fp);
    }
    else
    {
        printf("---------> ERRO NA LEITURA DO FICHEIRO <---------\n\n");
        exit(EXIT_FAILURE);
    }
}

void init_jogadores() {
    printf("Insira o numero de jogadores:  ");
    scanf("%d", &jogadores->num_jogadores);
    for (int i=0; i<jogadores->num_jogadores; i++) {
        printf("Insira o nome do jogador %d:  ",i+1);
        scanf("%s",&jogadores->nome[i]);
        jogadores->id=i+1;
        jogadores->pontuacao=0;
    }
}

void modo_jogo() {
    int modo_jogo;
    printf("Deseja perguntas aleatorias (1) ou perguntas por categoria (2)? ");
    scanf("%d",&modo_jogo);
    if (modo_jogo==1) {
        //perguntas aleatorias
    } else if (modo_jogo==2) {
        //perguntas por categorias
    }
}

void print_perguntas() {
    for (int i=0; i<perguntas->num_perguntas; i++){
        printf("CATEGORIA: %s\n->%s\n1. %s\t2. %s\t3. %s",perguntas[i].categoria,perguntas[i].pergunta,perguntas[i].opcao1,perguntas[i].opcao2,perguntas[i].opcao3);
    }
}

void print_categorias() {
    //ATENÇÃO: Vai imprimir a categoria de cada pergunta. Mudar para imprimir só as categorias diferentes.
    printf("Lista de categorias: \n");
    for (int i=0; i<perguntas->num_perguntas; i++) {
        printf("\t%d. %s\n",i+1, perguntas->categoria);
    }
}


