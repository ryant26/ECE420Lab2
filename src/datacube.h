#ifndef DATACUBE_H
#define DATACUBE_H

// This function creates a cube of integers for tracking
// which iterations have been completed. 
// Params: int edge Length
void create_data_cube(int);

// This function retreives a value from the data cube
// Params: int i, int j, int k (indicies)
int get_value(int, int, int);

// This function sets a value from the data cube
// Params: int i, int j, int k (indicies)
void set_value(int, int, int, int);

// This function destroys the malloc-ed data cube
void destroy_data_cube();

#endif