#include "quiz.h"

// Carrega uma questão a partir de um arquivo de texto
void carregarQuestao(const char *caminho, Questao *q) {
    FILE *arquivo = fopen(caminho, "r");
    
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", caminho);
        return;
    }
    
    // Lê a pergunta (primeira linha)
    fgets(q->pergunta, sizeof(q->pergunta), arquivo);
    q->pergunta[strcspn(q->pergunta, "\n")] = 0;  // Remove quebra de linha
    
    // Lê as alternativas
    fgets(q->alternativaA, sizeof(q->alternativaA), arquivo);
    q->alternativaA[strcspn(q->alternativaA, "\n")] = 0;
    
    fgets(q->alternativaB, sizeof(q->alternativaB), arquivo);
    q->alternativaB[strcspn(q->alternativaB, "\n")] = 0;
    
    fgets(q->alternativaC, sizeof(q->alternativaC), arquivo);
    q->alternativaC[strcspn(q->alternativaC, "\n")] = 0;
    
    fgets(q->alternativaD, sizeof(q->alternativaD), arquivo);
    q->alternativaD[strcspn(q->alternativaD, "\n")] = 0;
    
    // Lê o gabarito (última linha)
    char gabarito[10];
    fgets(gabarito, sizeof(gabarito), arquivo);
    q->gabarito = gabarito[0];  // Pega apenas o primeiro caractere
    
    fclose(arquivo);
}

// Exibe a questão no terminal
void exibirQuestao(const Questao *q) {
    printf("\n");
    printf("=====================================\n");
    printf("PERGUNTA:\n%s\n\n", q->pergunta);
    printf("A) %s\n", q->alternativaA);
    printf("B) %s\n", q->alternativaB);
    printf("C) %s\n", q->alternativaC);
    printf("D) %s\n", q->alternativaD);
    printf("=====================================\n");
}

// Obtém a resposta do usuário
char obterRespostaUsuario(void) {
    char resposta;
    printf("Digite sua resposta (A, B, C ou D): ");
    scanf(" %c", &resposta);
    
    // Converte para maiúscula se necessário
    if (resposta >= 'a' && resposta <= 'd') {
        resposta = resposta - 32;  // Converte para maiúscula
    }
    
    return resposta;
}

// Verifica se a resposta está correta
int verificarResposta(char respostaUsuario, char gabarito) {
    return (respostaUsuario == gabarito) ? 1 : 0;
}

// Conta quantos arquivos .txt existem em um diretório
int contarArquivos(const char *diretorio) {
    DIR *dir = opendir(diretorio);
    struct dirent *entrada;
    int contador = 0;
    
    if (dir == NULL) {
        printf("Erro ao abrir diretório: %s\n", diretorio);
        return 0;
    }
    
    while ((entrada = readdir(dir)) != NULL) {
        // Verifica se o arquivo tem extensão .txt
        if (entrada->d_type == DT_REG && strstr(entrada->d_name, ".txt") != NULL) {
            contador++;
        }
    }
    
    closedir(dir);
    return contador;
}

// Obtém um arquivo aleatório do diretório
char* obterDificuldadeUsuario(void) {
    static char dificuldade[20];
    
    printf("\nEscolha a dificuldade:\n");
    printf("1) Fácil\n");
    printf("2) Médio\n");
    printf("3) Difícil\n");
    printf("Digite sua escolha (1, 2 ou 3): ");
    
    int escolha;
    scanf("%d", &escolha);
    
    switch (escolha) {
        case 1:
            strcpy(dificuldade, "facil");
            break;
        case 2:
            strcpy(dificuldade, "medio");
            break;
        case 3:
            strcpy(dificuldade, "dificil");
            break;
        default:
            strcpy(dificuldade, "facil");
    }
    
    return dificuldade;
}

// Seleciona uma questão aleatória de um diretório
int selecionarQuestaoAleatoria(const char *diretorio, char *caminho_selecionado) {
    DIR *dir = opendir(diretorio);
    struct dirent *entrada;
    int totalArquivos = contarArquivos(diretorio);
    
    if (dir == NULL || totalArquivos == 0) {
        return 0;
    }
    
    int aleatorio = rand() % totalArquivos;
    int contador = 0;
    
    rewinddir(dir);
    
    while ((entrada = readdir(dir)) != NULL) {
        if (entrada->d_type == DT_REG && strstr(entrada->d_name, ".txt") != NULL) {
            if (contador == aleatorio) {
                snprintf(caminho_selecionado, 256, "%s/%s", diretorio, entrada->d_name);
                closedir(dir);
                return 1;
            }
            contador++;
        }
    }
    
    closedir(dir);
    return 0;
}
