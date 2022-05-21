#include<stdio.h>
#include<malloc.h>
#include<memory.h>
#include<math.h>
#include<string.h>
#include "dispersed.h"

void delect_space(char* expression,int *len) {
	if (char* temp = (char*)malloc(*len)) {
		memcpy(temp, expression, *len);
		for (int p = 0; p < *len; p++)
		{
			if (*(expression + p) == SPACE) {
				memcpy(temp, expression + p + 1, *len - p - 1);
				memset(expression + p, 0, *len - p);
				memcpy(expression + p, temp, *len - p -1);
				memset(temp, 0, *len);
				*len -=1;
				p = -1;
			}
		}
		free(temp);
	}
}
int not_formatted(char* context, int len) {
	int brackets = 0;
	for (int i = 0; i < len; i++) {
		if (*(context + i) == '(')brackets++;
		else if (*(context + i) == ')')brackets--;
	}
	return brackets ;
}
int is_bracket(char* context, int len) {
	for (int i = 0; i < len; i++) {
		if (*(context + i) == '(')return 1;
	}
	return 0;
}
char _and(char p, char q)
{
	p = p == TRUE ? 1 : 0;
	q = q == TRUE ? 1 : 0;
	int m = p && q;
	char a;
	if (m == 0) a = FALSE;
	if (m == 1) a = TRUE;
	return a;
}
char _or(char p, char q)
{
	p = p == TRUE ? 1 : 0;
	q = q == TRUE ? 1 : 0;
	int m = p || q;
	char a;
	if (m == 0) a = FALSE;
	if (m == 1) a = TRUE;
	return a;
}
char negative(char p)
{
	p = p == TRUE ? 1 : 0;
	int m = !p;
	char a;

	if (m == 0) a = FALSE;
	if (m == 1) a = TRUE;
	return a;
}
char condition(char p, char q)
{
	p = p == TRUE ? 1 : 0;
	q = q == TRUE ? 1 : 0;
	int m = !p || q;
	char a;
	if (m == 0) a = FALSE;
	if (m == 1) a = TRUE;
	return a;
}
char double_condition(char p, char q) {
	p = p == TRUE ? 1 : 0;
	q = q == TRUE ? 1 : 0;
	int m = (!p || q) && (!q || p);
	char a;
	if (m == 0) a = FALSE;
	if (m == 1) a = TRUE;
	return a;
}
char _xor(char p, char q) {
	p = p == TRUE ? 1 : 0;
	q = q == TRUE ? 1 : 0;
	int m = !(q || p);
	char a;
	if (m == 0) a = FALSE;
	if (m == 1) a = TRUE;
	return a;
}
void operation(int len, char input[]) {
	char small[3];
	memset(small, SPACE, sizeof(small));
	int i;
	for (i = 0; i < len; i++) {
		if (input[i] < 'a' || input[i]>'z') {
			small[0] = input[i - 1];
			small[1] = input[i];
			small[2] = input[i + 1];
			switch (small[1]) {
			case AND:input[i + 1] = _and(small[0], small[2]); break;
			case OR:input[i + 1] = _or(small[0], small[2]); break;
			case NEGATIVE:input[i + 1] = negative(small[2]); break;
			case CONDITION:input[i + 1] = condition(small[0], small[2]); break;
			case DOUBLE_CONDITION:input[i + 1] = double_condition(small[0], small[2]); break;
			case XOR:input[i + 1] = _xor(small[0], small[2]); break;
			}
			input[i] = SPACE; if (!(i > 1))input[i - 1] = SPACE;
			break;
		}
	}
	delect_space(input, &len);
}

int  recursive_computation(char* exp,int len) {
	int brackets = 0, l_bracket = -1, r_bracket = 0;
	delect_space(exp, &len);
	if (is_bracket(exp, len)) {
		for (int num = 0; !r_bracket; num++) {
			if (*(exp + num) == '(') {
				brackets++;
				if(l_bracket==-1) l_bracket = num;
			}
			if (*(exp + num) == ')') {
				if (!(--brackets)) {
					r_bracket = num;
					*(exp + l_bracket) = SPACE;
					*(exp + r_bracket) = SPACE;
					break;
				}
			}
		}
		if (char* _fork = (char*)malloc(len)) {
			memset(_fork, 0, len);
			memcpy(_fork, exp + l_bracket + 1, r_bracket - l_bracket - 1);
			int _len = recursive_computation(_fork, r_bracket - l_bracket - 1);
			memset(exp + l_bracket + 1,SPACE ,r_bracket - l_bracket - 1);
			memcpy(exp + l_bracket ,_fork ,_len);
			free(_fork);
			//len -= r_bracket - l_bracket + 1 - _len;
			return len;
		}
	}
	else {
		operation(len, exp);
		return 1;
	}
	return 0;
}
static char op[] = { NEGATIVE,AND,OR,CONDITION,DOUBLE_CONDITION,XOR,'(',')'};
void value_list(char* exp, int len) {
	char propositional_formula[8];
	memset(propositional_formula, 0, 8);
	delect_space(exp, &len);
	int o_size = 0;
	for (int i = 0; i < len; i++) {
		for (int p = 0; p < sizeof(op); p++) {
			if (exp[i] == op[p]) {
				continue;
			}
		}
		if (o_size<8) {
			for (int p = 0; p < o_size; p++) {
				if (exp[i] == propositional_formula[p]) {
					continue;
				}
			}
			propositional_formula[o_size++] = exp[i];
		}
	}
	int round = 0;
	for (; round < pow(2, o_size); round++) {
		for (int i = 0; i < o_size; i++) {
			int x = 1;
			x << i;
			if (x & round) {
				for (int l = 0; l < len; l++)if (exp[l] == propositional_formula[i])exp[l] = TRUE;
			}
			else {
				for (int l = 0; l < len; l++)if (exp[l] == propositional_formula[i])exp[l] = FALSE;
			}
		}
		while (len != 1)
		{
			recursive_computation(exp, len);
			len = strlen(exp);
		}
		printf("%s\n", exp);
	}
}
void calculate(char input[], int len) {
	while (len != 1)
	{
		recursive_computation(input, len);
		len = strlen(input);
	}
}

