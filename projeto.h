//
// IAPG - 2020/2021
// Gonçalo Brandão Paiva, 39807
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef PROJETOIAPG2021_PROJETO_H
#define PROJETOIAPG2021_PROJETO_H

#define TAM_VECTOR 150
#define NUM_PERGUNTAS 6
#define NUM_JOGADORES 10

typedef struct perguntas {
    char categoria[TAM_VECTOR];
    char pergunta[TAM_VECTOR];
    char opcao1[TAM_VECTOR];
    char opcao2[TAM_VECTOR];
    char opcao3[TAM_VECTOR];
    char resposta[TAM_VECTOR];
} PERGUNTA;

typedef struct jogadores {
    int num_jogadores;
    int id;
    char nome[TAM_VECTOR];
    int pontuacao;
} JOGADOR;

int main_projeto();

/**
 * Função que pede ao utilizador o numero de jogadores e os respetivos nomes.
 */
void init_jogadores();

/**
 * Funcao que lê as perguntas do ficheiro.
 * Categoria;Pergunta;Opcao1;Opcao2;Opcao3;Resposta
 * @return
 */
int read_file();

/**
 * Funcao que pergunta ao utilizador o modo de jogo
 */
void modo_jogo();

/**
 * Funcao que lista de perguntas.
 */
void print_perguntas();

/**
 * Funcao que lista as categorias.
 */
void print_categorias();

#endif //PROJETOIAPG2021_PROJETO_H
