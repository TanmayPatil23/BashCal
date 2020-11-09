project:main.o stack.o num.o func.o token.o eval.o 
	cc -g main.o stack.o num.o func.o token.o eval.o -o bc -lm
main.o: main.c stack.h num.h eval.h
	cc -g -c main.c -Wall
stack.o: stack.c stack.h num.h
	cc -g -c stack.c -Wall
num.o: num.c num.h stack.h
	cc -g -c num.c -Wall
func.o: func.c num.h func.h stack.h
	cc -g -c func.c -Wall
token.o: token.c token.h num.h
	cc -g -c token.c -Wall
eval.o: eval.c eval.h stack.h num.h func.h token.h
	cc -g -c eval.c -Wall