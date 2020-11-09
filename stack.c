#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "stack.h"
#include "num.h"

/* For Numstack */
void sinit(num_stack *s) {
	s->i = 0;
	return;
}
void push_num_stack(num_stack *s, number *n) {
	s->l[s->i]= n;
	(s->i)++;
	return;
}
number *pop_num_stack(num_stack *s) {
	number *t = (number *)malloc(sizeof(number)); 
	t = s->l[s->i - 1];
	(s->i)--;
	return t;
}
int num_stack_empty(num_stack *s) {
	return s->i == 0;
}
int full(num_stack *s) {
	return s->i == MAX;
}

/* For CharStack */
void cinit(char_stack *s) {
	s->i = 0;
	return;
}

void push_char_stack(char_stack *s, char op) {
	s->a[s->i]= op;
	(s->i)++;
	return;
}
char pop_char_stack(char_stack *s) {
	char t = s->a[s->i - 1];
	(s->i)--;
	return t;
}
int char_stack_empty(char_stack *s) {
	return s->i == 0;
}
int cfull(char_stack *s) {
	return s->i == MAX;
}