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



int main_projeto() {

    //TODO -> Modo de jogo. Decidir se é aleatorio ou perguntas por categoria e depois carregar as perguntas para a struct correspondente.
    //TODO -> Carregar para o ficheiro "partidas.csv" os dados da partida no final do jogo.

    //........................................................

    read_file(); //Sim
    init_jogadores(); //Sim
    modo_jogo();
    start_game();
    write_file();
    print_resultados(); //Sim
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
    printf("Insira o numero de jogadores:  ");
    scanf("%d", &num_jogadores);
    printf("\n");
    for (int i=0; i<num_jogadores; i++) {
        printf("Insira o nome do jogador %d:  ", i+1);
        fgets(jogadores[i].nome,TAM_VECTOR,stdin);
        //scanf("%s",jogadores[i].nome);
        jogadores[i].id = i+1;
        jogadores[i].pontuacao = 0;
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
            perguntas_partida[i] = perguntas[rand()];
        }


    } else if (mdjogo==2) {
        //perguntas por categoria
        print_categorias();
        printf("Introduza a categoria: ");
        fgets(categoria_escolhida, TAM_VECTOR, stdin);

    }
}

int start_game() {
    char opcao;
    printf("* * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * V A M O S  C O M E C A R * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * * *\n\n");

    for (int i=0; i<nrPerguntasPartida; i++) {
        for (int j=0; j<num_jogadores; j++){
            printf("\n%s\n\t1. %s\t2. %s\t3. %s\n",perguntas[i].pergunta,perguntas[i].opcao1,perguntas[i].opcao2,perguntas[i].opcao3);
            printf("Reposta: ");
            scanf("%c", &opcao);

            if (check_resposta(perguntas[i].opcao1, perguntas[i].opcao2, perguntas[i].opcao3, opcao, perguntas[i].resposta) == 1) {
                jogadores[j].pontuacao++;
            }
        }
    }
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
    printf("* * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * *  V E N C E D O R  * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * * *\n\n");

    for (int i=0; i<num_jogadores; i++) {
        if (jogadores[i+1].pontuacao > jogadores[i].pontuacao) {
            strcpy(vencedor[0].nome, jogadores[i+1].nome);
            vencedor[0].pontuacao = jogadores[i+1].pontuacao;
        }
    }

    printf("VENCEDOR: %s \t\t PONTUAÇÃO: %d \n\n",vencedor[0].nome, vencedor[0].pontuacao);

    for (int i=0; i<num_jogadores; i++) {
        printf("%d \t%s \t%d \n",jogadores[i].id, jogadores[i].nome, jogadores[i].pontuacao);
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

int check_resposta(char *op1, char *op2, char *op3, char opcao, char *resposta) {
    int resposta_certa;

    if (strcmp(op1, resposta) == 0) {
        resposta_certa=1;
    }
    if (strcmp(op2, resposta) == 0) {
        resposta_certa=2;
    }
    if (strcmp(op3, resposta) == 0) {
        resposta_certa=3;
    }
    //VERIFICAR SE A OPCAO ESCOLHIDA ESTA CORRETA
    if (opcao == resposta_certa) {
        return 1;
    } else {
        return 0;
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






