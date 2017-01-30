
//Knight's tour problem 

#include <stdio.h>
#include <stdlib.h>

#define MAX_MOVES 8

int cmp (const void* a, const void* b)
{
   int* a1 = *(int*)a; // два адреса!!!!!!!1111
   int* b1 = *(int*)b;
   printf("a1 = %d, b1 = %d\n", a1[2], b1[2]);
  return (a1[2] > b1[2]);
}

int** init(int Height, int Width)
{
  int i = 0;

  int **Matrix = (int**)calloc(Height, sizeof(int*));
  
  for (i = 0; i < Height; i++)
  {
    Matrix[i] = (int*)calloc(Width, sizeof(int));
  }

  return Matrix;
}

void Clean_that_table(int** Matrix, int Height)// free Matrix
{
  int w = 0;
    
  for (w = 0; w < Height; w++)
    free(Matrix[w]);
  
  free(Matrix);

}

int check(int x, int y, int Height, int Width)
{
  return (x >= 0 && y >= 0 && x < Width && y < Height);
}

void show(int** Matrix, int Height, int Width) // show field
{ 
  int i = 0;

  for (i = 0; i < Height; i++)
  {
    int j = 0;
    for (j = 0; j < Width; j++)
    {
      printf(" %3d ", Matrix[i][j]);
    }
    putchar('\n');
  }
  putchar('\n');
}


void find_min(int steps[8][3], int** Matrix, int x, int y, int Height, int Width)
{
  int i = 0;
  int j = 0;
  int next_X = 0;
  int next_Y = 0;
  int next_X2 = 0;
  int next_Y2 = 0;
  int count_moves = 0;

  int Moves[MAX_MOVES][2] = { // possible moves of knight
    {1,2},
    {2,1},
    {-1,-2},
    {-2,-1},
    {2,-1},
    {-1,2},
    {-2,1},
    {1,-2},
  }; 
  
  for (i = 0; i < MAX_MOVES; i++) // 1 step
  {
    next_X = x + Moves[i][0];
    next_Y = y + Moves[i][1]; 
    count_moves = 0;
    
    if (check(next_X,next_Y,Height,Width) && !Matrix[next_Y][next_X])
    {   
      
      for (j = 0; j < MAX_MOVES; j++) // 2 step
      {
        next_X2 = next_X + Moves[j][0];
        next_Y2 = next_Y + Moves[j][1];
        
        if (check(next_X2, next_Y2, Height, Width) && !Matrix[next_Y2][next_X2])
        {
          count_moves++;
        }
      }
      //array of min steps 
      steps[i][0] = Moves[i][0];
      steps[i][1] = Moves[i][1];             
      steps[i][2] = count_moves;

    }
  }
}

int move(int** Matrix, int x, int y, int Height, int Width, int count)// recursive function 
{
  int i = 0;
  int dx = 0;
  int dy = 0;
  
  int steps[8][3] = {{0}};
  find_min(steps, Matrix, x, y, Height, Width);
  qsort(steps, 8, 3*sizeof(int), cmp); // sort in increase order 

  
  if((count - 1)  == (Height*Width)) // END
  {
    printf("Uspeh\n");
    show(Matrix, Height, Width);
    return 1;        
  }
  
  for( i = 0; i < MAX_MOVES; i++) 
  {
    if(steps[i][0] && steps[i][1]) // if we have possible moves 
    {
      dx = steps[i][0]; 
      dy = steps[i][1];
      
      if(check(x+dx, y+dy, Height, Width) && !Matrix[y+dy][x+dx])
      {
        Matrix[y+dy][x+dx] = count;
        if(move(Matrix, x+dx, y+dy, Height, Width, count + 1)) 
          return 1;
        else
          Matrix[y+dy][x+dx] = 0;
      }
    }
  }
  return 0;
}

int main()
{
  // int Height = 0;
  // int Width = 0;
  // int x = 0;
  // int w = 0 ;
  // int y = 0;
  
  // int** Matrix = NULL;
  
  // printf("Enter size of Matrix ");
  // scanf("%d %d",&Height, &Width);

  // Matrix = init(Height, Width);
 
  // printf("Enter position(x,y) ");
  // scanf("%d %d",&x,&y);
  
  // if (x >= Height || y >= Width || y < 0 || x < 0)
  // {
  //   printf("U kidding me?\n");
  //   Clean_that_table(Matrix, Height);
  //   return 1;
  // }
  
  // Matrix[y][x] = 1;
  
  int** Matrix1 = init(8,3);

  Matrix1[2][2] = 1;
  qsort(Matrix1,8, sizeof(int*), cmp);

  show(Matrix1,8,3);



  // if(!move(Matrix, x, y, Height, Width, 2))
  // {
  //   printf("FAIL\n");
  //   Clean_that_table(Matrix, Height);
  //   return 0;
  // }
  // Clean_that_table(Matrix, Height);

}
