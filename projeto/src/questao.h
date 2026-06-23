#ifndef QUESTAO_H
#define QUESTAO_H

typedef struct {
    char pergunta[500];
    char alternativa_a[200];
    char alternativa_b[200];
    char alternativa_c[200];
    char alternativa_d[200];
    char gabarito;
} Questao;

typedef struct {
    Questao *questoes;
    int total;
} ConjuntoQuestoes;

// Funções
Questao carregar_questao(const char *caminho);
ConjuntoQuestoes carregar_questoes_dificuldade(const char *diretorio);
int validar_resposta(Questao questao, char resposta);
void exibir_questao(Questao questao, int numero);
void liberar_questoes(ConjuntoQuestoes conjunto);

#endif