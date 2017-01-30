#include <stdio.h>
#include <stdlib.h>
#include "lib_graf.h"
#include "fibo.h" 


int main(int argc,char* argv[])
{
    struct vertex* graph = NULL;
    FILE* file = NULL;
    int a = 0;
    int b = 0;
    
    if (argc > 1)
    {
	file = fopen(argv[1],"r");
    }
    else
    {	
	printf("Segmentation fault (core dumped)!\n");
	return 1;
    } 
    
    if(NULL == file)
    {
	printf("Segmentation fault (core dumped)!\n");
	return 1;
    }
    
    printf("Enter start and goal ");
    scanf("%d %d",&a, &b);
    
    graph = init_graf(file);
    
    putchar('\n');
    
    print_graf(graph);	
    
    A_star(graph,a,b);
    
    delete(graph);
    fclose(file);
}