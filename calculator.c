#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_EXPR_LEN 100

// Estrutura que representa um token (número ou operador)
typedef struct{
    char type;      // 'n' para número, 'o' para operador
    double value;   // Valor do número (se type == 'n')
    char op;        // Operador (se type == 'o')
} Token;

// Estrutura de pilha para armazenar tokens
typedef struct{
    Token tokens[MAX_EXPR_LEN];
    int top;
} Stack;

// Função para empilhar um token
void push(Stack* stack, Token token){
    stack->tokens[++(stack->top)] = token;
}

// Função para desempilhar um token
Token pop(Stack* stack){
    return stack->tokens[(stack->top)--];
}

// Função para visualizar o token no topo da pilha sem removê-lo
Token peek(Stack* stack) {
    return stack->tokens[stack->top];
}

// Função para retornar a precedência de um operador
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
    }
    return 0;
}

// Função para converter expressão infixa para pós-fixa (RPN)
void infixToPostfix(const char* expr, Token* output, int* outputLen) {
    Stack opStack = {.top = -1};
    int i = 0;
    int k = 0;

    while (expr[i] != '\0') {

        // Se o caractere é um dígito ou ponto, trata como número
        if (isdigit(expr[i]) || expr[i] == '.' || expr[i] == ',') {
            char number[20];
            int j = 0;
            // Continua capturando o número
            while (isdigit(expr[i]) || expr[i] == '.' || expr[i] == ',') {
                number[j++] = expr[i++];
            }
            number[j] = '\0';

            for (int m = 0; number[m] != '\0'; m++) {
                if (number[m] == ',') {
                    number[m] = '.';
                }
            }
            Token num = {.type = 'n', .value = atof(number)};
            output[k++] = num;
        // Se o caractere é um operador
        } else if (strchr("+-*/^(", expr[i])) {
            // Desempilha operadores de maior ou igual precedência
            while (opStack.top != -1 && precedence(peek(&opStack).op) >= precedence(expr[i]) && expr[i] != '(') {
                output[k++] = pop(&opStack);
            }
            // Empilha o operador atual
            Token op = {.type = 'o', .op = expr[i]};
            push(&opStack, op);
            i++;
        
        //Se for um parêntese de fechamento, desempilha até chegar em um parêntese de abertura
        } else if (expr[i] == ')'){
            while(peek(&opStack).op != '('){
                output[k++] = pop(&opStack);
            }
            pop(&opStack);
            i++;
        } else {
            i++;
        }
    }

    // Desempilha todos os operadores restantes na pilha
    while (opStack.top != -1) {
        output[k++] = pop(&opStack);
    }
    *outputLen = k;
}

//Função para calcular a expressão pós-fixa
double calcPostfix(Token *tokens, int length){
    Stack numStack = {.top = -1};
    for(int i = 0; i < length; i++){
        //Se o token é um número, empilha
        if(tokens[i].type == 'n'){
            push(&numStack, tokens[i]);
        //Se é operador, desempilha dois números e aplica o operador
        } else {
            double b = pop(&numStack).value;
            double a = pop(&numStack).value;
            double result;
            switch (tokens[i].op)
            {
            case '+':
                result = a + b;
                break;
            case '-':
                result = a - b;
                break;
            case '*':
                result = a * b;
                break;
            case '/':
                result = a / b;
                break;
            case '^':
                result = pow(a,b);
                break;
            } 
            //Empilha o resultado da operação
            Token finalResult = {.type = 'n', .value = result};
            push(&numStack, finalResult);  
        }
    }
    //O resultado final é o único valor restante na pilha
    return pop(&numStack).value;
}

int main(){
    printf(">> CALCULADORA <<\n\n");
    char expression[MAX_EXPR_LEN];
    printf(" + -> soma\n");
    printf(" - -> subtracao\n");
    printf(" * -> multiplicacao\n");
    printf(" / -> divisao\n");
    printf(" ^ -> potenciacao\n\n");

    printf("Digite a expressao (Ex: 2 + 2): ");
    scanf("%[^\n]s", expression);

    Token postfix[MAX_EXPR_LEN];
    int postfixLen;

    infixToPostfix(expression, postfix, &postfixLen);
    double result = calcPostfix(postfix, postfixLen);

    printf("\n%.2f\n", result);
    return 0;
}
