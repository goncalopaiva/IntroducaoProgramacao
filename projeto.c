//
// IAPG - 2020/2021
// Gonçalo Paiva (39807) e João Miranda (40229)
//

void print_jogadores();


#include "projeto.h"

PERGUNTA perguntas [NUM_PERGUNTAS];
JOGADOR jogadores [NUM_JOGADORES];
int num_jogadores;
const int nrPerguntasPartida=0; //Utilizador determina quantas perguntas terá a partida
PERGUNTA perguntas_partida [nrPerguntasPartida];

int main_projeto() {

    //1. Le ficheiro e carrega as perguntas para "perguntas"
    //2. Inicializacao jogadores: pergunta quantos jogadores ("num_jogadores") e nomes de cada jogador. Carrega para "jogadores"
    //3. Pergunta quantas perguntas terá a partida e guarda em "nrPerguntasPartida"
    //4. Pergunta qual o modo de jogo (aleatório -> "" ou por categoria -> "")
    //5. Conforme o numero de perguntas e o modo de jogo carrega as perguntas para "perguntas_partida"
    //6. Inicia o jogo. Mostra a pergunta e opcoes. O utilizador insere a opçao. Verifica se está correto. Altera pontuação.
    //7. Guardar os dados da partida no ficheiro "partidas.csv"
    //8. Depois de todas as perguntas apresentar o vencedor.

    //........................................................

    read_file();
    init_jogadores();
    modo_jogo();
    start_game();
    write_file();
    print_resultados();
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
        printf("Insira o nome do jogador %d:  ",i+1);
        scanf("%s",jogadores[i].nome);
        jogadores[i].id = i+1;
        jogadores[i].pontuacao = 0;
    }
    printf("\n\n");
}

int start_game() {
    int opcao;
    printf("* * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * V A M O S  C O M E C A R * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * * *\n\n");

    for (int i=0; i<nrPerguntasPartida; i++) {
        for (int j=0; j<num_jogadores; j++){
            printf("\n%s\n\t1. %s\t2. %s\t3. %s\n",perguntas[i].pergunta,perguntas[i].opcao1,perguntas[i].opcao2,perguntas[i].opcao3);
            printf("Reposta: ");
            scanf("%d", &opcao);

            if (check_resposta(perguntas[i].opcao1, perguntas[i].opcao2, perguntas[i].opcao3, opcao, perguntas[i].resposta) == 1) {
                jogadores[j].pontuacao++;
            }
        }
    }
}

void modo_jogo() {
    int modo_jogo;
    printf("\nQuantas perguntas terá a partida? ");
    scanf("%d",&nrPerguntasPartida);
    printf("\nDeseja perguntas aleatorias (1) ou perguntas por categoria (2)? ");
    scanf("%d",&modo_jogo);
    if (modo_jogo==1) {
        //perguntas aleatorias
    } else if (modo_jogo==2) {
        //perguntas por categorias
    }
}

void print_categorias() {
    char categorias[NUM_PERGUNTAS];
    for (int i=0; i<NUM_PERGUNTAS; i++) {
        categorias[i] = *(perguntas+i)->categoria;
    }
    for (int i=0; i<strlen(categorias); i++) {
        if (categorias[i+1]==categorias[i]){
            categorias[i] = ' ';
        }
    }
    for (int i=0; i<strlen(categorias);i++) {
        if (categorias[i] == ' '){
            categorias[i]=categorias[i+1];
        }
    }
    printf("\nCATEGORIAS: ");
    for (int i=0; i<NUM_PERGUNTAS; i++){
        printf("%c \t",categorias[i]);
    }


}

int check_resposta(char op1[], char op2[], char op3[], char opcao, char resposta()) {
    int resposta_certa;
    if (op1 == resposta) {
        resposta_certa=1
    } else if (op2[] == resposta[]) {
        resposta_certa=2;
    } else if (op3[] == resposta[]) {
        resposta_certa=3;
    }

    //VERIFICAR SE A OPCAO ESCOLHIDA ESTA CORRETA
    if (opcao == resposta_certa) {
        return 1;
    } else {
        return 0;
    }
}

int write_file () {


}

void print_resultados () {
    printf("* * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * *  V E N C E D O R  * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * * *\n\n");

    char vencedor[15];

    //print vencedor e pontos
    for (int i=0; i<num_jogadores; i++) {
        if (jogadores[i+1].pontuacao > jogadores[i].pontuacao) {
            for (int j=0; j<strlen(jogadores[i+1].nome)) {
                vencedor[j] = jogadores[i+1].nome[j];
            }
        }
    }

    printf("%s",vencedor);

    for (int i=0; i<num_jogadores; i++) {
        printf("%d \t%s \t%d",jogadores[i].id, jogadores[i].nome, jogadores[i].pontuacao);
    }


}

