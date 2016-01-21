#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../sdk/Lab2IO.h"
#include "../sdk/timer.h"
#include "path.h"
#include "utilities.h"

pthread_cond_t** Condition;
int **A; int **W; int size;
pthread_mutex_t mutex;

int main(char **argv, int argc){
	int number_threads = parse_number_threads(argc, argv);
	Lab2_loadinput(&A, &size);
	create_condition_variables(size);
	pthread_t threads[number_threads];

	//Init mutex
	if (pthread_mutex_init(&mutex, NULL)){
		printf("Error initalizing mutex\n");
		exit(1);
	}


}

void* thread(void* thread_id){

} 

void create_condition_variables(int size){
	Condition = malloc(size * sizeof(pthread_cond_t *));
	int i;
	int j;
	for (i = 0; i < size; i++){
		Condition[i] = malloc (size * sizeof(pthread_cond_t *));
	}
	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			if (pthread_cond_init(&Condition[i][j], NULL)){
				printf("Error creating condition variable\n");
				exit(1);
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

void block_cond(int i, int j){
	pthread_mutex_lock(&mutex);
	pthread_cond_wait (&Condition[i][j], &mutex);
	pthread_mutex_unlock(&mutex);

}

void signal_cond(int i, int j){
	pthread_mutex_lock(&mutex);
	pthread_cond_signal(&Condition[i][j]);
	pthread_mutex_unlock(&mutex);
}