#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <math.h>
#include <x86intrin.h>
#include <limits.h>
#include <sched.h>
#include <pthread.h>

#define THREAD_SIZE 2
#define HEIGHT 1024
#define WIDTH 2038
#define ARR2

typedef unsigned long long lld;

lld time_start() { 
	return __rdtsc();
}

unsigned long long time_stop(lld t0) { 
	return __rdtsc()-t0; 
}

#ifdef ARR1
volatile int arr[128] = {0};
void my_barrier(volatile int arr[128], int id){
	if(id == 0){

		for(int i = 1; i < THREAD_SIZE; ++i){
			while(arr[i] == 0){
			}	
		}

		for (int i = 1; i < THREAD_SIZE; ++i)
		{
			arr[i]++;	
		}
		return;
	}else{
		arr[id]++;
		while(arr[id] != 2);
		arr[id] = 0;
		return;
	}

}

#endif

#ifdef ARR2
volatile int arr[128][64] = {{0}};
void my_barrier(volatile int arr[128][64], int id){
	if(id == 0){

		for(int i = 1; i < THREAD_SIZE; ++i){
			while(arr[i][0] == 0){
			}	
		}

		for (int i = 1; i < THREAD_SIZE; ++i)
		{
			arr[i][0]++;

		}
		return;
	}else{
		arr[id][0]++;
		while(arr[id][0] != 2);
		arr[id][0] = 0;
		return;
	}


}

#endif



void show_arr(float* arr){
	for(int i = 0 ; i < WIDTH; i++){
		for (int j = 0; j < HEIGHT; ++j)
		{
			printf("%.3g ",arr[i*WIDTH + j] );
		}
		printf("\n");
	}
		printf("\n");
}

int min(int a, int b){
	if(a < b){
		return a;
	}else{
		return b;
	}
}

int max(int a, int b){
	if(a > b){
		return a;
	}else{
		return b;
	}
}
void  stick_this_thread_to_core(int core_id) {
   cpu_set_t cpuset;
   CPU_ZERO(&cpuset);
   CPU_SET(core_id, &cpuset);
   pthread_t current_thread = pthread_self();
   pthread_setaffinity_np(current_thread, sizeof(cpu_set_t), &cpuset);
   		

}
int main(int argc, char const *argv[])
{

    float* src = (float*)calloc(WIDTH * HEIGHT, sizeof(double));
    for(int i = 0 ; i < WIDTH*HEIGHT; ++i){
    	src[i] = rand();
    } 
    float* dst = (float*)calloc(WIDTH * HEIGHT, sizeof(double)); 
	#pragma omp parallel  num_threads(THREAD_SIZE)
	{
		int id = omp_get_thread_num();
		stick_this_thread_to_core(id);	
		lld time = 0;
   		lld min = 0;
   		int q = 0;
   		for(q = 0 ; q < 1000; q++){
   			#pragma omp for
   			for(int i = 0; i < HEIGHT; i++){
        		for(int j = 0; j < WIDTH; j++) {
            		double val = 0; 
            		double wsum = 0;
            		int counter = 0;
            		wsum += src[i*(HEIGHT) + j];	            	
            		if(i > 0){
            			wsum += src[i*(HEIGHT - 1) + j];	            	
            			counter++;
            		}
            		if(i < HEIGHT - 1){
            			wsum += src[i*(HEIGHT + 1) + j];	            	
            			counter++;
            		}
            		
            		if(j < WIDTH - 1){
            			wsum += src[i*(HEIGHT) + j + 1];	            	
            			counter++;
            		}
            		if(j > 0){
            			wsum += src[i*(HEIGHT) + j - 1];	  
            			counter++;
            		}          		
            		dst[i*HEIGHT+j] = round(wsum / counter);            
        		}
    		}
    		
    		lld start = time_start();	
        	// my_barrier(arr,id);
			#pragma omp barrier
			time = time_stop(start) ;
			min += time;
    	}
		printf(" %d %lld\n", id, min/1000LL);
	}

	free(src);
	free(dst);
	return 0;
}