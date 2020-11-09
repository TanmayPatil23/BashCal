#ifndef __EVAL__
#define __EVAL__
#include "stack.h"
#include "num.h"
#include "func.h"
int precedence(char op);
int read(char *arr, int len);
number *solve(char *str);
#endif