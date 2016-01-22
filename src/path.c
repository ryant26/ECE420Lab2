#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../sdk/Lab2IO.h"
#include "../sdk/timer.h"
#include "path.h"
#include "utilities.h"
#include "datacube.h"

// Globals for use
int **A; int **W; int size; int number_threads;
pthread_mutex_t **mutex;
pthread_cond_t Condition;
pthread_cond_t **CondMatrix;

int main(int argc, char * argv[]){

	//Initialization functions
	number_threads = parse_number_threads(argc, argv);
	Lab2_loadinput(&A, &size);
	create_mutex_matrix(size);
	create_weight_matrix(size);
	create_data_cube(size);
	create_condvar_matrix(size);

	// Pthreads / Synchronication initialization
	pthread_t threads[number_threads];
	pthread_cond_init(&Condition, NULL);
	
	// Initialize Times
	double start_time;
	double end_time;
	GET_TIME(start_time);

	// Start worker threads
	int i;
	for (i = 0; i < number_threads; i++){
		if (pthread_create(&threads[i], NULL, thread, (void *) i)){
			element_creation_error("Thread");
		}	
	}

	// Join worker threads
	for (i = 0; i < number_threads; i++){
		pthread_join(threads[i], NULL);
	}

	// Retrieve elapsed time
	GET_TIME(end_time);

	Lab2_saveoutput(W, size, end_time - start_time);

	return 0;
}

void* thread(void* thread_id){
	// Initialize thread specific variables
	int id = (int) thread_id;
	int rows = (size/number_threads);
	int offset = id * rows;

	// Loop vars
	int i;
	int j;
	int k;

	// Loop through matrix n^3 times to find shortest path
	for (k = 0; k < size; k++){
		for (i = offset; i < offset + rows; i++){
			for (j = 0; j < size; j++){

				// Ensure previous iterations have finished for cells we need
				if (k > 0){
					previous_iteration_complete(i, j, k);
					previous_iteration_complete(i, k, k);
					previous_iteration_complete(k, j, k);
				}

				//Protect the currently worked on cell
				pthread_mutex_t *lock = &mutex[i][j];
				pthread_mutex_lock(lock);

				// Replace current cost with shortes cost
				if (W[i][k] + W[k][j] < W[i][j]){
					W[i][j] = W[i][k] + W[k][j];
				}

				// Log a completed cell iteration in data cube
				set_value(i, j, k);
				
				// Unlock mutex, signal waiting threads to check if their cell is completed
				pthread_cond_signal(&CondMatrix[i][j]);
				pthread_mutex_unlock(lock);
			}
		}
	}
	return 0;
}

void create_condvar_matrix(int size){
	// Create outer array
	CondMatrix = malloc(size * sizeof(pthread_cond_t *));
	
	//Create inner array
	int i;
	int j;
	for(i =0; i < size; i++){
		CondMatrix[i] = malloc(size * sizeof(pthread_cond_t));
	}

	// Initialize condition variables
	for(i =0; i < size; i++){
		for(j =0; j < size; j++){
			pthread_cond_init(&CondMatrix[i][j], NULL);
		}
	}
} 

void create_weight_matrix(int size){
	// Create outter array
	W = malloc(size * sizeof(int *));
	
	// Create inner arrays
	int i;
	int j;
	for (i = 0; i < size; i++){
		W[i] = malloc (size * sizeof(int));
	}

	// Copy original cost matrix to weight matrix
	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			W[i][j] = A[i][j];
		}
	}
}

void create_mutex_matrix(int size){
	// Create outter array
	mutex = malloc(size * sizeof(pthread_mutex_t *));
	
	// Create inner arrays
	int i;
	int j;
	for (i = 0; i < size; i++){
		mutex[i] = malloc (size * sizeof(pthread_mutex_t));
	}

	// Initialize mutexes
	for(i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			if (pthread_mutex_init(&mutex[i][j], NULL)){
				element_creation_error("Mutex");
			}
		}
	}		 
}

void previous_iteration_complete(int i, int j, int k){
	// Lock the condition variables protecting mutex
	pthread_mutex_lock(&mutex[i][j]);

	// Check if the previous iteration has been completed
	int value = get_value(i, j);
	while ( value != k && value != k-1) {
		pthread_cond_wait (&CondMatrix[i][j], &mutex[i][j]);
	}

	// Unlock the protecting mutex
	pthread_mutex_unlock(&mutex[i][j]);
}
