// nome: Luiz Augusto Bello Marques dos Anjos
// Matrícula: 202010242

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Analisador léxico para números decimais
void analisador_lexical_decimal(char *palavra) {
    int estado = 0;
    size_t i;
    for (i = 0; i < strlen(palavra); i++) {
        if (palavra[i] >= '0' && palavra[i] <= '9') {
            estado = 1;
        } else {
            estado = 0;
            break;
        }
    }
    if (estado == 1)
        printf("%s --> reconhecida\n", palavra);
    else
        printf("%s --> rejeitada\n", palavra);
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