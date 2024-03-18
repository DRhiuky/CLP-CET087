#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define amax 2047       /* maximum address */
#define levmax 3        /* maximum depth of block nesting */
#define cxmax 200       /* size of code array */

typedef enum {lit, opr, lod, sto, cal, inter, jmp, jpc} fct;

typedef struct {
    fct f;
    int l;
    int a;
    char name[5]; // Aumento do tamanho para acomodar todos os nomes de instruções
} instrucao;

instrucao code[cxmax];

void interpret(FILE *output, int instrucao_count) {
    const int stacksize = 500;
    int p, b, t;
    instrucao i;
    int s[stacksize];

    p = 0; b = 1; t = 0;
    memset(s, 0, sizeof(int) * stacksize);

    for (int index = 0; index < instrucao_count; index++) {
        i = code[index];
        switch (i.f) {
            case lit:
                s[++t] = i.a;
                fprintf(output, "%s %d %d %d ", i.name, p, b, t);
                for (int j = 1; j <= t; j++) {
                    fprintf(output, "%d ", s[j]);
                }
                fprintf(output, "\n");
                break;
            case opr:
                switch (i.a) {
                    case 0: /* return */
                        t = b - 1; 
                        p = s[t + 2]; 
                        b = s[t + 1];
                        break;
                    case 1:
                        s[t] = -s[t];
                        break;
                    case 2:
                        t--;
                        s[t] = s[t] + s[t + 1];
                        break;
                    case 3:
                        t--;
                        s[t] = s[t] - s[t + 1];
                        break;
                    case 4:
                        t--;
                        s[t] = s[t] * s[t + 1];
                        break;
                    case 5:
                        t--;
                        s[t] = s[t] / s[t + 1];
                        break;
                    case 6:
                        s[t] = (s[t] % 2);
                        break;
                    case 8:
                        t--;
                        s[t] = (s[t] == s[t + 1]);
                        break;
                    case 9:
                        t--;
                        s[t] = (s[t] != s[t + 1]);
                        break;
                    case 10:
                        t--;
                        s[t] = (s[t] < s[t + 1]);
                        break;
                    case 11:
                        t--;
                        s[t] = (s[t] >= s[t + 1]);
                        break;
                    case 12:
                        t--;
                        s[t] = (s[t] > s[t + 1]);
                        break;
                    case 13:
                        t--;
                        s[t] = (s[t] <= s[t + 1]);
                        break;
                }
                fprintf(output, "%s %d %d %d ", i.name, p, b, t);
                for (int j = 1; j <= t; j++) {
                    fprintf(output, "%d ", s[j]);
                }
                fprintf(output, "\n");
                break;
            case lod:
                s[++t] = s[b + i.a];
                fprintf(output, "%s %d %d %d ", i.name, p, b, t);
                for (int j = 1; j <= t; j++) {
                    fprintf(output, "%d ", s[j]);
                }
                fprintf(output, "\n");
                break;
            case sto:
                s[b + i.a] = s[t];
                fprintf(output, "%s %d %d %d ", i.name, p, b, t);
                for (int j = 1; j <= t; j++) {
                    fprintf(output, "%d ", s[j]);
                }
                fprintf(output, "\n");
                t--;
                break;
            case cal:
                s[t + 1] = b; 
                s[t + 2] = p; 
                s[t + 3] = i.a;
                b = t + 1; 
                p = i.a;
                break;
            case inter:
                t += i.a;
                fprintf(output, "%s %d %d %d ", i.name, p, b, t);
                for (int j = 1; j <= t; j++) {
                    fprintf(output, "%d ", s[j]);
                }
                fprintf(output, "\n");
                break;
            case jmp:
                p = i.a;
                fprintf(output, "%s %d %d %d ", i.name, p, b, t);
                for (int j = 1; j <= t; j++) {
                    fprintf(output, "%d ", s[j]);
                }
                fprintf(output, "\n");
                break;
            case jpc:
                if (s[t] == 0)
                    p = i.a;
                t--;
                fprintf(output, "%s %d %d %d ", i.name, p, b, t);
                for (int j = 1; j <= t; j++) {
                    fprintf(output, "%d ", s[j]);
                }
                fprintf(output, "\n");
                break;
            default:
                printf("Invalid operation code.\n");
                break;
        }
    }
}

void parse_instrucao(const char *line, instrucao *ins) {
    char op[5]; // Aumento do tamanho para acomodar todos os nomes de instruções
    sscanf(line, "%s %d %d", op, &(ins->l), &(ins->a));
    if (strcmp(op, "lit") == 0) {
        ins->f = lit;
        strcpy(ins->name, "lit"); // Atribui o nome da instrução
    } else if (strcmp(op, "opr") == 0) {
        ins->f = opr;
        strcpy(ins->name, "opr"); // Atribui o nome da instrução
    } else if (strcmp(op, "lod") == 0) {
        ins->f = lod;
        strcpy(ins->name, "lod"); // Atribui o nome da instrução
    } else if (strcmp(op, "sto") == 0) {
        ins->f = sto;
        strcpy(ins->name, "sto"); // Atribui o nome da instrução
    } else if (strcmp(op, "cal") == 0) {
        ins->f = cal;
        strcpy(ins->name, "cal"); // Atribui o nome da instrução
    } else if (strcmp(op, "int") == 0) {
        ins->f = inter;
        strcpy(ins->name, "int"); // Atribui o nome da instrução
    } else if (strcmp(op, "jmp") == 0) {
        ins->f = jmp;
        strcpy(ins->name, "jmp"); // Atribui o nome da instrução
    } else if (strcmp(op, "jpc") == 0) {
        ins->f = jpc;
        strcpy(ins->name, "jpc"); // Atribui o nome da instrução
    } else {
        ins->f = -1; // indica que a instrucao e invalida
    }
}

int main() {
    char line[20];
    int index = 0;
    FILE *input_file = fopen("instrucoes.txt", "r");
    FILE *output_file = fopen("resposta.txt", "w");
    int instrucao_count = 0; // Variável para contar o número de instrucoes lidas

    if (input_file == NULL || output_file == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    while (index < cxmax && fgets(line, sizeof(line), input_file)) {
        parse_instrucao(line, &code[index]);
        index++;
        instrucao_count++; // Incrementa o número de instrucoes lidas
    }

    interpret(output_file, instrucao_count); // Passa o número de instrucoes lidas para a função interpret

    fclose(input_file);
    fclose(output_file);

    return 0;   
}
