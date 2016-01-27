#ifndef UTILITIES_H
#define UTILITIES_H

// The function to parse the number of threads from the 
// command line
// Params: int argc, char** argv, int matrix size
int parse_number_threads(int, char**, int);

//Prints the usage of the binary from the terminal
void print_usage();

// Used for printing errors when creating elements like threads
void element_creation_error(char*);

// Used for testing if the passed number of threads is valid
// Params: int number of threads, int matrix size
void thread_condition_met(int, int);

// Prints a specific error if a thread condition is not met
void print_error();

#endif