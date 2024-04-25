#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAX_arvore_SIZE 100

// Definição da estrutura de pilha
typedef struct {
    char stack[MAX_STACK_SIZE];
    int top;
} Stack;

// Função para inicializar a pilha
void initStack(Stack *s) {
    s->top = -1;
}

// Função para adicionar um elemento à pilha (push)
void push(Stack *s, char c) {
    if (s->top < MAX_STACK_SIZE - 1) {
        s->top++;
        s->stack[s->top] = c;
    } else {
        printf("Erro: Pilha cheia\n");
        exit(1);
    }
}

// Função para remover um elemento da pilha (pop)
char pop(Stack *s) {
    if (s->top >= 0) {
        return s->stack[s->top--];
    } else {
        printf("Erro: Pilha vazia\n");
        exit(1);
    }
}

// Função principal para simular o autômato pilha e imprimir a árvore em um vetor
int automatoPilha(FILE *fp, char *arvore, int *indiceArvore) {
    Stack stack;
    char token;
    int nodeIndex = 0;

    initStack(&stack);
    push(&stack, 'S'); // Empilhar o símbolo inicial 'S'
    arvore[nodeIndex++] = 'S'; // Raiz da árvore

    while (fscanf(fp, " %c", &token) != EOF) {
        switch (stack.stack[stack.top]) {
            case 'S':
                if (token == 'a') {
                    pop(&stack);
                    arvore[nodeIndex++] = 'a'; // Nodo 'a'
                    push(&stack, 'b');
                    push(&stack, 'S');
                    push(&stack, 'a');
                } else if (token == 'b') {
                    pop(&stack);
                    arvore[nodeIndex++] = 'b'; // Nodo 'b'
                    push(&stack, 'b');
                    push(&stack, 'S');
                    push(&stack, 'a');
                } else if (token == 'c') {
                    pop(&stack);
                    arvore[nodeIndex++] = 'c'; // Nodo 'c'
                    push(&stack, 'c');
                } else {
                    printf("Erro: Token inesperado\n");
                    exit(1);
                }
                break;
            case 'a':
            case 'b':
            case 'c':
                if (token == stack.stack[stack.top]) {
                    pop(&stack);
                } else {
                    printf("Erro: Token inesperado\n");
                    exit(1);
                }
                break;
            default:
                printf("Erro: Símbolo inesperado na pilha\n");
                exit(1);
        }
    }

    *indiceArvore = nodeIndex;

    return 0;
}

// Função para imprimir a árvore em um vetor
void printarvore(char *arvore, int indiceArvore) {
    printf("Árvore de análise sintática:\n");
    for (int i = 0; i < indiceArvore; i++) {
        printf("%c ", arvore[i]);
    }
    printf("\n");
}

int main() {
    FILE *fp;
    fp = fopen("entrada.txt", "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    char arvore[MAX_arvore_SIZE];
    int indiceArvore;

    automatoPilha(fp, arvore, &indiceArvore);
    printarvore(arvore, indiceArvore);

    fclose(fp);
    return 0;
}
