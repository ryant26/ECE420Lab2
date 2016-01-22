#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../sdk/Lab2IO.h"
#include "../sdk/timer.h"
#include "path.h"
#include "utilities.h"
#include "datacube.h"

int **A; int **W; int size; int number_threads;
pthread_mutex_t **mutex;
pthread_cond_t Condition;

int main(int argc, char * argv[]){
	number_threads = parse_number_threads(argc, argv);
	Lab2_loadinput(&A, &size);
	create_mutex_matrix(size);
	create_weight_matrix(size);
	create_data_cube(size);

	pthread_t threads[number_threads];
	pthread_cond_init(&Condition, NULL);
	
	double start_time;
	double end_time;
	GET_TIME(start_time);

	int i;
	for (i = 0; i < number_threads; i++){
		if (pthread_create(&threads[i], NULL, thread, (void *) i)){
			element_creation_error("Thread");
		}	
	}
	for (i = 0; i < number_threads; i++){
		pthread_join(threads[i], NULL);
	}

	GET_TIME(end_time);
	printf("The elapsed time is: %f\n", end_time - start_time);

	Lab2_saveoutput(W, size, end_time - start_time);

	return 0;
}

void* thread(void* thread_id){
	int id = (int) thread_id;
	int rows = (size/number_threads);
	int offset = id * rows;

	int i;
	int j;
	int k;
	for (k = 0; k < size; k++){
		for (i = offset; i < offset + rows; i++){
			for (j = 0; j < size; j++){
				pthread_mutex_t *lock = &mutex[i][j];
				pthread_mutex_lock(lock);

				while ( k > 0
					&& (get_value(i, j, k-1) == 0
					|| get_value(i, k, k-1) == 0
					|| get_value(k, j, k-1) == 0) ) {
					pthread_cond_wait (&Condition, lock);
				}

				if (W[i][k] + W[k][j] < W[i][j]){
					W[i][j] = W[i][k] + W[k][j];
				}

				set_value(i, j, k, 1);
				
				pthread_mutex_unlock(lock);
				pthread_cond_signal(&Condition);
			}
		}
	}
	return 0;
} 

void create_weight_matrix(int size){
	W = malloc(size * sizeof(int *));
	int i;
	int j;
	for (i = 0; i < size; i++){
		W[i] = malloc (size * sizeof(int));
	}
	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			W[i][j] = A[i][j];
		}
	}
}

void create_mutex_matrix(int size){
	mutex = malloc(size * sizeof(pthread_mutex_t *));
	int i;
	int j;
	for (i = 0; i < size; i++){
		mutex[i] = malloc (size * sizeof(pthread_mutex_t));
	}
	for(i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			if (pthread_mutex_init(&mutex[i][j], NULL)){
				element_creation_error("Mutex");
			}
		}
	}		 
}