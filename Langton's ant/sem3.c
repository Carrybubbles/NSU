#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include <conio.h>
#include <assert.h>

#define Up 100
#define Down 101
#define Left 102
#define Right 103
#define MAX_LINE 256 
#define MAX_COLOR 10
#define Rectangle 219

enum ConsoleColor
{
  Black = 0,
  Blue = 1,
  Green = 2,
  Cyan = 3,
  Red = 4,
  Magenta = 5,
  Brown = 6,
  LightGray = 7,
  DarkGray = 8,
  LightBlue = 9,
  LightGreen = 10,
  LightCyan = 11,
  LightRed = 12,
  LightMagenta = 13,
  Yellow = 14,
  White = 15
};

void ClearScreen()
{
  HANDLE                     hStdOut;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD                      count;
  DWORD                      cellCount;
  COORD                      homeCoords = { 0, 0 };
  hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
  if (hStdOut == INVALID_HANDLE_VALUE) 
    return;
  /* Get the number of cells in the current buffer */
  if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) 
    return;
  cellCount = csbi.dwSize.X *csbi.dwSize.Y;
  /* Fill the entire buffer with spaces */
  if (!FillConsoleOutputCharacter(hStdOut,(TCHAR) ' ',cellCount,homeCoords,&count)) 
    return;
  /* Fill the entire buffer with the current colors and attributes */
  if (!FillConsoleOutputAttribute(hStdOut,csbi.wAttributes,cellCount,homeCoords,&count)) 
    return;
  /* Move the cursor home */
  SetConsoleCursorPosition( hStdOut, homeCoords );
}

void Field(FILE *file, const int Height, const int Width, int **Matrix, char *argv[], const char *move)
{
  int x = 0;
  int y = 0;
  int s = 0;
  char str[MAX_LINE] = {0};
  file = fopen(argv[0], "r");
  assert(file);
  while(fgets(str, MAX_LINE, file))
  {
    sscanf(str, "#XYS_ %d %d %d", &x, &y, &s);
    assert (x <= Height);
    assert (y < = Width);
    assert (s <= strlen(move));
    Matrix[x][y] = s;
  }
  fclose(file); 
}
void ShowField (const int Height, const int Width, int **Matrix)
{
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  assert(Height);
  assert(Width);
  int i = 0;
  for (i = 0; i < Height; i++)
  {
    int j = 0;
    for (j = 0; j < Width; j++)
    {
      if ( 3 == Matrix[i][j] )
      {
        SetConsoleTextAttribute(hConsole, (WORD) ((White << 4) | Red));
        printf("%c", Rectangle);        
      }
      else if (1 == Matrix[i][j])
      {
        SetConsoleTextAttribute(hConsole, (WORD) ((White << 4) | LightGreen));
        printf("%c", Rectangle);        
      }
      else if (4 == Matrix[i][j])
      {
        SetConsoleTextAttribute(hConsole, (WORD) ((White << 4) | LightMagenta));
        printf("%c", Rectangle);        
      }
      else if (5 == Matrix[i][j])
      {
        SetConsoleTextAttribute(hConsole, (WORD) ((White << 4) | Cyan));
        printf("%c", Rectangle);        
      }
      else if (6 == Matrix[i][j])
      {
        SetConsoleTextAttribute(hConsole, (WORD) ((White << 4) | Magenta));
        printf("%c", Rectangle);        
      }
      else if (7 == Matrix[i][j])
      {
        SetConsoleTextAttribute(hConsole, (WORD) ((White << 4) | Green));
        printf("%c", Rectangle);        
      }
      else if (2 == Matrix[i][j])
      {
        SetConsoleTextAttribute(hConsole, (WORD) ((White << 4) | Brown));
        printf("%c",Rectangle);        
      }
      else if (0 == Matrix[i][j])
      {
        SetConsoleTextAttribute(hConsole, (WORD) ((White << 4) | Black));
        printf(" ");        
      }
      else if (8 == Matrix[i][j])
      {
        SetConsoleTextAttribute(hConsole, (WORD) ((White << 4) | Black));
        printf("%c",Rectangle);        
      }
      else if (9 == Matrix[i][j])
      {
        SetConsoleTextAttribute(hConsole, (WORD) ((White << 4) | Blue));
        printf("%c",Rectangle);        
      }
    }
    printf("\n");
  }
  printf("\n");
}

void Jump(int *i, int const format) /*тороидальное поле*/
{
  *i = ((*i % format) + format) % format;
}

void L (int *direction, int *i , int *j, const int Height, const int Width)
{
  assert (Height);
  assert (Width);
  if ( Up == *direction)
  { 
    (*i)--;
    Jump(i, Height);
    *direction =  Left ;
  }
  else if ( Down == *direction) 
  {
    (*i)++;
    Jump(i, Height);
    *direction = Right;
  }
  else if ( Left == *direction) 
  {
    (*j)++;
    Jump(j,Width);
    *direction = Down;    
  }
  else if ( Right == *direction) 
  {
    (*j)--;
    Jump(j,Width);
    *direction = Up;
  }
}
void R (int *direction, int *i, int *j, int const Height, int const Width)
{
  assert (Height);
  assert (Width);
  if ( Up == *direction) 
  {
    (*i)++;
    Jump(i, Height);
    *direction = Right;
  }
  else if ( Down == *direction)
  { 
    (*i)--;
    Jump(i, Height);
    *direction = Left;
  }
  else if ( Left == *direction) 
  {
    (*j)--;    
    Jump(j,Width);
    *direction = Up;
  }
  else if ( Right == *direction)
  { 
    (*j)++;
    Jump(j,Width);
    *direction = Down;
  }
}

void Rule (const char *move, const char s, int *direction, int **Matrix, int *i ,int *j, int const Height, int const Width)
{
  assert (Height);
  assert (Width);
  assert(s);
  assert(move);
  assert(Matrix);
  assert(direction);
  if (( 0 == Matrix[*i][*j] ) && ( 'R' == move[0] ))
  {
    Matrix[*i][*j]++;
    if (Matrix[*i][*j] > s)
      Matrix[*i][*j] = 1;
    R(direction, i, j, Height, Width);
  }
  else if (( 1 == Matrix[*i][*j] ) && ('R' == move[1] ))
  {
    Matrix[*i][*j]++;
    if (Matrix[*i][*j] > s)
      Matrix[*i][*j] = 1;    
    R(direction, i, j, Height, Width);
  }
  else if (( 2 == Matrix[*i][*j] ) && ( 'R' == move[2] ))
  {
    Matrix[*i][*j]++;
    if (Matrix[*i][*j] > s)
      Matrix[*i][*j] = 1;
    R(direction, i, j, Height, Width);
  }
  else if (( 3 == Matrix[*i][*j] ) && ( 'R' == move[3] ))
  {
    Matrix[*i][*j]++;
    if (Matrix[*i][*j] > s)
      Matrix[*i][*j] = 1;
    R(direction, i, j, Height, Width);
  }
  else if (( 4 == Matrix[*i][*j] ) && ( 'R' == move[4] ))
  {
    Matrix[*i][*j]++;
    if (Matrix[*i][*j] > s)
      Matrix[*i][*j] = 1;
    R(direction, i, j, Height, Width);
  }
  else if (( 5 == Matrix[*i][*j] ) && ( 'R' == move[5] ))
  {
    Matrix[*i][*j]++;
    if (Matrix[*i][*j] > s)
      Matrix[*i][*j] = 1;
    R(direction, i, j, Height, Width);
  }
  else if (( 6 == Matrix[*i][*j] ) && ( 'R' == move[6] ))
  {
    Matrix[*i][*j]++;
    if (Matrix[*i][*j] > s)
      Matrix[*i][*j] = 1;
    R(direction, i, j, Height, Width);
  }
  else if (( 7 == Matrix[*i][*j] ) && ( 'R' == move[7] ))
  {
    Matrix[*i][*j]++;
    if (Matrix[*i][*j] > s)
      Matrix[*i][*j] = 1;
    R(direction, i, j, Height, Width);
  }
  else if (( 8 == Matrix[*i][*j] ) && ( 'R' == move[8] ))
  {
    Matrix[*i][*j]++;
    if (Matrix[*i][*j] > s)
      Matrix[*i][*j] = 1;
    R(direction, i, j, Height, Width);
  }
  else if (( 9 == Matrix[*i][*j] ) && ( 'R' == move[9] ))
  {
    Matrix[*i][*j]++;
    if (Matrix[*i][*j] > s)
      Matrix[*i][*j] = 1;
    R(direction, i, j, Height, Width);
  }
  else if (( 0 == Matrix[*i][*j] ) && ('L' == move[0]  ))
  {
    Matrix[*i][*j]++;
    if (Matrix[*i][*j] > s)
      Matrix[*i][*j] = 1;
    L(direction, i, j, Height, Width);
  }
  else if (( 1 == Matrix[*i][*j]) && ( 'L' ==  move[1] ))
  {
    Matrix[*i][*j]++;
    if (Matrix[*i][*j] > s)
      Matrix[*i][*j] = 1;
    L(direction, i, j, Height, Width);
  }
  else if (( 2 == Matrix[*i][*j]) && ( 'L' ==  move[2] ))
  {
    Matrix[*i][*j]++;
    if (Matrix[*i][*j] > s)
      Matrix[*i][*j] = 1;
    L(direction, i, j, Height, Width);
  }
  else if (( 3 == Matrix[*i][*j]) && ( 'L' ==  move[3] ))
  {
    Matrix[*i][*j]++;
    if (Matrix[*i][*j] > s)
      Matrix[*i][*j] = 1;
    L(direction, i, j, Height, Width);
  }
  else if (( 4 == Matrix[*i][*j]) && ('L' ==  move[4] ))
  {
    Matrix[*i][*j]++;
    if (Matrix[*i][*j] > s)
      Matrix[*i][*j] = 1;
    L(direction, i, j, Height, Width);
  }
  else if (( 5 == Matrix[*i][*j]) && ('L' ==  move[5] ))
  {
    Matrix[*i][*j]++;
    if (Matrix[*i][*j] > s)
      Matrix[*i][*j] = 1;
    L(direction, i, j, Height, Width);
  }
  else if (( 6 == Matrix[*i][*j]) && ('L' ==  move[6] ))
  {
    Matrix[*i][*j]++;
    if (Matrix[*i][*j] > s)
      Matrix[*i][*j] = 1;
    L(direction, i, j, Height, Width);
  }
  else if (( 7 == Matrix[*i][*j]) && ('L' ==  move[7] ))
  {
    Matrix[*i][*j]++;
    if (Matrix[*i][*j] > s)
      Matrix[*i][*j] = 1;
    L(direction, i, j, Height, Width);
  }
  else if (( 8 == Matrix[*i][*j] ) && ('L' == move[8] ))
  {
    Matrix[*i][*j]++;
    if (Matrix[*i][*j] > s)
      Matrix[*i][*j] = 1;
    L(direction, i, j, Height, Width);
  }
  else if (( 9 == Matrix[*i][*j] ) && ('L' == move[9] ))
  {
    Matrix[*i][*j]++;
    if (Matrix[*i][*j] > s)
      Matrix[*i][*j] = 1;
    L(direction, i, j, Height, Width);
  }
}

int main (int argc, char *argv[])
{
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  int Height = 0;
  int Width = 0;
  int k = 1;/*STEP*/
  char c = 0; /*Step*/
  int s = 0;  // правило
  int i = 0; /* x */
  int j = 0; /* y */
  int w = 0; /*дин. массив*/
  char move[MAX_LINE] = {0}; /*массив правил*/ 
  int direction = Up;
  char str[MAX_LINE] = {0};
  FILE *file = NULL;
  if( NULL == (file = fopen(argv[1], "r"))) 
  {
    printf("Can't open this file\n");
    return -1; 
  }  
  while(!feof(file))
  {
    fgets(str, MAX_LINE, file);
    sscanf(str, "#HW_ %d %d", &Height, &Width);
    fgets(str, MAX_LINE, file);
    sscanf(str, "#XY_ %d %d", &i, &j);
    if((i >= Height ) || (j >= Width))
    {
      printf("ERROR(XY)");
      return -1;
    }
    fgets(str, MAX_LINE, file);
    sscanf(str, "#AntRule_%s", move);
    if(MAX_COLOR < strlen(move) )
    {
      printf("RULE (1- 10)");
      return -1;
    }
  }
  s = strlen(move) - 1;
  fclose(file);
  int **Matrix = (int**)calloc(Height,sizeof(int*));
  for (w = 0; w < Width; w++)
    Matrix[w] = (int*)calloc(Width,sizeof(int)); 
  Field(file, Height, Width, Matrix, &argv[1], move); 
  ShowField(Height, Width, Matrix);
  while((c=getch()) != 27)
  {
    printf("Step %d\n",k++);
    Rule (move, s, &direction, Matrix, &i, &j, Height, Width);
    ClearScreen();
    ShowField(Height, Width, Matrix);
  }
  free(Matrix);
  for (w = 0; w < Width; w++)
    free(Matrix);
  return 0;
}
