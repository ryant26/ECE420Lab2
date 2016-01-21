#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../sdk/Lab2IO.h"
#include "../sdk/timer.h"
#include "path.h"
#include "utilities.h"

pthread_cond_t*** Condition;
int **A; int **W; int size;
pthread_mutex_t **mutex;

int main(char **argv, int argc){
	int number_threads = parse_number_threads(argc, argv);
	Lab2_loadinput(&A, &size);
	create_condition_variables(size);
	create_mutex_matrix(size);
	create_weight_matrix(size);
	pthread_t threads[number_threads];



}

void* thread(void* thread_id){

} 

void create_condition_variables(int size){
	Condition = malloc(size * sizeof(pthread_cond_t *));
	int i;
	int j;
	int k;
	for (i = 0; i < size; i++){
		Condition[i] = malloc (size * sizeof(pthread_cond_t *));		
		for (j = 0; j < size; j++){
			Condition[i][j] = malloc (size * sizeof(pthread_cond_t *));
		}
	}
	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			for (k = 0; k < size; k++){
				if (pthread_cond_init(&Condition[i][j][k], NULL)){
					printf("Error creating condition variable\n");
					exit(1);
				}
			}
		}
	}
}

void create_weight_matrix(int size){
	W = malloc(size * sizeof(int *));
	int i;
	for (i = 0; i < size; i++){
		W[i] = malloc (size * sizeof(int *));
	}
}

void create_mutex_matrix(int size){
	mutex = malloc(size * sizeof(pthread_mutex_t *));
	int i;
	int j;
	for (i = 0; i < size; i++){
		mutex[i] = malloc (size * sizeof(pthread_mutex_t *));
	}
	for(i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			if (pthread_mutex_init(&mutex[i][j], NULL)){
				printf("Error initalizing mutex\n");
				exit(1);
			}
		}
	}		 
}