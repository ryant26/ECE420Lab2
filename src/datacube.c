#include <stdlib.h>

//Globals for use
int **cube;
int cubeSize;

void create_data_cube(int size){
	cubeSize = size;
	cube = malloc(size * sizeof(int *));
	
	int i;
	for (i = 0; i < size; i++){
		cube[i] = malloc (size * sizeof(int));		
	}
}

int get_value(int i, int j){
	return cube[i][j];
}

void set_value(int i, int j, int k){
	cube[i][j] = k;
}

void destroy_data_cube(){
	int i;
	for (i = 0; i < cubeSize; i++){
		free(cube[i]);
	}
	free(cube);
}