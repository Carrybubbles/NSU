#include <stdio.h>
#include <stdlib.h>
#include "lib_dyn.h"

int getAT(dyn_array arr, int index)
{
	return arr.buffer[index];
}

dyn_array init_array(int size)
{
	dyn_array arr;
	arr.buffer = (int*)calloc(sizeof(int),size);
	arr.real_size = 0;
	arr.buffer_size = size;
	return arr;
}

dyn_array grow(dyn_array arr)
{
	int* new_buffer = (int*)calloc(sizeof(int),arr.buffer_size*2);
	int i = 0;

	for(i = 0; i < arr.real_size ;++i)
	{
		new_buffer[i] = arr.buffer[i];	
	}
	free(arr.buffer);
	arr.buffer = new_buffer;
	arr.buffer_size *=2 ;
	return arr;
}

dyn_array add(dyn_array arr,int element)
{
	if(arr.real_size == arr.buffer_size)
		arr = grow(arr);
	arr.buffer[arr.real_size++] = element;
	return arr;
}