#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"

int parse_number_threads(int argc, char** argv){
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

	return threads;
}

void print_usage(){
	printf("USAGE: main <integer number of threads> \n");
}

void element_creation_error(char * element){
	printf("Error Creating %s\n", element);
	exit(1);
}