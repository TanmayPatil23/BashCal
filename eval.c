#include<stdio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "stack.h"
#include "num.h"
#include "func.h"
#include "eval.h"
#include "token.h"

int precedence(char op) {
	if(op == '*' || op == '/' || op == '%')
		return 3;
	if(op == '+' || op == '-')
		return 2;
	if(op == '(')
		return 1;
	return 0;
}

int read(char *arr, int len) {
	int i = 0;
	int ch;
	while((ch = getchar()) != '\n' && i < len - 1) {
		arr[i] = ch;
		i++;
	}
	arr[i] = '\0';
	return i;
}
number *solve(char *str) {
	number *x, *y, *z, *w;
	x = (number *)malloc(sizeof(number));
	y = (number *)malloc(sizeof(number));
	z = (number *)malloc(sizeof(number));
	w = (number *)malloc(sizeof(number));
	init(x);
	init(y);
	init(z);
	init(w);
	int reset = 1, c, b;
	char op1, op2;
	token *t;
	t = (token *)malloc(sizeof(token));
	char_stack opstack;
	num_stack nstack;
	num_stack nstack1;
	sinit(&nstack);
	cinit(&opstack);
	sinit(&nstack1);
	int flag = 0, pow = 0;
	int i = 0;
	i = 0;
	while(1) {
		t = getnext(str, &reset);
		if(t->type == OPERAND){
			if(pow == 1) {
				x = pop_num_stack(&nstack);
				if(dec(t->l) != 0)
					return NULL;
				y = power(x, t->l);
				pow = 0;
				push_num_stack(&nstack, y);
			}
			else {
				push_num_stack(&nstack, t->l);
			}
		}
		else if(t->type == OPERATOR) {
			switch(t->op) {
				case '+': case '/': case '*': case '-': case '%':
					push_char_stack(&opstack, t->op);
					break;
				case '(':
					push_char_stack(&opstack, t->op);
					flag++;
					break;
				case '^':
					pow = 1;
					break;
				case ')':						 
					flag--;
					if(flag < 0)
						return NULL;
					while(1) {
						if(!char_stack_empty(&opstack)) {
							op1 = pop_char_stack(&opstack);
							if(op1 == '(') {
								break;
							}						
						}
						else
							break;
						if(!char_stack_empty(&opstack)) 
							op2 = pop_char_stack(&opstack);
						c = precedence(op1);
						b = precedence(op2);
						if(c > b) {
							if(!num_stack_empty(&nstack)) 
								z = pop_num_stack(&nstack);
							else
								return NULL;
							if(!num_stack_empty(&nstack))
								y = pop_num_stack(&nstack);
							else
								return NULL;
							switch(op1) {
								case '+':
									push_num_stack(&nstack, add(y, z));
									break;
								case '-':
									push_num_stack(&nstack, sub(y, z));
									break;
								case '/':
									push_num_stack(&nstack, division(y, z));
									break;
								case '*':
									push_num_stack(&nstack, mul(y, z));
									break;
								case '%':
									push_num_stack(&nstack, mod(y,z));
									break;
							}
							if(op2 != '(') {
								if(!num_stack_empty(&nstack))
									z = pop_num_stack(&nstack);
								else
									return NULL;
								if(!num_stack_empty(&nstack))
									y = pop_num_stack(&nstack);
								else
									return NULL;
								switch(op2) {
									case '+':
										push_num_stack(&nstack, add(y, z));
										break;
									case '-':
										push_num_stack(&nstack, sub(y, z));
										break;
									case '/':
										push_num_stack(&nstack, division(y, z));
										break;
									case '*':
										push_num_stack(&nstack, mul(y, z));
										break;
									case '%':
										push_num_stack(&nstack, mod(y,z));
										break;
								}
							}
						}
						else if(c <= b) {
							if(!num_stack_empty(&nstack))
								z = pop_num_stack(&nstack);
							else
								return NULL;
							if(!num_stack_empty(&nstack))
								y = pop_num_stack(&nstack);
							else
								return NULL;
							if(!num_stack_empty(&nstack))
								x = pop_num_stack(&nstack);
							else
								return NULL;
							switch(op2) {
								case '+':
									x = add(x, y);
									break;
								case '-':
									x = sub(x, y);
									break;
								case '/':
									x = division(x, y);
									break;
								case '*':
									x = mul(x, y);
									break;
								case '%':
									x = mod(x, y);
									break;	
							}
							switch(op1) {
								case '+':
									push_num_stack(&nstack, add(x, z));
									break;
								case '-':
									push_num_stack(&nstack, sub(x, z));
									break;
								case '/':
									push_num_stack(&nstack, division(x, z));
									break;
								case '*':
									push_num_stack(&nstack, mul(x, z));
									break;
								case '%':
									push_num_stack(&nstack, mod(x,z));
									break;
							}
						}
					}
					break;	
				default:
					printf("default");
					return NULL;
					break;
			}
		}			
		else if(t->type == END) {
			while(!num_stack_empty(&nstack)) {
				x = pop_num_stack(&nstack);
				push_num_stack(&nstack1, x);
				
			}
			char op[100];
			i = 0;
			while(!char_stack_empty(&opstack)) {
				op[i] = pop_char_stack(&opstack);
				i++;
			}
			int j = 0;
			while(j < i) {
				push_char_stack(&opstack, op[j]);
				j++;
			}
						
			while(1) {
				if(flag != 0)
					return NULL;
				if(!char_stack_empty(&opstack)) {
					op1 = pop_char_stack(&opstack);
				}
				else {
					break;
				}
				if(!char_stack_empty(&opstack))
					op2 = pop_char_stack(&opstack);
				else {	
					if(!num_stack_empty(&nstack1)) {
						z = pop_num_stack(&nstack1);
					}
					else
						return NULL;
					if(!num_stack_empty(&nstack1)) {
						y = pop_num_stack(&nstack1);
					}
					else
						return NULL;
					switch(op1) {
						case '+':
							push_num_stack(&nstack1, add(z, y));
							break;
						case '-':
							push_num_stack(&nstack1, sub(z, y));
							break;
						case '/':
							push_num_stack(&nstack1, division(z, y));
							break;
						case '*':
							push_num_stack(&nstack1, mul(z, y));
							break;
						case '%':
							push_num_stack(&nstack1, mod(z,y));
							break;
					}
					break;
				}
				c = precedence(op1);
				b = precedence(op2);
				if(c >= b) {
					if(!num_stack_empty(&nstack1)) {
						z = pop_num_stack(&nstack1);
					}
					else
						return NULL;
					if(!num_stack_empty(&nstack1)) {
						y = pop_num_stack(&nstack1);
					}
					else
						return NULL;
					switch(op1) {
						case '+':
							push_num_stack(&nstack1, add(z, y));
							break;
						case '-':
							push_num_stack(&nstack1, sub(z, y));
							break;
						case '/':
							push_num_stack(&nstack1, division(z, y));
							break;
						case '*':
							push_num_stack(&nstack1, mul(z, y));
							break;
						case '%':
							push_num_stack(&nstack1, mod(z, y));
							break;
					}
					push_char_stack(&opstack, op2);
				}
				else if(c < b) {
					if(!num_stack_empty(&nstack1)) {
						z = pop_num_stack(&nstack1);
					}
					else
						return NULL;
					if(!num_stack_empty(&nstack1)) {
						y = pop_num_stack(&nstack1);
					}
					else
						return NULL;
					if(!num_stack_empty(&nstack1))
						x = pop_num_stack(&nstack1);
					else
						return NULL;
					switch(op2) {
						case '+':
							push_num_stack(&nstack1, add(y, x));
							break;
						case '-':
							push_num_stack(&nstack1, sub(y, x));
							break;
						case '/':
							push_num_stack(&nstack1, division(y, x));
							break;
						case '*':
							push_num_stack(&nstack1, mul(y, x));
							break;
						case '%':
							push_num_stack(&nstack1, mod(y, x));
							break;		
					}
					push_num_stack(&nstack1, z);
					push_char_stack(&opstack, op1);
				}		
			}
			if(!num_stack_empty(&nstack1) && char_stack_empty(&opstack)) {	
				y = (pop_num_stack(&nstack1));
				if(num_stack_empty(&nstack1) && char_stack_empty(&opstack)) {
					x = NULL;
					z = NULL;
					w = NULL;
					free(x);
					free(z);
					free(w);
					return (y);
					
				}
				else if(pow == 1) {
					if(!num_stack_empty(&nstack1))
						x = pop_num_stack(&nstack1);
					else
						return NULL;
					if(x->dec != 0)
						return NULL;
					z = power(y, x);
					pow = 0;
					x = NULL;
					y = NULL;
					w = NULL;
					free(x);
					free(y);
					free(w);
					return z;
				}
				else {
					x = NULL;
					y = NULL;
					w = NULL;
					z = NULL;
					free(x);
					free(y);
					free(w);
					free(z);
					return NULL;	
				}	
			}
			else {
				
				x = NULL;
				y = NULL;
				w = NULL;
				z = NULL;
				free(x);
				free(y);
				free(w);
				free(z);
				return NULL;
			}
			
		}
		else if(t->type == ERROR) {
			x = NULL;
			y = NULL;
			z = NULL;
			w = NULL;
			free(x);
			free(y);
			free(z);
			free(w);
			return NULL;
		}
	}
	if(!num_stack_empty(&nstack1))
		return (pop_num_stack(&nstack1));
	return NULL;						
}