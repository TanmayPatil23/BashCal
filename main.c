#include "stack.h"
#include "num.h"
#include "eval.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdlib.h>
#define LEN 200
int main(int argc, char* argv[]) {
	if(argc == 2 && (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0)) {
		printf("BC version 1.0\n");
		return 0;
	}
	if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
		printf("OPTIONS\n-i, --interactive\n\tForce interactive mode.\n-q, --quiet\n\tDo not print the normal GNU bc welcome.\n-o, --original\n\tRuns the original bc (Use on LINUX distros only).\n");
		return 0;
	}
	if (argc == 2 && (strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "--interactive") == 0)) {
		printf("Entering an interactive mode...\n");
		printf("This is BC.\n version 1.0\n Fully written in C.\n Hope that it doesn't have bugs.\n");
		printf("This is free software with ABSOLUTELY NO WARRANTY.\nFor details type `warranty'.\n");
	}
	if (argc == 2 && (strcmp(argv[1], "-q") == 0 || strcmp(argv[1], "--quiet") == 0)) {
		printf("Entering an quiet mode...\n");
	}
	if (argc == 2 && (strcmp(argv[1], "-o") == 0 || strcmp(argv[1], "--original") == 0)) {
		printf("[RUNNING THE ORIGINAL BC]\n\n");
		system("bc");
		return 0;
	}
	if(argc == 1) {
		printf("BC Version 1.0\nFully written in C.\nHope that it doesn't have bugs.\n");
		printf("This is free software with ABSOLUTELY NO WARRANTY.\nFor details type `warranty'.\n\n");
	}
	char str[LEN];	
	int x;
	number *res;
	number *last;
	res = (number *)malloc(sizeof(number));
	last = (number *)malloc(sizeof(number));
	init(res);
	init(last);
	append(last, 0);
	while((x = read(str, LEN))) {
		if (strcmp(str, "quit") == 0 || strcmp(str, "exit") == 0) {
			break;
		}
		else if (strcmp(str, "clear") == 0) {
			system("clear");
		}
		else if(strcmp(str, "last") == 0) {
			traverse(last);
			printf("\n");
		}
		else if (strcmp(str, "warranty") == 0) {
			printf("This program is free software; you can redistribute it and/or modify it under certain terms...\n");
		}
		else if (strcmp(str, "ibase") == 0) {
			printf("%d\n", 10);
		}
		else if (strcmp(str, "obase") == 0) {
			printf("%d\n", 10);
		}
		else {
			res = solve(str);
			if(res == NULL) {
				fprintf(stderr, "[ERROR] unexpected expression\n");
			}  
			else { 
				copy(res, last);
				traverse(res);
				printf("\n");
			}
		}
	}
	return 0;
}