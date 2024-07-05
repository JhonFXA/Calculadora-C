# Calculadora
Este projeto é uma implementação de uma calculadora em C que converte expressões infixas (como 2 + 2) em expressões pós-fixas 
(RPN, Notação Polonesa Reversa) e, em seguida, calcula o valor da expressão pós-fixa. Baseado no algoritmo de Shunting-Yard.

O algoritmo utiliza uma pilha para guardar os operadores e os parênteses à medida que formos lendo cada um deles. 
Com isso, vamos lendo a expressão um caractere por vez, tomando medidas diferentes dependendo de qual caractere estamos lendo no momento:

- Se o caractere é um operando, escrever tal caractere direto na resposta

- Se o caractere é um parênteses aberto, colocar um parênteses aberto na pilha

- Se o caractere é um parênteses fechado, ir tirando operadores da pilha, escrevendo-os na resposta, até encontrarmos um parênteses aberto na pilha, caso em que vamos retirá-lo da pilha, mas não vamos escrevê-lo na resposta

- Se o caractere é um operador, ir tirando operadores da pilha, escrevendo-os na resposta, até uma dessas três possibilidades acontecer.
  1. A pilha estar vazia
  2. Encontrarmos um parênteses aberto
  3. Encontrarmos um operador com precedência menor do que a do operador que lemos naquele momento

 Quando algo acima acontecer, coloque o operador na pilha e passe para o próximo caractere.



## Funcionalidades

- **Operações Suportadas**:
  - Adição (`+`)
  - Subtração (`-`)
  - Multiplicação (`*`)
  - Divisão (`/`)
  - Potenciação (`^`)
  
## Como Usar
1. **Abra o terminal**

2. **Clone o repositório**:
   ```sh
   git clone https://github.com/JhonFXA/Calculadora-C/
   cd Calculadora-C

3. **Compile o código**
   ```sh
   gcc -o calculadora calculator.c -lm
4. **Execute**
   ```
   ./calculadora
