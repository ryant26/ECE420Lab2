#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"

int parse_number_threads(int argc, char** argv, int matrix_size){
	if (argc != 2){
		printf("You didn't enter the correct number of arguments\n");
		print_usage();

		exit(EXIT_FAILURE);
	}

	int threads = atoi(argv[1]);
	if (threads < 1){
		printf("You entered an invalid number of threads\n");
		printf("Please select an integer greater than 1\n");
		print_usage();

		exit(EXIT_FAILURE);		
	}

	thread_condition_met(threads, matrix_size);

	return threads;
}

void print_usage(){
	printf("USAGE: main <integer number of threads> \n");
}

void element_creation_error(char * element){
	printf("Error Creating %s\n", element);
	exit(1);
}

void thread_condition_met(int number_threads, int matrix_size){
	if (matrix_size % number_threads != 0){
		print_error();
		exit(EXIT_FAILURE);
	}
}

void print_error(){
	printf("Please make sure the number of threads evenly divides the one dimensional size of the input matrix\n");
}