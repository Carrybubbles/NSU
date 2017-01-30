#ifndef _LIB_DYN_
#define _LIB_DYN_

typedef struct massiv{
	int real_size;
	int* buffer;
	int buffer_size;
}dyn_array;

int getAT(dyn_array arr, int index);
dyn_array init_array(int size);
dyn_array grow(dyn_array arr);
dyn_array add(dyn_array arr,int element);

#endif