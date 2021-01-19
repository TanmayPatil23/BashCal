# BC -- An Arbitrary precision calculator

## Overview
This is an attempt to replicate the functionalities of the bc command on Unix based systems. In tthis we could do all the basic arithmetics like addition, substraction, multiplication and division. With all those basic functions, one can also have power and modulo function for their assistance.

## Data Types and Backbone of the program
Here, I have a linked list that stores the digits of an arbitrary long number and with that to make infix evaluations easier we have here two stacks for the calculational purposes

## Extras
Apart from the orthodox function, one can have *clear*, *obase*, and *ibase* as some other functions to make their life more easy.
Notably, one also has a *last* function that stores the value of the last final answer of the evaluation and works same as "_"(underscore) in the python shell prompt.
