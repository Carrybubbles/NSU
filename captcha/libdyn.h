#ifndef _LIB_DYN_
#define _LIB_DYN_

typedef struct massiv{
    int real_size;
    double* buffer;
    int buffer_size;
}dyn_array;

int getAT(dyn_array arr, const int index);
dyn_array* init_array(const int size);
void grow(dyn_array* arr);
void add(dyn_array* arr, const double element);

#endif