#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char ** argv){
	srand(atoi(argv[1]));
	int x = 0;
	while(x < atoi(argv[2])){
		x++;
		printf("%f\n", ((double)rand())/((double)RAND_MAX));
	}
//	return 0;
	printf("RAND_MAX: %i\n", RAND_MAX);
	return 0;
}
