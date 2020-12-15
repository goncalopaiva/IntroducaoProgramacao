//
// UFP - IAPG - 2020/2021
// Gonçalo Paiva (39807) e João Miranda (40229)
//

#include "projeto.h"

PERGUNTA perguntas [NUM_PERGUNTAS]; //Struct com todas as perguntas carregadas do ficheiro.
JOGADOR jogadores [NUM_JOGADORES]; //Struct com os jogadores.
JOGADOR vencedor [1]; //Struct para guardar os dados do vencedor.
PERGUNTA perguntas_partida[PERGUNTAS_PARTIDA]; //Struct com as perguntas que vão ser usadas no jogo.
CATEGORIA categorias [NUM_PERGUNTAS];

int num_jogadores=1;
int nrPerguntasPartida; //Utilizador determina quantas perguntas terá a partidagit

void print_pontuacao();

int main_projeto() {

    //TODO -> Modo de jogo. Decidir se é aleatorio ou perguntas por categoria e depois carregar as perguntas para a struct correspondente.
    //TODO -> Carregar para o ficheiro "partidas.csv" os dados da partida no final do jogo.

    //TODO -> funcao check_respostas nao esta a funcionar bem

    //........................................................

    read_file(); //Sim
    init_jogadores(); //Sim
    modo_jogo();
    fflush(stdin);
    start_game();
    write_file();
    print_resultados(); //Sim

    printf("\n\n<Enter> para sair\n");
    getchar();
}

int read_file() {
    FILE *fp = fopen("perguntas.csv","r");

    if (!fp) {
        perror("Impossivel abrir o ficheiro.\n");
        return 0;
        // exit(1);
    }
    char buff[1024];
    int row_count = 0;
    int field_count = 0;
    int i = 0;

    while (fgets(buff, 1024, fp)) {
        field_count = 0;
        row_count++;
        if (row_count == 1) {
            continue; //Para não carregar as etiquetas (linhha 1 do ficheiro .csv
        }
        char *field = strtok(buff, ";");
        while (field) {
            //Categoria;Pergunta;Opcao1;Opcao2;Opcao3;Resposta
            if (field_count == 0) {
                strcpy(perguntas[i].categoria, field);
            }
            if (field_count == 1) {
                strcpy(perguntas[i].pergunta, field);
            }
            if (field_count == 2) {
                strcpy(perguntas[i].opcao1, field);
            }
            if (field_count == 3) {
                strcpy(perguntas[i].opcao2, field);
            }
            if (field_count == 4) {
                strcpy(perguntas[i].opcao3, field);
            }
            if (field_count == 5) {
                strcpy(perguntas[i].resposta, field);
            }
            field = strtok(NULL, ";");
            field_count++;
        }
        i++;
    }
    fclose(fp);
}

void init_jogadores() {
    fflush(stdin);
    printf("Insira o numero de jogadores: ");
    scanf("%d",&num_jogadores);
    printf("\n");
    fflush(stdin);
    for (int i=0; i<num_jogadores; i++) {
        printf("Insira o nome do jogador %d:  ", i+1);
        fgets(jogadores[i].nome,TAM_VECTOR,stdin);
        //scanf("%s",jogadores[i].nome);
        jogadores[i].id = i+1;
        jogadores[i].pontuacao = 0;
        fflush(stdin);
    }
    printf("\n");
}

void modo_jogo() {
    int mdjogo;
    char categoria_escolhida[TAM_VECTOR];
    printf("\nQuantas perguntas tera a partida? ");
    scanf("%d",&nrPerguntasPartida);
    printf("\nDeseja perguntas aleatorias (1) ou perguntas por categoria (2)? ");
    scanf("%d",&mdjogo);
    if (mdjogo==1) {
        //perguntas aleatorias

        for (int i=0; i<nrPerguntasPartida; i++) {
            int pergunta_random = rand() %nrPerguntasPartida;
            perguntas_partida[i] = perguntas[pergunta_random];
        }


    } else if (mdjogo==2) {
        //perguntas por categoria
        print_categorias();
        printf("Introduza a categoria: ");
        fgets(categoria_escolhida, TAM_VECTOR, stdin);

    }
}

int start_game() {
    int opcao;
    printf("\n\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * V A M O S   C O M E C A R * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * * * *\n\n");

    for (int i=0; i<nrPerguntasPartida; i++) {
        char opcao1[TAM_VECTOR], opcao2[TAM_VECTOR], opcao3[TAM_VECTOR], resposta_correta[TAM_VECTOR];
        int int_resposta_correta;

        strcpy(opcao1, perguntas[i].opcao1);
        strcpy(opcao2, perguntas[i].opcao2);
        strcpy(opcao3, perguntas[i].opcao3);
        strcpy(resposta_correta, perguntas[i].resposta);

        strtok(resposta_correta, "\n");

        if (strcmp(opcao1, resposta_correta) == 0) int_resposta_correta=1;
        if (strcmp(opcao2, resposta_correta) == 0) int_resposta_correta=2;
        if (strcmp(opcao3, resposta_correta) == 0) int_resposta_correta=3;

        for (int j=0; j<num_jogadores; j++) {
            fflush(stdin);
            printf("JOGADOR %d: %s",jogadores[j].id,jogadores[j].nome);
            printf("%d. %s\n1. %s\t2. %s\t3. %s\n",i+1,perguntas[i].pergunta,perguntas[i].opcao1,perguntas[i].opcao2,perguntas[i].opcao3);
            printf("Reposta: ");
            scanf("%d", &opcao);

            if (opcao == int_resposta_correta) {
                jogadores[j].pontuacao++;
            }
            printf("\n\n");
        }
    }
    fflush(stdin);
}

int write_file () {
    //Data; Hora; Vencedor; Pontuacao

    FILE *fp = fopen("partidas.csv","a");

    if (!fp) {
        perror("Impossivel abrir o ficheiro.\n");
        return 0;
    }

    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);

    fprintf(fp, "%d-%d-%d;%d:%d;%s;%d",tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900,tm.tm_hour, tm.tm_min, vencedor[0].nome, vencedor[0].pontuacao);

    fclose(fp);
}

void print_resultados () {
    strcpy(vencedor[0].nome, jogadores[0].nome);
    vencedor[0].pontuacao = jogadores[0].pontuacao;

    for (int i = 1; i < num_jogadores - 1; i++) {
        if (jogadores[i].pontuacao > jogadores[i - 1].pontuacao) {
            strcpy(vencedor[0].nome, jogadores[i].nome);
            vencedor[0].pontuacao = jogadores[i].pontuacao;
        }
    }

    printf("* * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * *  V E N C E D O R  * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * * *\n\n");

    printf("%s ganhou o jogo.\n\n", strtok(vencedor[0].nome, "\n"));

    printf("PONTUACOES:\n");
    for (int i = 0; i < num_jogadores; i++) {
        printf("\tJogador %d. %s \t\tPontuacao: %d\n", jogadores[i].id, strtok(jogadores[i].nome, "\n"), jogadores[i].pontuacao);
    }

}

void print_pontuacao() {
    for (int i=0; i<num_jogadores; i++) {
        printf("\nJogador %d. %s",i+1, jogadores[i].nome);
        printf("Pontuacao: %d \n\n", jogadores[i].pontuacao);
    }
}

void print_perguntas() {

    printf("++++++++ LISTA DE PERGUNTAS E RESPOSTAS ++++++++\n\n");

    for (int i = 0; i < NUM_PERGUNTAS-1; i++) {
        printf("Pergunta %d. %s\n", i+1, perguntas[i].pergunta);
        printf("1. %s \n2. %s \n3. %s \n", perguntas[i].opcao1, perguntas[i].opcao2, perguntas[i].opcao3);
        printf("RESPOSTA: %s \n\n",perguntas[i].resposta);
    }

}


void print_categorias() {
    int size=NUM_PERGUNTAS;
    for (int i=0; i<size-1; i++) {
        strcpy(categorias[i].categoria, perguntas[i].categoria);
    }

    //Remover as categorias duplicadas

    printf("\nCATEGORIAS:\n");
    for (int i=0; i<size-1; i++){
        printf("\t%s \n",categorias[i].categoria);
    }
}






