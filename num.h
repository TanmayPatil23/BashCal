#ifndef __NUM__
#define __NUM__
typedef struct node {
	int num;
	int flag;
	struct node *next, *prev;
}node;

typedef struct list {
	node *head, *tail;
	int len, dec, sign;
} number;
void init(number *n);
void insert(number *n, int pos, int digit);
int del(number *n, int pos);
void traverse(number *n);
void append(number *n, int digit);
int length(number *n);
int dec(number *n);
int get(number *n, int pos);
#endif
