#include <stdio.h>
#include <stdlib.h>

#define max(a,b) ((a) >= (b)) ? (a) : (b)


struct cell{
	int weigth;
	int gold;
};

void Clean_that_table(int** Matrix,int Height)// free Matrix
{
	int w = 0;
	
    for (w = 0; w < Height; w++)
    	free(Matrix[w]);
    
    free(Matrix);

}

int** init_Matrix(int Height,int Width)
{
    int i = 0;

    int **Matrix = (int**)calloc(Height,sizeof(int*));
    for (i = 0; i < Height; i++)
    {
        Matrix[i] = (int*)calloc(Width,sizeof(int));
    }
    
    return Matrix;

}

struct cell* init_struct(int size,int weigth, int gold) // create a hash table
{
    struct cell* table = (struct cell*)calloc(size,sizeof(*table));
    int i = 0;
    int j = 0;

    if (NULL == table)
        return NULL;

    for (i = 0; i < size; i++)
    {
       scanf("%d %d",&table[i].weigth,&table[i].gold);
       
    }

    return table;
}

void show(int** Matrix,int Height, int Width) // show field
{ 
    int i = 0;
    for (i = 0; i < Height; i++)
    {
        int j = 0;
        for (j = 0; j < Width; j++)
        {
            printf(" %d ",Matrix[i][j]);
        }
        putchar('\n');
    }
	putchar('\n');
}

int** Matrix_end(int** Matrix,int N, int Weight_of_knapsack,struct cell* table)
{
	int i = 0;
	int j = 0;
	
	for(i = 1; i < N + 1;i++)
	{
		for (j = 1;j < Weight_of_knapsack + 1;j++)
		{
			if( j - table[i-1].weigth >= 0)
			{
				Matrix[i][j] = max(Matrix[i-1][j - table[i-1].weigth] + table[i-1].gold, Matrix[i-1][j]);
			}
			else
			{
				Matrix[i][j] = Matrix[i-1][j];
			}
		}
	}
	
	return Matrix;
}

void result(int** Matrix,int N,int Weight_of_knapsack,struct cell* table)
{
	int i = N;
	int j = Weight_of_knapsack;

	while( i > 0)
	{
		if (Matrix[i][j] == Matrix[i-1][j] )
		{
			i--;
		}
		else if ( Matrix[i][j] != Matrix[i-1][j])// WE NEED ARRAY TO AVOID REPETITION
		{	
			printf(" %d ",i);
			j -= table[i-1].weigth;
			i--; 
		}
	}
}

int main()
{
	int N = 0;
	int Weight_of_knapsack = 0;
	int gold = 0;
	int weigth = 0;
	int i = 0;
	int j = 0;
	printf("Amount of items ");
	scanf("%d",&N);
	printf("Max capacity of BAG ");
	scanf("%d",&Weight_of_knapsack);
	int** Matrix = init_Matrix(N+1,Weight_of_knapsack+1);
	int** Matrix2 = init_Matrix(N+1,Weight_of_knapsack+1);
	printf("Enter items (weight,gold) ");
	struct cell* table = init_struct(N,weigth,gold);
	
	Matrix_end(Matrix,N,Weight_of_knapsack,table);
	show(Matrix,N+1,Weight_of_knapsack+1);
	result(Matrix,N,Weight_of_knapsack,table);
	Clean_that_table(Matrix,N);
}
