#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define amax 2047       // máximo endereço
#define levmax 3        // máxima profundidade de aninhamento de blocos
#define cxmax 200       // tamanho do array de código

typedef enum {
    lit, opr, lod, sto, cal, inte, jmp, jpc
} fct;

typedef struct {
    fct function;
    int arg1;
    int arg2;
} instruction;

instruction code[cxmax]; // array de instruções

void interpret() {
    const int stacksize = 500;
    int p, b, t; // registradores de programa, base e topo da pilha
    int s[stacksize]; // datastore

    int base(int l) {
        int b1 = b; // encontrar a base l níveis abaixo
        while (l > 0) {
            b1 = s[b1];
            l--;
        }
        return b1;
    }

    printf("start pl/0\n");
    t = 0; b = 1; p = 0;
    s[1] = 0; s[2] = 0; s[3] = 0;
    do {
        instruction instr = code[p];
        p++;
        switch (instr.function) {
            case lit:
                t++;
                s[t] = instr.arg1;
                break;
            case opr:
                switch (instr.arg1) { // operador
                    case 0: // retornar
                        t = b - 1;
                        p = s[t + 3];
                        b = s[t + 2];
                        break;
                    case 1:
                        s[t] = -s[t];
                        break;
                    case 2:
                        t--;
                        s[t] += s[t + 1];
                        break;
                    case 3:
                        t--;
                        s[t] -= s[t + 1];
                        break;
                    case 4:
                        t--;
                        s[t] *= s[t + 1];
                        break;
                    case 5:
                        t--;
                        s[t] /= s[t + 1];
                        break;
                    case 6:
                        s[t] = s[t] % 2;
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
                t++;
                s[t] = s[base(instr.arg1) + instr.arg2];
                break;
            case sto:
                s[base(instr.arg1) + instr.arg2] = s[t];
                printf("%d\n", s[t]);
                t--;
                break;
            case cal: // gerar novo marcador de bloco
                s[t + 1] = base(instr.arg1);
                s[t + 2] = b;
                s[t + 3] = p;
                b = t + 1;
                p = instr.arg2;
                break;
            case inte:
                t += instr.arg1;
                break;
            case jmp:
                p = instr.arg1;
                break;
            case jpc:
                if (s[t] == 0)
                    p = instr.arg1;
                t--;
                break;
        }
    } while (p != 0);
    printf("end pl/0\n");
}

int main() {
    printf("Enter P-code instructions (format: 'inst arg1 arg2'):\n");
    
    // Reading P-code instructions
    int index = 0;
    char inst[4];
    int arg1, arg2;
    while (scanf("%s %d %d", inst, &arg1, &arg2) == 3 && strcmp(inst, "0")) {
        if (strcmp(inst, "lit") == 0) {
            code[index].function = lit;
            code[index].arg1 = arg1;
            code[index].arg2 = arg2;
        } else if (strcmp(inst, "opr") == 0) {
            code[index].function = opr;
            code[index].arg1 = arg1;
            code[index].arg2 = 0;
        } else if (strcmp(inst, "lod") == 0) {
            code[index].function = lod;
            code[index].arg1 = arg1;
            code[index].arg2 = arg2;
        } else if (strcmp(inst, "sto") == 0) {
            code[index].function = sto;
            code[index].arg1 = arg1;
            code[index].arg2 = arg2;
        } else if (strcmp(inst, "cal") == 0) {
            code[index].function = cal;
            code[index].arg1 = arg1;
            code[index].arg2 = arg2;
        } else if (strcmp(inst, "inte") == 0) {
            code[index].function = inte;
            code[index].arg1 = arg1;
            code[index].arg2 = 0;
        } else if (strcmp(inst, "jmp") == 0) {
            code[index].function = jmp;
            code[index].arg1 = arg1;
            code[index].arg2 = 0;
        } else if (strcmp(inst, "jpc") == 0) {
            code[index].function = jpc;
            code[index].arg1 = arg1;
            code[index].arg2 = 0;
        }
        index++;
    }

    interpret();
    return 0;
}
