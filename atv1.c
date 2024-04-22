#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUNOS 100
#define MAX_NOME 50
#define ARQUIVO_ENTRADA "DadosEntrada.csv"
#define ARQUIVO_SAIDA "SituacaoFinal.csv"

typedef struct {
    char nome[MAX_NOME];
    float nota1;
    float nota2;
    float media;
    char situacao[10];
} Aluno;

// Função para determinar a situação do aluno com base na média
void determinarSituacao(float media, char situacao[]) {
    if (media >= 7.0) {
        strcpy(situacao, "APROVADO");
    } else {
        strcpy(situacao, "REPROVADO");
    }
}

int main() {
    FILE *arquivo_entrada = fopen(ARQUIVO_ENTRADA, "r");
    if (arquivo_entrada == NULL) {
        perror("Erro ao abrir arquivo de entrada");
        return EXIT_FAILURE;
    }

    FILE *arquivo_saida = fopen(ARQUIVO_SAIDA, "w");
    if (arquivo_saida == NULL) {
        perror("Erro ao abrir arquivo de saída");
        fclose(arquivo_entrada);
        return EXIT_FAILURE;
    }

    Aluno alunos[MAX_ALUNOS];
    int num_alunos = 0;

    char linha[MAX_NOME + 20]; // Tamanho máximo da linha

    // Ignorar cabeçalho do arquivo CSV
    fgets(linha, sizeof(linha), arquivo_entrada);

    // Ler os dados do arquivo e calcular a média
    while (fgets(linha, sizeof(linha), arquivo_entrada) != NULL && num_alunos < MAX_ALUNOS) {
        // Extrair os dados da linha
        char nome[MAX_NOME];
        float nota1, nota2;
        if (sscanf(linha, "%49[^,],%*[^,],%*[^,],%f,%f", nome, &nota1, &nota2) == 3) {
            strcpy(alunos[num_alunos].nome, nome);
            alunos[num_alunos].nota1 = nota1;
            alunos[num_alunos].nota2 = nota2;
            alunos[num_alunos].media = (nota1 + nota2) / 2.0;
            determinarSituacao(alunos[num_alunos].media, alunos[num_alunos].situacao);
            fprintf(arquivo_saida, "%s, %.2f, %s\n", alunos[num_alunos].nome, alunos[num_alunos].media, alunos[num_alunos].situacao);
            num_alunos++;
        } else {
            printf("Erro ao ler a linha: %s\n", linha);
        }
    }

    fclose(arquivo_entrada);
    fclose(arquivo_saida);

    printf("Processo concluido.\n");

    return EXIT_SUCCESS;
}
