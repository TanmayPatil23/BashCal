#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "num.h"
#include "func.h"
#include "stack.h"

void copy(number *n1, number *n2) {
	int dec, i, num, sign;
	init(n2);
	for(i = 0; i < n1->len; i++) {
		num = get(n1, i);
		append(n2, num);
	}
	dec = n1->dec;
	n2->dec = dec;
	sign = n1->sign;
	n2->sign = sign;
	return;
}

int iszero(number *n) {
	int i, flag = 0;
	for(i = 0; i < n->len; i++) {
		if(get(n, i) != 0)
			flag = 1;
	}
	return flag;	
}

number *add(number *n1, number *n2) {
	number *result;
	int sign1, sign2;
	sign1 = n1->sign;
	sign2 = n2->sign;
	result = (number *)malloc(sizeof(number));
	init(result);
	if(dec(n1) > dec(n2)) {
		int i;
		int y = (dec(n1) - dec(n2));
		for(i = 0; i < y; i++) {
			append(n2, 0);
			n2->dec++;
		}
	}
	else if(dec(n2) > dec(n1)) {
		int i;
		int y = (dec(n2) - dec(n1));
		for(i = 0; i < y; i++) {
			append(n1, 0);
			n1->dec++;
		}
	}
	
	if(n1->sign != n2->sign) {
		if(n1->sign == -1) {
			n1->sign = 1;
			result = sub(n2, n1);
		}
		else if(n2->sign == -1) {
			n2->sign = 1;
			result = sub(n1, n2);
		}
	}
	else if(n1->sign == n2->sign) {
		if(n1->sign == -1)
			result->sign = -1;
		else
			result->sign = 1;
		int num = 0, i, j;
		i = length(n1);
		j = length(n2);
		int carry = 0;
		while(i != 0 || j != 0) {
			if(i == 0) {
				num = get(n2, j - 1) + carry;
				j--;
				carry = num / 10;
				num = num % 10;
				insert(result, 0, num);
			}
			else if(j == 0) {
				num = get(n1, i -1) + carry;
				i--;
				carry = num / 10;
				num = num % 10;
				insert(result, 0, num);
			}
			else {
				num = get(n1, i - 1) + get(n2, j - 1) + carry;
				i--;
				j--;
				carry = num / 10;
				num = num % 10;
				insert(result, 0 , num);
			}
		}
		result->dec = dec(n1);
		if(carry != 0)
			insert(result, 0, carry);
	}
	n1->sign = sign1;
	n2->sign = sign2;
	return result;
}

number *sub(number *n1, number *n2) {
	int sign1, sign2;
	sign1 = n1->sign;
	sign2 = n2->sign;
	/*Make no of digits after decimal equal*/
	if(dec(n1) > dec(n2)) {
		int i;
		int y = (dec(n1) - dec(n2));
		for(i = 0; i < y; i++) {
			append(n2, 0);
			n2->dec++;
		}
	}
	else if(dec(n2) > dec(n1)) {
		int i;
		int y = (dec(n2) - dec(n1));
		for(i = 0; i < y; i++) {
			append(n1, 0);
			n1->dec++;
		}
	}
	int num;
	static int flag = 0;
	number *result;
	result = (number *)malloc(sizeof(number));
	init(result);
	if(n1->sign != n2->sign) {
		if(n2->sign == -1) {
			n2->sign = 1;
			result = add(n1, n2);
			result->sign = 1;
		}
		if(n1->sign == -1) {
			n1->sign = 1;
			result = add(n1, n2);
			result->sign = -1;
		}
	}
	else if(n1->sign == n2->sign) {
		if(n1->sign == -1) {
			n1->sign = 1;
			n2->sign = 1;
			result = sub(n2, n1);
		}
		if(n1->sign == 1) {
			if(compare(n1, n2) >= 0) {
				if(flag != 1)
					result->sign = 1;
				else
					result->sign = -1;
				int b = 0;
				int m,n;
				m = length(n1) - 1;
				n = length(n2) - 1; 
				while(m != -1 || n != -1) {
						if(n == -1) {
						num = get(n1, m);m--;
						insert(result, 0, num);
					}
					else {
						int a = get(n1, m);m--;
						int c = get(n2, n);n--;
						if(a >= c) {
							num = a - c;
							insert(result, 0, num);
						}
						else {
							int d = 0;
							while(!(b = del(n1, m))) {
								m--;
								d++;
							}
							m--;
							m++;
							insert(n1, m, b - 1);
							int i;
							for(i = 0; i < d; i++) {
								m++;
								insert(n1, m, 9);
							}
							num = 10 + a - c;
							insert(result, 0, num);
						}
					}
				}
			}
			else if(compare(n1, n2) < 0) {
				flag = 1;
				result = sub(n2, n1);
				result->sign = -1;
			}
		}
	}
	result->dec = n1->dec;
	flag = 0;
	n1->sign = sign1;
	n2->sign = sign2;
	return result;
}   



number *mul(number *n1, number *n2) {
	number *result;
	result = (number *)malloc(sizeof(number));
	init(result);
	int tempsign, sign1, sign2;
	sign1 = n1->sign;
	sign2 = n2->sign;
	if(iszero(n1) == 0)
		return n1;
	if(iszero(n2) == 0)
		return n2;	
	if(n1->sign == n2->sign) {
		tempsign = 1;
		n1->sign = n2->sign = 1;
	}
	else {
		tempsign = -1;
		n1->sign = n2->sign = 1;
	}
	int x = length(n1) - length(n2);
	if(x < 0) {
		result = mul(n2, n1);
		return result;
	}
	else {
		int n = length(n2) - 1, j, i;
		int a = length(n2), b = length(n1);
		int arr[2 * b];
		for( i = 0; i < 2 * b; i++)
			arr[i] = 0;
		int num1 = 0, num2 = 0;
		int k = 2 * b - 1;
		for( i = 0; i < a; i++) {
			int m = length(n1) - 1;
			int carry1 = 0, carry2 = 0;
			for( j = k - i; j > b - 2; j--) {
				if(m != -1 && n != -1) {
					num1 = get(n1, m) * get(n2, n) + carry1;
					m--;
					carry1 = num1 / 10;
					num1 = num1 % 10;
					num2 = arr[j] + num1 + carry2;
					carry2 = num2 / 10;
					num2 = num2 % 10;
					arr[j] = num2;
				}
				else {
					break;
				}
			}
			arr[j] = carry1 + carry2 + arr[j];
			b--; n--;
		}
		j = 0;
		for( i = 2 * length(n1) - 1; i > b - 1 && i >= 0; i--) {
			insert(result, 0, arr[i]); j++;
		}
		result->dec = n1->dec + n2->dec;
		result->sign = tempsign;
		n1->sign = sign1;
		n2->sign = sign2;
		return result;
	}
}




number *division(number *n1, number *n2) {
	if(iszero(n2) == 0) {
		printf("[INVALID INPUT] dividing by zero\n");
		return NULL;
	}
	number *result;
	result = (number *)malloc(sizeof(number));
	number *temp;
	temp = (number *)malloc(sizeof(number));
	init(temp);
	init(result);
	int m, sign1, sign2;
	sign1 = n1->sign;
	sign2 = n2->sign;
	if(n1->sign == n2->sign) {
		result->sign = 1;
		n1->sign = n2->sign = 1;
	}
	else {
		result->sign = -1;
		n1->sign = n2->sign = 1;
	}
	
	int a, b;
	m = n1->dec - n2->dec;
	int i, j, k, num;
	
	a = n1->dec;
	b = n2->dec;
	n1->dec = n2->dec = 0;
	for(i = 0; i < length(n1); i++) {
		num = get(n1, i);
		append(temp, num);
		if(compare(temp, n2) < 0) {
			append(result, 0);
		}
		else {
			int d = 0;
			while(1) {
				temp = sub(temp, n2);
				d++;
				if(compare(temp, n2) < 0)
					break;
					
			}
			append(result, d);
		}
	}
	j = 0; k = 0;
	while(j < 10) {
		append(temp, 0);
		int d = 0;
		while(compare(temp, n2) >= 0) {
			temp = sub(temp, n2);
			d++;
		}
		append(result, d);
		k++;j++;
	}
	result->dec = 10 + m;
	n1->dec = a;
	n2->dec = b;
	n1->sign = sign1;
	n2->sign = sign2;
	return result;
}


number *mod(number *n1, number *n2) {
	if(iszero(n2) == 0) {
		printf("[INVALID INPUT] modulo by zero\n");
		return NULL;
	}
	number *result;
	result = (number *)malloc(sizeof(number));
	number *temp;
	temp = (number *)malloc(sizeof(number));
	init(temp);
	init(result);
	number *copyofn2;
	copyofn2 = (number *)malloc(sizeof(number));
	init(copyofn2);
	copy(n2, copyofn2);
	int m, sign1, sign2;
	sign1 = n1->sign;
	sign2 = n2->sign;
	if(n1->sign == n2->sign) {
		result->sign = 1;
		n1->sign = n2->sign = 1;
	}
	else {
		result->sign = -1;
		n1->sign = n2->sign = 1;
	}
	
	int a, b;
	m = length(n1);
	int i, j, num;
	
	a = dec(n1);
	b = dec(n2);
	if(dec(n1) != 0) {
		n1->len = n1->len - dec(n1);
	}
	if(copyofn2->dec != 0) {
		i = dec(copyofn2);
		for(j = 0; j < i; j++) {
			del(copyofn2, copyofn2->len);
		}
	}
	for(i = 0; i < n1->len; i++) {
		num = get(n1, i);
		append(temp, num);
		if(compare(temp, copyofn2) < 0) {
			append(result, 0);
		}
		else {
			int d = 0;
			while(1) {
				temp = sub(temp, copyofn2);
				d++;
				if(compare(temp, copyofn2) < 0)
					break;
					
			}
			append(result, d);
		}
	}
	n1->len = m;
	n1->sign = sign1;
	n2->sign = sign2;
	n1->dec = a;
	n2->dec = b;
	return temp;
}

	
	
int compare(number *n1, number *n2) {
	if(n1->sign == 1 && n2->sign == -1)
		return 1;
	if(n2->sign == 1 && n1->sign == -1)
		return -1;
	/*Make no. of digits after decimal equal*/
	if(dec(n1) > dec(n2)) {
		int i;
		int y = (dec(n1) - dec(n2));
		for(i = 0; i < y; i++) {
			append(n2, 0);
			n2->dec++;
		}
	}
	else if(dec(n2) > dec(n1)) {
		int i;
		int y = (dec(n2) - dec(n1));
		for(i = 0; i < y; i++) {
			append(n1, 0);
			n1->dec++;
		}
	}
	int a = (length(n1) - length(n2));
	if(a > 0) {
		int i = 0;
		while(i < a) {
			insert(n2, 0, 0);
			i++;
		}
	}
	else if(a < 0) {
		int i = 0;
		a = -a;
		while(i < a) {
			insert(n1, 0, 0);
			i++;
		}
	}	
	
		int i;
		for(i = 1; i <= length(n1); i++) {
			if(get(n1, i - 1) > get(n2, i - 1))
				return 1;
			else if(get(n1, i - 1) < get(n2, i - 1))
				return -1;
		}
		return 0;
}

number *power(number *n1, number *n2) {
	number *result = (number *)malloc(sizeof(number));
	init(result);
	append(result, 1);
	number *num_1 = (number *)malloc(sizeof(number));
	init(num_1);
	append(num_1, 1);
	number *copyofn2 = (number *)malloc(sizeof(number));
	init(copyofn2);
	number *num_2 = (number *)malloc(sizeof(number));
	init(num_2);
	number *num_0 = (number *)malloc(sizeof(number));
	init(num_0);
	int sign = n1->sign;
	append(num_2, 2);
	append(num_0, 0);
	copy(n2, copyofn2);
	if(n2->sign == 1) {
		while(iszero(copyofn2) != 0) {
			result = mul(result, n1);
			copyofn2 = sub(copyofn2, num_1);
		}
	}
	else if(n2->sign == -1) {
		while(iszero(copyofn2) != 0) {
			result = division(result, n1);
			copyofn2 = add(copyofn2, num_1);
		}
	}
	n1->sign = sign;
	if(n1->sign == -1) {
		if(compare(mod(n2, num_2), num_0) == 0)
			result->sign = 1;
		else
			result->sign = -1;
	}
	return result; 
} 