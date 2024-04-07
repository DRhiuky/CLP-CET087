// nome: Luiz Augusto Bello Marques dos Anjos
// Matrícula: 202010242

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Analisador léxico para números binários
void analisador_lexical_binario(char *palavra) {
    size_t i;
    int estado = 0;
    for (i = 0; i < strlen(palavra); i++) {
        if (palavra[i] == '0' || palavra[i] == '1') {
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
        analisador_lexical_binario(palavra);
    }

    fclose(file);
    return 0;
}

/*
101010 --> reconhecida
11011 --> reconhecida
0 --> reconhecida
1 --> reconhecida
1111 --> reconhecida
1010 --> reconhecida
1001 --> reconhecida
1100 --> reconhecida
1011 --> reconhecida
1110 --> reconhecida
10201 --> rejeitada
1010.1 --> rejeitada
abc --> rejeitada
1234 --> rejeitada
5678 --> rejeitada
9.01 --> rejeitada
10.11 --> rejeitada
2abc --> rejeitada
3def --> rejeitada
4ghi --> rejeitada
*/
