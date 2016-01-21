#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../sdk/Lab2IO.h"
#include "../sdk/timer.h"
#include "path.h"

pthread_cond_t** Condition;
int **A; int size;

int main(char **argv, int argc){
	Lab2_loadinput(&A, &size);
	create_condition_variables(size);
}

void create_condition_variables(int size){
	Condition = malloc(size * sizeof(pthread_cond_t *));
	int i;
	for (i = 0; i < size; i++){
		Condition[i] = malloc (size * sizeof(pthread_cond_t *));
	}
}