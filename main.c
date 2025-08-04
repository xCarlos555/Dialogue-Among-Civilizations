#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int **dados;
    int linhas;
    int colunas;
} matriz_t;

// ===== Configurações =====
const char NOME_ARQUIVO[] = "input.txt";
#define MAX_CIVS 10

// Prototipos
void aloca_matriz(matriz_t *matriz);
void free_matriz(matriz_t *matriz);
int verificar_paz(matriz_t *matriz);
int verificar_valores(matriz_t *matriz);
int verificar_simetria(matriz_t *matriz);
int dialogo(int *seq_dialogo, matriz_t *matriz);
int gerar_sequencia(int *seq_dialogo, int k, matriz_t *matriz);
void imprimir_matriz(matriz_t *matriz);
void guardar_matriz_em_ficheiro(matriz_t *matriz, const char *nome_ficheiro);
void gerar_grafo_python(const char *ficheiro_python, const char *ficheiro_matriz);

void aloca_matriz(matriz_t *matriz) {
    matriz->dados = (int **)malloc(matriz->linhas * sizeof(int *));
    for (int i = 0; i < matriz->linhas; i++)
        matriz->dados[i] = (int *)malloc(matriz->colunas * sizeof(int));
}

void free_matriz(matriz_t *matriz) {
    for (int i = 0; i < matriz->linhas; i++)
        free(matriz->dados[i]);
    free(matriz->dados);
}

int verificar_paz(matriz_t *matriz) {
    for (int i = 0; i < matriz->linhas; i++) {
        for (int j = 0; j < matriz->colunas; j++) {
            if (matriz->dados[i][j] < 0)
                return 0;
        }
    }
    return 1;
}

int verificar_valores(matriz_t *matriz) {
    for (int i = 0; i < matriz->linhas; i++) {
        for (int j = 0; j < matriz->colunas; j++) {
            if (matriz->dados[i][j] < -100 || matriz->dados[i][j] > 100)
                return 0;
        }
    }
    return 1;
}

int verificar_simetria(matriz_t *matriz) {
    for (int i = 0; i < matriz->linhas; i++) {
        if (matriz->dados[i][i] != 0)
            return 0;

        for (int j = 0; j < matriz->colunas; j++) {
            if (matriz->dados[i][j] != matriz->dados[j][i])
                return 0;
        }
    }
    return 1;
}

void copiar_matriz(matriz_t *origem, matriz_t *destino) {
    for (int i = 0; i < origem->linhas; i++) {
        for (int j = 0; j < origem->colunas; j++) {
            destino->dados[i][j] = origem->dados[i][j];
        }
    }
}

void imprimir_matriz(matriz_t *matriz) {
    printf("\nInitial relations between civilizations (%d civilizations):\n", matriz->linhas);
    printf("--------------------------------------------------------\n");
    for (int i = 0; i < matriz->linhas; i++) {
        for (int j = 0; j < matriz->colunas; j++) {
            printf("%5d ", matriz->dados[i][j]);
        }
        printf("\n");
    }
    printf("--------------------------------------------------------\n");
}

void guardar_matriz_em_ficheiro(matriz_t *matriz, const char *nome_ficheiro) {
    FILE *out = fopen(nome_ficheiro, "w");
    fprintf(out, "%d\n", matriz->linhas);
    for (int i = 0; i < matriz->linhas; i++) {
        for (int j = 0; j < matriz->colunas; j++) {
            fprintf(out, "%d ", matriz->dados[i][j]);
        }
        fprintf(out, "\n");
    }
    fclose(out);
}

void gerar_grafo_python(const char *ficheiro_python, const char *ficheiro_matriz) {
    char comando[200];
    sprintf(comando, "python %s %s", ficheiro_python, ficheiro_matriz);
    system(comando);
}

int dialogo(int *seq_dialogo, matriz_t *matriz_original) {
    matriz_t matriz;
    matriz.linhas = matriz_original->linhas;
    matriz.colunas = matriz_original->colunas;
    aloca_matriz(&matriz);

    copiar_matriz(matriz_original, &matriz);

    int sequencia_real[200];
    int passo = 0;

    for (int idx = 0; idx < matriz.linhas - 1; idx++) {
        int civilizacao = seq_dialogo[idx] - 1;

        // Realiza diálogo
        for (int j = 0; j < matriz.linhas; j++) {
            matriz.dados[0][j] += matriz.dados[civilizacao][j];
            matriz.dados[civilizacao][j] = matriz.dados[0][j];
        }

        // Zeros na diagonal e simetria
        for (int i = 0; i < matriz.linhas; i++) {
            matriz.dados[i][i] = 0;
            for (int j = 0; j < matriz.colunas; j++) {
                matriz.dados[j][i] = matriz.dados[i][j];
            }
        }

        sequencia_real[passo++] = civilizacao + 1;

        if (verificar_paz(&matriz)) {
            printf("\n====================\n");
            printf("Peace achieved!\n");
            printf("Dialogue sequence (actions by Civilization 1): ");
            for (int i = 0; i < passo; i++) {
                printf("Civ %d", sequencia_real[i]);
                if (i < passo - 1) printf(" -> ");
            }
            printf("\n====================\n");

            guardar_matriz_em_ficheiro(&matriz, "final_matrix.txt");
            gerar_grafo_python("gerar_grafo_final.py", "final_matrix.txt");

            free_matriz(&matriz);
            return 1; // PAZ
        }
    }

    free_matriz(&matriz);
    return 0; // SEM PAZ
}

int gerar_sequencia(int *seq_dialogo, int k, matriz_t *matriz) {
    static int num = 0;
    int paz = 0;

    num++;
    seq_dialogo[k] = num;

    if (num == matriz->linhas) {
        paz = dialogo(seq_dialogo, matriz);  // guardar retorno
    } else {
        for (int i = 0; i < matriz->linhas - 1 && !paz; i++) {
            if (seq_dialogo[i] == 0 || seq_dialogo[i] == 1)
                paz = gerar_sequencia(seq_dialogo, i, matriz);
        }
    }

    num--;
    seq_dialogo[k] = 0;
    return paz;  // devolver estado
}

int main() {
    FILE *arquivo = fopen(NOME_ARQUIVO, "r");

    if (!arquivo) {
        printf("Error: could not open file '%s'\n", NOME_ARQUIVO);
        return 1;
    }

    int civ;
    fscanf(arquivo, "%d", &civ);

    if (civ < 2 || civ > MAX_CIVS) {
        printf("Error: number of civilizations must be between 2 and %d\n", MAX_CIVS);
        fclose(arquivo);
        return 1;
    }

    matriz_t matriz;
    matriz.linhas = civ;
    matriz.colunas = civ;
    aloca_matriz(&matriz);

    for (int i = 0; i < civ; i++) {
        for (int j = 0; j < civ; j++) {
            fscanf(arquivo, "%d", &matriz.dados[i][j]);
        }
    }

    fclose(arquivo);

    // validações
    if (!verificar_valores(&matriz) || !verificar_simetria(&matriz)) {
        printf("Error: invalid matrix values or not symmetric\n");
        free_matriz(&matriz);
        return 1;
    }

    // Mostra a matriz inicial
    imprimir_matriz(&matriz);

    // Gerar grafo inicial
    guardar_matriz_em_ficheiro(&matriz, "initial_matrix.txt");
    gerar_grafo_python("gerar_grafo_inicial.py", "initial_matrix.txt");

    // Mensagem de processamento
    printf("\nProcessing dialogue sequences to check for possible peace...\n");

    // inicia processo
    int seq_dialogo[200] = {0};
    int paz = gerar_sequencia(seq_dialogo, 0, &matriz);

    if (!paz) {
        printf("\n====================\n");
        printf("No peace was achieved.\n");
        printf("====================\n");
        guardar_matriz_em_ficheiro(&matriz, "final_matrix.txt");
        gerar_grafo_python("gerar_grafo_final.py", "final_matrix.txt");
    }

    free_matriz(&matriz);

    if (remove("initial_matrix.txt") != 0)
        perror("Error deleting initial_matrix.txt");
    if (remove("final_matrix.txt") != 0)
        perror("Error deleting final_matrix.txt");

    return 0;
}
