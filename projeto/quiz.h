#ifndef QUIZ_H
#define QUIZ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>

// Estrutura para armazenar uma questão
typedef struct {
    char pergunta[256];
    char alternativaA[100];
    char alternativaB[100];
    char alternativaC[100];
    char alternativaD[100];
    char gabarito;  // 'A', 'B', 'C' ou 'D'
} Questao;

// Estrutura para armazenar um arquivo de questão
typedef struct {
    char caminho[256];
} ArquivoQuestao;

// Funções do sistema de quiz
void carregarQuestao(const char *caminho, Questao *q);
void exibirQuestao(const Questao *q);
char obterRespostaUsuario(void);
int verificarResposta(char respostaUsuario, char gabarito);
int contarArquivos(const char *diretorio);
void obterArquivosAleatorios(const char *diretorio, ArquivoQuestao *arquivos, int total);
char* obterDificuldadeUsuario(void);

#endif
