#include <stdlib.h>

//Globals for use
int ***cube;
int cubeSize;

void create_data_cube(int size){
	cubeSize = size;
	cube = malloc(size * sizeof(int *));
	
	int i;
	int j;
	for (i = 0; i < size; i++){
		cube[i] = malloc (size * sizeof(int *));		
		for (j = 0; j < size; j++){
			cube[i][j] = calloc (size, sizeof(int));
		}
	}
}

int get_value(int i, int j, int k){
	return cube[i][j][k];
}

void set_value(int i, int j, int k, int val){
	cube[i][j][k] = val;
}

void destroy_data_cube(){
	int i;
	int j;
	for (i = 0; i < cubeSize; i++){
		for (j = 0; j < cubeSize; j++){
			free(cube[i][j]);
		}
		free(cube[i]);
	}
	free(cube);
}