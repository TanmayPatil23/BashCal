#include "num.h"
#include "token.h"
#include<stdlib.h>
token *getnext(char *arr, int *reset) {
	static int current_state;
	int next_state;
	static int i;
	static number *n;
	static int dec = 0;
	static int flag = 0;
	static int m = 0, num = 0, sign = 1;
	n = (number *)malloc(sizeof(number));
	init(n);
	if(m == 1) {
		append(n, num);
		m = 0;
	}	
	if(*reset == 1) {
		i = 0;
		current_state = SPC;
		*reset = 0;
	}
	token *t = (token *)malloc(sizeof(token));
	while(1) {
		switch(arr[i]) {
			case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7':
			case '8': case '9': case '.':
				next_state = DIG;
				break;
			case '+': case '-': case '*': case '/':
			case '%': case '(': case ')': case '^':
				next_state = OPR;
				break;
			case '\0':
				next_state = STOP;
				break;
			case ' ':
				next_state = SPC;
				break;
			default:
				next_state = ERR;
				break;
		}
		switch(current_state) {
			case SPC:
				if(next_state == DIG) {
					if(arr[i] == '.') {
						flag = 1;
					}
					else {
						append(n,(arr[i] - '0'));
						if(flag == 1)
							dec++;
					}
				}			
				break;
			case DIG:
				if(next_state == DIG) {
					if(arr[i] == '.') {
						flag = 1;
					}
					else {
						append(n, (arr[i] - '0'));
						if(flag == 1)
							dec++;
					}
				}
				else  { 
					t->type = OPERAND;
					t->l = n;
					t->l->dec = dec;
					t->l->sign = sign;
					sign = 1; 
					dec = 0;
					flag = 0;
					current_state = next_state;
					i++;
					return t;
				}
				break;
			case OPR:
				if(arr[i - 2] == '(') {
					if(arr[i - 1] == '-')
						sign = -1;
					else
						sign = 1;
				}
				if(sign != -1) {
					t->type = OPERATOR;
					t->op = arr[i - 1];
				}
				current_state = next_state;
				if(next_state == DIG) { 
					if(arr[i] == '.') {
						flag = 1;
						dec = 0;
					}
					else {	
						m = 1;
						num = arr[i] - '0';
						if(flag == 1)
							dec++;
					}
				}
				i++;
				return t;
				break;
			case STOP:
				t->type = END;
				current_state = next_state;
				i++;
				return t;
				break;
			case ERR:
				t->type = ERROR;
				current_state = next_state;
				i++;
				return t;
				break;
		}
		current_state = next_state;
		i++;
	}
}