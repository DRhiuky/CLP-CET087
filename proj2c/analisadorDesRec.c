#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Prototipos das funcoes
void expr(char **);
void term(char **);
void factor(char **);

// Funcao para relatar um erro
void error(char *message) {
    printf("Erro: %s\n", message);
    exit(EXIT_FAILURE);
}

// Funcao para verificar se um caractere é um operador
int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Funcao para verificar se um caractere é um espaco em branco
int is_space(char c) {
    return (c == ' ' || c == '\t' || c == '\n');
}

// Funcao para consumir espacos em branco
void consume_spaces(char **str) {
    while (is_space(**str))
        (*str)++;
}

// Funcao para analisar a expressao
void expr(char **str) {
    term(str);
    while (**str == '+' || **str == '-') {
        printf("<expr> -> <term>\n");
        (*str)++;
        term(str);
    }
}

// Funcao para analisar o termo
void term(char **str) {
    factor(str);
    while (**str == '*' || **str == '/') {
        printf("<term> -> <factor>\n");
        (*str)++;
        factor(str);
    }
}

// Funcao para analisar o fator
void factor(char **str) {
    if (isdigit(**str)) {
        printf("<factor> -> int_constant\n");
        while (isdigit(**str))
            (*str)++;
    } else if (**str == '(') {
        printf("<factor> -> ( <expr> )\n");
        (*str)++;
        expr(str);
        if (**str != ')')
            error("Falta ')' apos a expressao dentro de parenteses");
        (*str)++;
    } else {
        printf("<factor> -> id\n");
    }
}

int main() {
    char input[100];
    printf("Digite a expressao: ");
    fgets(input, sizeof(input), stdin);

    char *ptr = input;
    printf("Lista de producoes da gramatica:\n");
    printf("---------------------------------\n");
    expr(&ptr);
    consume_spaces(&ptr);
    if (*ptr != '\0' && *ptr != '\n')
        error("Caracteres extras apos a expressao");

    printf("\nPrograma aceito.\n");

    return 0;
}

/*
--------------------------------------------ANALISADOR DESCENDENTE RECURSIVO--------------------------------------------
EXEMPLOS DE ENTRADA E SAIDA:


--> xyz
Lista de producoes da gramatica:
---------------------------------
<factor> -> id
Erro: Caracteres extras apos a expressao


--> 1357
Lista de producoes da gramatica:
---------------------------------
<factor> -> int_constant
Programa aceito.


--> 1+(3*5)
Lista de producoes da gramatica:
---------------------------------
<factor> -> int_constant
<expr> -> <term>
<factor> -> ( <expr> )
<factor> -> int_constant
<term> -> <factor>
<factor> -> int_constant
Programa aceito.


--> (5*7)+(9/11)
Lista de producoes da gramatica:
---------------------------------
<factor> -> ( <expr> )
<factor> -> int_constant
<term> -> <factor>
<factor> -> int_constant
<expr> -> <term>
<factor> -> ( <expr> )
<factor> -> int_constant
<term> -> <factor>
<factor> -> int_constant
Programa aceito.


--> (8642)
Lista de producoes da gramatica:
---------------------------------
<factor> -> ( <expr> )
<factor> -> int_constant
Programa aceito.
*/