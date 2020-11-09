#ifndef __FUNC__
#define __FUNC__
#include "num.h"
void copy(number *n1, number *n2);
int compare(number *n1, number *n2);
int iszero(number *n);
number *add(number *n1, number *n2);
number *sub(number *n1, number *n2);
number *mul(number *n1, number *n2);
number *division(number *n1, number *n2);
number *mod(number *n1, number *n2);
number *power(number *n1, number *n2);
#endif