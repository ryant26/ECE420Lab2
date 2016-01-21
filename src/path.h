#ifndef PATH_H
#define PATH_H

void create_condition_variables(int);
void* thread(void*);
void block_cond(int, int);
void signal_cond(int, int);
void create_weight_matrix(int);
#endif