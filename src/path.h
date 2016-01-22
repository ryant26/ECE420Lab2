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
#endif