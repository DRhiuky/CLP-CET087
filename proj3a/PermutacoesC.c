#include <stdio.h>
#include <time.h>

// Função para calcular o fatorial de um número
unsigned long long fatorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    unsigned long long resultado = 1;
    for (int i = 2; i <= n; i++) {
        resultado *= i;
    }
    return resultado;
}

int main() {
    int n;
    clock_t inicio, fim;
    double tempo_gasto;

    printf("Digite um numero para calcular seu fatorial: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("O fatorial não está definido para numeros negativos.\n");
    } else {
        inicio = clock();
        unsigned long long resultado = fatorial(n);
        fim = clock();

        tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

        printf("O fatorial de %d e: %llu\n", n, resultado);
        printf("Tempo gasto para calcular: %f segundos\n", tempo_gasto);
    }

    return 0;
}
