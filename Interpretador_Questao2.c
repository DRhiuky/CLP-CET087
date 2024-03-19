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
    fprintf(output, "(%d %d %d)|", p, b, t);
    for (int j = 1; j <= t; j++) {
        fprintf(output, " s[%02d]", j);
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

int main() {
    instrucao programa[] = {
        {lit, 0, 0, "lit"},
        {lit, 0, 100, "lit"},
        {sto, 0, 0, "sto"},
        {lit, 0, 1, "lit"},
        {sto, 0, 1, "sto"},
        {lit, 0, 0, "lit"},
        {sto, 0, 2, "sto"},
        {lod, 0, 1, "lod"},
        {lod, 0, 1, "lod"},
        {opr, 0, 4, "opr"},
        {lod, 0, 0, "lod"},
        {opr, 0, 2, "opr"},
        {sto, 0, 0, "sto"},
        {lit, 0, 1, "lit"},
        {lod, 0, 1, "lod"},
        {opr, 0, 2, "opr"},
        {sto, 0, 1, "sto"},
        {lit, 0, 100, "lit"},
        {lod, 0, 1, "lod"},
        {opr, 0, 11, "opr"},
        {jpc, 0, 24, "jpc"},
        {jmp, 0, 8, "jmp"},
        {opr, 0, 0, "opr"},
    };

    int instrucao_count = sizeof(programa) / sizeof(instrucao);

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
