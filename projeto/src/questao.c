#include "questao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>

// Carregar uma única questão de um arquivo
Questao carregar_questao(const char *caminho) {
    Questao q;
    FILE *arquivo = fopen(caminho, "r");
    
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir arquivo: %s\n", caminho);
        exit(1);
    }
    
    // Ler pergunta
    fgets(q.pergunta, sizeof(q.pergunta), arquivo);
    q.pergunta[strcspn(q.pergunta, "\n")] = 0; // Remove '\n'
    
    // Ler alternativas
    fgets(q.alternativa_a, sizeof(q.alternativa_a), arquivo);
    q.alternativa_a[strcspn(q.alternativa_a, "\n")] = 0;
    
    fgets(q.alternativa_b, sizeof(q.alternativa_b), arquivo);
    q.alternativa_b[strcspn(q.alternativa_b, "\n")] = 0;
    
    fgets(q.alternativa_c, sizeof(q.alternativa_c), arquivo);
    q.alternativa_c[strcspn(q.alternativa_c, "\n")] = 0;
    
    fgets(q.alternativa_d, sizeof(q.alternativa_d), arquivo);
    q.alternativa_d[strcspn(q.alternativa_d, "\n")] = 0;
    
    // Ler gabarito
    char gabarito_str[10];
    fgets(gabarito_str, sizeof(gabarito_str), arquivo);
    q.gabarito = gabarito_str[0];
    
    fclose(arquivo);
    return q;
}

// Comparar nomes de arquivos para ordenação
int comparar_arquivos(const struct dirent **a, const struct dirent **b) {
    return strcmp((*a)->d_name, (*b)->d_name);
}

// Carregar todas as questões de um diretório
ConjuntoQuestoes carregar_questoes_dificuldade(const char *diretorio) {
    ConjuntoQuestoes conjunto;
    struct dirent **arquivos;
    int count;
    
    // Listar arquivos do diretório
    count = scandir(diretorio, &arquivos, NULL, comparar_arquivos);
    
    if (count < 0) {
        fprintf(stderr, "Erro ao abrir diretório: %s\n", diretorio);
        conjunto.total = 0;
        conjunto.questoes = NULL;
        return conjunto;
    }
    
    // Alocar espaço para questões
    conjunto.questoes = malloc(count * sizeof(Questao));
    conjunto.total = 0;
    
    // Carregar cada questão
    for (int i = 0; i < count; i++) {
        // Pular '.' e '..'
        if (strcmp(arquivos[i]->d_name, ".") == 0 || 
            strcmp(arquivos[i]->d_name, "..") == 0) {
            free(arquivos[i]);
            continue;
        }
        
        // Construir caminho completo
        char caminho[300];
        snprintf(caminho, sizeof(caminho), "%s/%s", 
                 diretorio, arquivos[i]->d_name);
        
        // Carregar questão
        conjunto.questoes[conjunto.total] = carregar_questao(caminho);
        conjunto.total++;
        
        free(arquivos[i]);
    }
    
    free(arquivos);
    return conjunto;
}

// Validar se a resposta está correta
int validar_resposta(Questao questao, char resposta) {
    resposta = toupper(resposta);
    return resposta == toupper(questao.gabarito);
}

// Exibir questão no terminal
void exibir_questao(Questao questao, int numero) {
    printf("\n" "═" "════════════════════════════════════════════\n");
    printf("  Questão %d\n", numero);
    printf("═" "════════════════════════════════════════════\n\n");
    
    printf("%s\n\n", questao.pergunta);
    
    printf("%s\n", questao.alternativa_a);
    printf("%s\n", questao.alternativa_b);
    printf("%s\n", questao.alternativa_c);
    printf("%s\n\n", questao.alternativa_d);
}

// Liberar memória alocada
void liberar_questoes(ConjuntoQuestoes conjunto) {
    if (conjunto.questoes != NULL) {
        free(conjunto.questoes);
    }
}