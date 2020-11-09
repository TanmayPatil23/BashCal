#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "num.h"
#include "stack.h"


void init(number *n){
	n->head = n->tail = NULL;
	n->len = 0;
	n->dec = 0;
	n->sign = 1;
}
void insert(number *n, int pos, int digit){
	node *temp, *p;
	int i;
	/* handle errors on position */	
	if(pos < 0 || pos > n->len)
		return;	
	/* create a new node */
	temp = (node *)malloc(sizeof(node));	
	temp->num = digit;
	/* handle first node case separately */
	if(n->head == NULL) {
		temp->next = NULL; 
		temp->prev = NULL;
		n->head = n->tail = temp;
		n->len++;
		return;		
	}
	/* link the new node on the number at appropriate position*/
	p = n->head;
	for(i = 0; i < pos - 1; i++)
		p = p->next;
	if(pos == 0) {
		temp->next = n->head;
		n->head->prev = temp;
		n->head = temp;
		n->head->prev = NULL;
		n->len++;
		return;
	}
	if(pos != n->len) {
		temp->next = p->next;
		temp->prev = p;
		p->next->prev = temp;
		p->next = temp;
		n->len++;
		return;
	}
	if(pos == n->len) {
		p->next = temp;
		n->tail = temp;
		temp->prev = p;	
		temp->next = NULL;
		n->len++;
		return;
	}
}
int del(number *n, int pos){
	int i;
	int num;
	node *p, *temp;
	/* handle errors on position */	
	if(pos < 0 || pos >= n->len)
		return 0;	
	
	p = n->head;
	for(i = 0; i < pos - 1; i++)
		p = p->next;
	if(n->head == NULL) {
		return 0;
	}
	if(n->len == 1) {	
		num = p->num;
		n->head = n->tail = p = NULL;
		n->len--;
		return num;
	}
	if(pos == 0) {	
		num = p->num;
		p->next->prev = NULL;
		n->head = p->next;
		free(p);
		n->len--;
		return num;
	}
	if(pos == n->len - 1) {	
		num = p->next->num;
		temp = p->next;
		p->next = NULL;
		n->tail = p;
		free(temp);
		n->len--;
		return num;
	}
	
	temp = p->next;
	p->next = p->next->next;
	temp->next->prev = p;	
	num = temp->num;
	free(temp);
	n->len--;
	return num;
}
void traverse(number *n){
	node *p = n->head;
	int i = 0;
	int flag = 0, print = 0;
	int flag1 = 0;
	if(!p) {
		return;
	}
	do {
		if(n->sign == -1) {
			printf("-");
			n->sign = 1;
			flag = 1;
		}
		if(i == n->len - n->dec) {
			if(print != 1) {
				printf("0.");
				print = 1;
			}
		}
		i++;
		if(p->num != 0 || i > n->len - n->dec - 2) {
			flag1 = 1;
		}
		if(flag1 == 1)
			printf("%d", p->num);
		if( i == n->len - n->dec) {
			if(print != 1) {
				if(n->dec != 0)
					printf(".");
				print = 1;
			}
		}
		p = p->next;
	} while(p != NULL) ;
	if(flag == 1) {
		n->sign = -1;
		flag = 0;
	}
}
void append(number *n, int digit) {
	insert(n, n->len, digit);
}
int length(number *n) {
	return n->len;
}
int dec(number *n) {
	return n->dec;
}
int get(number *n, int pos) {
	node *p;
	if(pos < 0 || pos > n->len)
		return 0;
	p = n->head;
	int i;
	for(i = 0; i < pos; i++)
		p = p->next;
	return p->num;
}