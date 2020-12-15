//
// UFP - IAPG - 2020/2021
// Gonçalo Paiva (39807) e João Miranda (40229)
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#ifndef PROJETOIAPG2021_PROJETO_H
#define PROJETOIAPG2021_PROJETO_H

#define TAM_VECTOR 150
#define NUM_PERGUNTAS 11
#define NUM_JOGADORES 10
#define PERGUNTAS_PARTIDA 10

typedef struct categorias {
    char categoria [TAM_VECTOR];
} CATEGORIA;

typedef struct perguntas {
    char categoria[TAM_VECTOR];
    char pergunta[TAM_VECTOR];
    char opcao1[TAM_VECTOR];
    char opcao2[TAM_VECTOR];
    char opcao3[TAM_VECTOR];
    char resposta[TAM_VECTOR];
} PERGUNTA;

typedef struct jogadores {
    int id;
    char nome[TAM_VECTOR];
    int pontuacao;
} JOGADOR;

/**
 * Funcao main
 * @return
 */
int main_projeto();

/**
 * Funcao que lê as perguntas do ficheiro.
 * Categoria;Pergunta;Opcao1;Opcao2;Opcao3;Resposta
 * @return
 */
int read_file();

/**
 * Função que pede ao utilizador o numero de jogadores e os respetivos nomes.
 */
void init_jogadores();

/**
 * Funcao principal idk (?)
 * @return
 */
int start_game();

/**
 * Funcao que pergunta ao utilizador o modo de jogo
 */
void modo_jogo();

/**
 * Funcao que lista as categorias.
 */
void print_categorias();

/**
 * Funlão que lista todas as perguntas e respostas
 */
void print_perguntas();

/**
 * Funcao que verifica se a resposta escolhida esta certa ou errada
 * @return
 */
int check_resposta(char op1[], char op2[], char op3[], char opcao, char resposta[]);

/**
 * Função que escreve no ficheiro a partida, hora/dia, e o vencedor
 * @return
 */
int write_file();

/**
 * Funcao que imprime o resultado da partida
 */
void print_resultados();

#endif //PROJETOIAPG2021_PROJETO_H
