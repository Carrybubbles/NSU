#ifndef  _LIB_GRAF_
#define _LIB_GRAF_


#include "lib_dyn.h"

struct vertex{
	int id;
	int x;
	int y;
	int block;
	int visited;
	struct vertex* next;
	dyn_array neighbours_weight;
	dyn_array neighbours;
};


void delete(struct vertex* graf);
struct vertex* init_graf(FILE* file);
void print_graf(struct vertex* graf);
void path(int* came_from, int start, int goal);
void A_star(struct vertex* graf, const int A, const int B);
void show(int** Matrix,int Height, int Width); // show field





#endif