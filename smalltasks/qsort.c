#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap_any(const void* a, const void* b, size_t size)
{
  int i = 0;
  for(i = 0; i < size; i++)
  {
    char temp = *((char*)a + i);
    *((char*)a + i) = *((char*)b + i);
    *((char*)b + i) = temp;
  }
}

int comp_2(const void* a,const void* b)
{
	return strcmp((char*)a,(char*)b);
}

int comp_1(const void* a,const void* b)
{
	return (*(int*)a  > *(int*)b);
}

void qsort_1(void* array, size_t size, int N, int (*cmp)(const void*, const void*))
{
	int j = 0;
	int i = 0;
	
	for (i = 0; i < N - 1;  i++)
	{
		for (j = 0; j < N - 1 - i; j++)
		{
			if(cmp((char*)array + size*j, (char*)array + (j+1)*size) > 0)
				swap_any((char*)array + j*size, (char*)array + (j+1)*size, size);	
		}
	}
}

int main()
{
	int arr[7] = {0x80000000,2,1,5,4,6,0x80000001};
	char* arr2[7] = {"lol","ale","fit","a","z","c","qwe"};
	
	qsort_1(arr,sizeof(int),7,comp_1);
	qsort_1(arr2,sizeof(char*),7,comp_2);
	int i = 0;

	for ( i = 0 ; i < 7;i++)
		printf("%d ",arr[i]);
	printf("\n");
	for (i = 0; i < 7;i++)
		printf("(%s)",arr2[i]);
}