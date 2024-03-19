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

void print_status(FILE *output, int p, int b, int t, int *s) {
    fprintf(output, "  %d |", p);
    fprintf(output, "(%d %d %d)|", code[p].f, code[p].l, code[p].a);
    fprintf(output, "(%d %d %d)|", p, b, t - 1);
    for (int j = 0; j < t; j++) {
        fprintf(output, " s[%02d]", j + 1);
    }
    fprintf(output, "\n");
}

void interpret(FILE *output, int instrucao_count) {
    const int stacksize = 500;
    int p, b, t;
    instrucao i;
    int s[stacksize];

    p = 0; b = 1; t = 0;
    memset(s, 0, sizeof(int) * stacksize);

    while (p < instrucao_count) {
        i = code[p];
        print_status(output, p, b, t, s);
        switch (i.f) {
            case lit:
                s[++t] = i.a;
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
                break;
            case lod:
                s[++t] = s[b + i.a];
                break;
            case sto:
                s[b + i.a] = s[t];
                t--;
                break;
            case cal:
                s[t + 1] = b; 
                s[t + 2] = p + 1; 
                s[t + 3] = i.a;
                b = t + 1; 
                p = i.a;
                break;
            case inter:
                t += i.a;
                break;
            case jmp:
                p = i.a;
                break;
            case jpc:
                if (s[t] == 0)
                    p = i.a;
                t--;
                break;
            default:
                printf("Invalid operation code.\n");
                break;
        }
        p++;
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
    instrucao programa[] = {
        {lit, 0, 0, "lit"},
        {lit, 0, 1000, "lit"},
        {sto, 0, 0, "sto"},
        {lit, 0, 1, "lit"},
        {sto, 0, 1, "sto"},
        {lit, 0, 0, "lit"},
        {sto, 0, 2, "sto"},
        {lod, 0, 1, "lod"},
        {lod, 0, 1, "lod"},
        {lod, 0, 1, "lod"},
        {opr, 0, 4, "opr"},
        {opr, 0, 4, "opr"},
        {opr, 0, 4, "opr"},
        {opr, 0, 2, "opr"},
        {lod, 0, 0, "lod"},
        {opr, 0, 2, "opr"},
        {sto, 0, 0, "sto"},
        {lit, 0, 1, "lit"},
        {lod, 0, 1, "lod"},
        {opr, 0, 2, "opr"},
        {sto, 0, 1, "sto"},
        {lit, 0, 1000, "lit"},
        {lod, 0, 1, "lod"},
        {opr, 0, 11, "opr"},
        {jpc, 0, 24, "jpc"},
        {jmp, 0, 8, "jmp"},
        {opr, 0, 0, "opr"},
    };

    int instrucao_count = sizeof(code) / sizeof(instrucao);

    memcpy(code, programa, sizeof(programa));

    FILE *output_file = fopen("resposta.txt", "w");

    if (output_file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    interpret(output_file, instrucao_count); // Passa o número de instrucoes lidas para a função interpret

    fclose(output_file);

    return 0;   
}
