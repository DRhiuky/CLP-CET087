// nome: Luiz Augusto Bello Marques dos Anjos
// Matrícula: 202010242

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Analisador léxico para números decimais
void analisador_lexical_decimal(char *palavra) {
    size_t i = 0;
    
    // Estado inicial
    int estado = 0;
    G1:
    if (palavra[i] >= '0' && palavra[i] <= '9') {
        estado = 1;
        i++;
        if (palavra[i] == '\0') {
            goto FIM;
        }
        goto G1;
    } else {
        estado = 0;
        goto FIM;
    }

    FIM:
    if (estado == 1){
        printf("%s --> reconhecida\n", palavra);
    } else {
        printf("%s --> rejeitada\n", palavra);
    }
}

int main() {
    char palavra[256];
    
    FILE *file = fopen("palavras.txt", "r");
    if (file == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
        return 0;
    }

    while (fscanf(file, "%s", palavra) != EOF) {
        analisador_lexical_decimal(palavra);
    }

    fclose(file);
    return 0;
}