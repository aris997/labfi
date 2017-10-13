#include <stdio.h>
#include <stdlib.h>


int somma(int, int);
int diff(int, int);

int main (int argc, char *argv[]) {

	int i, a=7, b=5, result;

  	if (argv == 0) i = 0;
  	else if (*argv != 0) i = atof(argv[1]);
  	else exit(EXIT_FAILURE);

	int (*algorithm)(int a, int b);

	if (i==1) algorithm = &somma;
	else algorithm = &diff;
	printf("%d\n", i);



	result = algorithm(a, b);
	printf("%d\n", result);
	return 0;
}

int somma(int a, int b) {
	return a + b;
}

int diff(int a, int b) {
	return a - b;
}