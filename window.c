/**@file window.c
 *
 * \brief Executa o comando window
 *
 * Este módulo contem o comando window, que irá
 * devolver um novo input com o resultado de executar
 * uma operação (avg,max,min,sum) sobre os inputs
 * anteriores.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stringProcessing.h"

/*Operação de média
 */
#define AVG 0
/*Operação de máximo
 */
#define MAX 1
/*Operação de mínimo
 */
#define MIN 2
/*Operação de soma
 */
#define SUM 3

/**
 * @struct Estrutura com os valores antigos
 */
typedef struct values_{
	int *values; ///< Array com os valores
	int used;	 ///< Número de elementos usados
	int size;	 ///< Tamanho do array
}*Values;

/**
 * \brief Inicializa a estrutura de valores
 * @return Estrutura inicializada
 */
Values initValues(){
	Values values = malloc (sizeof(struct values_));
	values->size = 10;
	values->used = 0;
	values->values = (int *) malloc (sizeof(int) * values->size);
	return values;
}

/**
 * \brief Realoca espaço para o array de valores
 * @param values Estrutura de valores
 */
void reallocValues(Values values){
	values->values = realloc(values->values, sizeof(int) * values->size * 2);
	values->size *= 2;
	
}

/**
 * \brief Devolve a média dos n ultimos valores
 * @param  values Estrutura de valores
 * @param  n      Número de elementos a contabilizar
 * @return        Média
 */
int avg(Values values, int n){
	int i, total = 0;
	for (i=0; i<n && i<values->used; i++)
		total += values->values[values->used - 1 - i];

	if (i > 0) return total/i;
	else return 0;
}

/**
 * \brief Devolve o máximo dos n ultimos valores
 * @param  values Estrutura de valores
 * @param  n      Número de elementos a contabilizar
 * @return        Máximo
 */
int max(Values values, int n){
	int i, max = values->values[values->used -1];
	for (i=0; i<n && i<values->used; i++)
		if (values->values[values->used - 1 - i] > max)
			max = values->values[values->used - 1 - i];

	if (i > 0) return max;
	else return 0;
}

/**
 * \brief Devolve o mínimo dos n ultimos valores
 * @param  values Estrutura de valores
 * @param  n      Número de elementos a contabilizar
 * @return        Mínimo
 */
int min(Values values, int n){
	int i, min = values->values[values->used -1];
	for (i=0; i<n && i<values->used; i++)
		if (values->values[values->used - 1 - i] < min)
			min = values->values[values->used - 1 - i];

	if (i > 0) return min;
	else return 0;
}

/**
 * \brief Devolve a soma dos n ultimos valores
 * @param  values Estrutura de valores
 * @param  n      Número de elementos a contabilizar
 * @return        Soma
 */
int sum(Values values, int n){
	int i, sum = 0;
	for (i=0; i<n && i<values->used; i++)
		sum += values->values[values->used - 1 - i];

	return sum;
}

/**
 * \brief Devolve uma nova string com o resultado de efetuar uma operação nos n ultimos números da coluna i
 * @param  input  Input
 * @param  values Estrutura de valores
 * @param  i      Coluna da qual queremos aplicar a operação
 * @param  op     Operação a realizar
 * @param  n      Número de elementos a contabilizar
 * @return String com o input + resultado
 */
char* window(char* input, Values values, int i, int op, int n){
	char **c;
	char inputCopy[strlen(input) +1], *new;
	int x;
	
	strcpy(inputCopy, input);
	c = divideString(inputCopy, ":");


	if 		(op == AVG) x = avg(values, n);
	else if (op == MAX) x = max(values, n);
	else if (op == MIN) x = min(values, n);
	else if (op == SUM) x = sum(values, n);

	char *x_string;
	x_string = malloc (sizeof(char) * numberOfDigits(x));
	sprintf(x_string, "%d\n", x);

	new = malloc (sizeof(char) * (strlen(input) + strlen(x_string) +1));
	strcpy(new, input);
	new[strlen(input)-1] = ':';
	new[strlen(input)] = '\0';
	strcat(new, x_string);

	values->values[values->used++] = atoi(c[i]);

	return new;
}

/**
 * \brief Função main de window
 * @param  argc Número de argumentos
 * @param  argv Array de argumentos
 * @return ---
 */
int main(int argc, char *argv[]){
	Values values = initValues();
	int charsRead;
	char** commands = divideString(argv[1], " ");
	char buffer[4096];
	char* out;
	int i, n, op;

	i = atoi(commands[0]) - 1;
	n = atoi(commands[2]);

	if (!strcmp(commands[1], "avg")) op = 0;
	if (!strcmp(commands[1], "max")) op = 1;
	if (!strcmp(commands[1], "min")) op = 2;
	if (!strcmp(commands[1], "sum")) op = 3;

	while((charsRead = readline(0, buffer, 4096)) > 0){
		if (charsRead > 1){
			char inputCopy[charsRead];
			out = window(buffer, values, i, op, n);
			write(1, out, strlen(out));
			memset(buffer, 0, charsRead);

			if (values->used == values->size)
				reallocValues(values);
		}
	}
	return 0;
}