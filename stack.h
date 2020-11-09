#ifndef __STACK__
#define __STACK__
#include "num.h"
#define MAX 100
typedef struct stack{
	int i;
	number *l[MAX];
} num_stack;

void sinit(num_stack *s);
void push_num_stack(num_stack *s, number *n);
number *pop_num_stack(num_stack *s);
int num_stack_empty(num_stack *s);
int full(num_stack *s);


typedef struct cstack{
	char a[MAX];
	int i;
} char_stack;

void cinit(char_stack *s);
void push_char_stack(char_stack *s, char num);
char pop_char_stack(char_stack *s);
int char_stack_empty(char_stack *s);
int cfull(char_stack *s);
#endif