#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para criar vetores aleatórios
void criaVetores(int vetores[][100], int num_Vetores, int tam_vetores) {
    int i, j;
    srand(time(NULL));
    for (i = 0; i < num_Vetores; i++) {
        for (j = 0; j < tam_vetores; j++) {
            vetores[i][j] = rand() % 1000; // números inteiros aleatórios entre 0 e 999
        }
    }
}

// Função para ordenar vetor usando o algoritmo de ordenação por inserção
void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Função para embaralhar vetor
void embaralha_Vetor(int arr[], int n) {
    srand(time(NULL));
    if (n > 1) {
        int i;
        for (i = n - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
}

int main() {
    int vetores[1024][100];
    int i, j, n = 100;
    int x = 1024; // Número de ciclos

    // Gerar vetores aleatórios
    criaVetores(vetores, 1024, n);

    // Abrir arquivo para escrita
    FILE *fp = fopen("tempos3_c.txt", "w");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo para escrita.\n");
        return 1;
    }

    while (x > 0) {
        // Medir o tempo de execução
        clock_t begin = clock();

        // Ordenar 1024 vetores e registrar o tempo de execução
        for (i = 0; i < 1024; i++) {
            insertionSort(vetores[i], n);
        }

        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

        // Escrever o tempo de processamento no arquivo
        fprintf(fp, "%.9f\n", time_spent);

        x--; // Decrementa o número de ciclos

        // Re-embaralha os vetores para proximo ciclo
        for (i = 0; i < 1024; i++) {
            embaralha_Vetor(vetores[i], n);
        }
    }

    // Fechar arquivo
    fclose(fp);
    return 0;
}