#ifndef PATH_H
#define PATH_H

// The function that is passed to the threads
// PArams: (void *) threadID
void* thread(void*);

// Creates the square matrix the storing the result
// PArams: int size
void create_weight_matrix(int);

// Creates a square matrix of mutexes for synchronization
// Params: int size
void create_mutex_matrix(int);

// Creates a square matrix of condition variables for synchronization
// Params: int size
void create_condvar_matrix(int);

// Blocks the exection of the thread if the previous iteration on this element
// has not been completed
// Params: int i, int j, int k
void previous_iteration_complete(int, int, int);
#endif