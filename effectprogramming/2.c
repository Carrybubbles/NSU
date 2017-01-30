#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <xmmintrin.h>
#include <pmmintrin.h>
#include <immintrin.h>
#define MB 1024 * 1024
#define N (MB * 100)


int main(){

	//copy 1 byte 
	char* C1 = (char*)malloc(N);
	char* C2 = (char*)malloc(N);

	for(int i = 0; i < N; i++){
		C1[i] = C2[i];
	}
	
	clock_t time1 = clock();
	for(int i = 0; i < N; i++){
		C2[i] = C1[i];
	}
	clock_t diff = clock() - time1;
	
	clock_t time2 = clock();
	memcpy(C1,C2,N);
	clock_t diff2 = clock() - time2;
	printf("MyMemcpy                SystemMemcpy\n");
	printf("%lf ", ((N / (MB)) /  ((double)diff  / CLOCKS_PER_SEC)));
	printf("%lf\n", ( (N / (MB)) / ((double)diff2  / CLOCKS_PER_SEC)));
	free(C1);
	free(C2);

	// copy 2 byte
	short* S1 = (short*)malloc(N);
	short* S2 = (short*)malloc(N);
	for(int i = 0; i < N / sizeof(short); i++){
		S1[i] = S2[i];
	}
	time1 = clock();
	for(int i = 0; i < N / sizeof(short); i++){
		S2[i] = S1[i];
	}

	diff = clock() - time1;
	time2 = clock();
	memcpy(S1,S2,N);
	diff2 = clock() - time2;
	free(S1);
	free(S2);
	printf("%lf ", ((N / (MB)) /  ((double)diff  / CLOCKS_PER_SEC)));
	printf("%lf\n", ( (N / (MB)) / ((double)diff2  / CLOCKS_PER_SEC)));
	
	//copy 4 byte
	int* I1 = (int*)malloc(N);
	int* I2 = (int*)malloc(N);
	
	for(int i = 0; i < N / sizeof(int); i++){
		I1[i] = I2[i];
	}
	
	time1 = clock();
	for(int i = 0; i < N / sizeof(int); i++){
		I2[i] = I1[i];
	}
	diff = clock() - time1;
	time2 = clock();
	memcpy(I2,I1,N);
	diff2 = clock() - time2;
	free(I1);
	free(I2);
	printf("%lf ", ((N / (MB)) /  ((double)diff  / CLOCKS_PER_SEC)));
	printf("%lf\n", ( (N / (MB)) / ((double)diff2  / CLOCKS_PER_SEC)));
	
	//copy 8 byte

	long long* F1 = (long long*)malloc(N);
	long long* F2 = (long long*)malloc(N);
	
	for(int i = 0; i < N / sizeof(long long); i++){
		F1[i] = F2[i];
	}
	
	time1 = clock();
	for(int i = 0; i < N / sizeof(long long); i++){
		F2[i] = F1[i];
	}
	
	diff = clock() - time1;
	time2 = clock();
	memcpy(F2,F1,N);
	diff2 = clock() - time2;
	free(F1);
	free(F2);
	printf("%lf ", ((N / (MB)) /  ((double)diff  / CLOCKS_PER_SEC)));
	printf("%lf\n", ( (N / (MB)) / ((double)diff2  / CLOCKS_PER_SEC)));
	
	//copy 16 byte
	__m128i* II1 = (__m128i*)malloc(N);
	__m128i* II2 = (__m128i*)malloc(N);

	for(int i = 0; i < N / sizeof(__m128i); i++){
		II1[i] = II2[i];
	}

	time1 = clock();
	for(int i = 0; i < N / sizeof(__m128i); i++){
		II2[i] = II1[i];
	}
	diff = clock() - time1;
	
	time2 = clock();
	memcpy(II1,II2,N);
	diff2 = clock() - time2;
	
	free(II1);
	free(II2);
	printf("%lf ", ((N / (MB)) /  ((double)diff  / CLOCKS_PER_SEC)));
	printf("%lf\n", ( (N / (MB)) / ((double)diff2  / CLOCKS_PER_SEC)));
	
	//copy 16 byte
	__m256i* arr1 = (__m256i*)valloc(N);
	__m256i* arr2 = (__m256i*)valloc(N);
	for(int i = 0; i < N / sizeof(__m256i); i++){
		arr1[i] = arr2[i];
	}

	time1 = clock();
	for(int i = 0; i < N / sizeof(__m256i); i++){
		arr2[i] = arr1[i];
	}
	diff = clock() - time1;
	
	time2 = clock();
	memcpy(arr1,arr2,N);
	diff2 = clock() - time2;
	
	free(arr1);
	free(arr2);

	printf("%lf ", ((N / (MB)) /  ((double)diff  / CLOCKS_PER_SEC)));
	printf("%lf\n", ( (N / (MB)) / ((double)diff2  / CLOCKS_PER_SEC)));
	
}