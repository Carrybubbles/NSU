#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "image.h"

#define MAXCOLS 21
#define MAXROWS 27
#define PNG_EXTENSION 4
#define MAX_NUM 10

static int** initTarmatrix(void)
{
  int i = 0;
  int** matrix = (int**)calloc(MAX_NUM, sizeof(int*));
  for( i = 0 ; i < MAX_NUM; i++)
  {  
    matrix[i] = (int*)calloc(MAX_NUM, sizeof(int));
  }
  int j = 0;
  for( i = 0 ; i < MAX_NUM; i++)
  {
    for(j = 0 ; j < MAX_NUM ;j++)
    {
      matrix[i][j] = -1;
    }
  }
  for( i = 0, j = 0; i < MAX_NUM; i++, j++)
  {
    matrix[i][j] = 1;
  }
  return matrix;
}

static void free_matrix(int** matrix, int Row)
{
  int i = 0;
  for(i = 0 ; i < Row; i++)
    free(matrix[i]);
  free(matrix);
}

static int** init_MatrixI(int Row, int Col)
{
  int** matrix = (int**)calloc(Row, sizeof(int*));
  int i = 0; 
  for(i = 0; i < Row; i++)
  {
    matrix[i] = (int*)calloc(Col, sizeof(int));
  }
  return matrix;
}

image* create_img(int Rn, int Cn, char* name)
{
  image* Inew = (image*)calloc(1 , sizeof(image));
  
  if(NULL == Inew)
  {
    printf("Cant create Image\n");
    return NULL;
  }
  
  int len = strlen(name);
  char* Bufname = (char*)calloc(len + 1, sizeof(char));
  
  Inew->cols = Cn;
  Inew->rows = Rn;
  
  Inew->data = init_MatrixI(Rn, Cn);
  Inew->name = memcpy(Bufname, name, sizeof(char) * (len + 1));
  return Inew;
} 

void free_img(image* img)
{
  free_matrix(img->data,img->rows);
  free(img->name);
  free(img);
}

static int** load_data(FILE* file)
{
  int i = 0;
  int** matrix = init_MatrixI(MAXROWS, MAXCOLS);
  for(i = 0; i < MAXROWS; i++)
  {
    int j = 0;
    for(j = 0; j < MAXCOLS + 1; j++)
    {
      char c = fgetc(file);
      if(c == '\n')
      {
        continue;
      }
      matrix[i][j] = c - '0';
    }
  }
  return matrix;
} 

image* img_open(char* filename)
{
  FILE* file = fopen(filename, "rb");
  if(NULL == file)
  {
    printf("Cant open file\n");
    return NULL;
  }
  
  int type = 0;
  fscanf(file, "P%d", &type);  
  if (5 != type)
  {
    printf("It doesnt PGM format of image\n");
    return NULL;
  }
  int Rn = 0;
  int Cn = 0;
  fscanf(file,"%d", &Cn);
  fscanf(file,"%d", &Rn);
  image* picture = create_img(Rn, Cn, filename);
  
  int maxval = 0;
  fscanf(file, "%d", &maxval);
  fgetc(file);
  if (maxval > 255)
  {
    printf("Error!Cant support this val, only 8 bit\n");
    free_img(picture);
    return NULL;
  }
  int i = 0;
  for(i = 0 ; i < Rn; i++)
  {
    int j = 0;
    for(j = 0; j < Cn; j++)
    {
      int c = fgetc(file);
      if(c > 128)
        picture->data[i][j] = 0;
      else
        picture->data[i][j] = 1;
    }
  }
  
  fclose(file);
  return picture;
} 

image* recognize_horiz(image* img, int* curCol)
{
  int Rn = img->rows;
  int Cn = img->cols;
  int pos1 = 0;
  int pos2 = 0;
  int sum = 0;
  int i = 0;
  int count1 = 0;
  int count2 = 0;
  int j = 0; 
  for(i = *curCol; i < Cn; i++)
  {
    for(j = 0; j < Rn; j++)
    {
      int value = img->data[j][i];
      sum += value;
      if(1 == value && !count1)
      {
        pos1 = i;
        count1++; 
      }
    }
    if(!sum && count1 && !count2)
    {
      pos2 = i;
      count2++;
    }
    sum = 0;
  }
  *curCol = pos2;

  int** matrix = init_MatrixI(Rn, pos2 - pos1);
  for(i = 0; i < pos2 - pos1; i++)
  {
    for(j = 0; j < Rn; j++)
    {
       matrix[j][i]= img->data[j][i+pos1];
    }
  }
  image* poly = create_img(Rn, pos2-pos1, "poly");
  free_matrix(poly->data,poly->rows);
  
  poly->data = matrix;
  
  return poly;
}
image* recognize_upright(image* img)
{
  int Rn = img->rows;
  int Cn = img->cols;
  int pos1 = 0;
  int pos2 = 0;
  int sum = 0;
  int i = 0;
  int count1 = 0;
  int count2 = 0;
  int j = 0; 
  for(i = 0; i < Rn; i++)
  {
    for(j = 0; j < Cn; j++)
    {
      int value = img->data[i][j];
      sum += value;
      if(1 == value && !count1)
      {
        pos1 = i;
        count1++; 
      }
    }
    if(!sum && count1 && !count2)
    {
      pos2 = i;
      count2++;
    }
    sum = 0;
  }
  int** matrix = init_MatrixI(pos2 - pos1, Cn);
  for(i = 0; i < Cn; i++)
  {
    for(j = 0; j < pos2 - pos1; j++)
    {
       matrix[j][i]= img->data[j+pos1][i];
    }
  }
  free_img(img);
  image* poly = create_img(pos2-pos1, Cn, "poly");
  free_matrix(poly->data,poly->rows);
  
  poly->data = matrix;
  
  return poly;
}

list* create_imgL(void)
{
  list* Nimg = (list*)calloc(1 , sizeof(list));
  Nimg->len = 0;
  Nimg->Aimg = NULL;
  return Nimg;
}

void free_list(list* Ilist, int size)
{
  int len = Ilist->len;
  int i = 0;
  for( i = 0; i < len; i++)
  {
    free_img(Ilist->Aimg[i]);
  }
  free_matrix(Ilist->target, size);
  free(Ilist->Aimg);
  free(Ilist);
  return;
}

void add_imgL(list* Ilist, image* img)
{
  int n = Ilist->len;
  
  if(0 == n)
  {
    Ilist->Aimg = (image**)calloc(1, sizeof(image*));
  }
  else
  {
    Ilist->Aimg = (image**)realloc(Ilist->Aimg, (n+1)*sizeof(image*));
  }
  
  if (Ilist->Aimg == NULL) 
  {
    printf("Couldn't reallocate image list\n");
  }
  
  Ilist->Aimg[n] = img;
  Ilist->len = n + 1;
}

void load_data_to_list(list* Ilist, FILE* file, int size)
{
  int i = 0;
  char c = 0;
  Ilist->target = (int**)calloc(size, sizeof(int*));
  int** temp = initTarmatrix();
                                                        
  for(i = 0 ; i < size; i++)
  {
    image* Inew = (image*)calloc(1, sizeof(image));
    Inew->rows = MAXROWS;
    Inew->cols = MAXCOLS;
    Inew->data = load_data(file);
    c = fgetc(file);    
    Inew->name = calloc(2, sizeof(char));
    Inew->name[0] = c;
    
    int* tar = (int*)calloc(MAX_NUM, sizeof(int)); // special symbols for recognition
    memcpy(tar, temp[c - '0'], sizeof(int)*MAX_NUM);
    Ilist->target[i] = tar;
    
    fgetc(file);
    
    add_imgL(Ilist, Inew);
  }
  free_matrix(temp, MAX_NUM);
}

void realloc_num(image* img)
{
  int Rn = img->rows;
  int Cn = img->cols;
  int i = 0;
  int** matrix = init_MatrixI(Rn, MAXCOLS);
  for(i = 0 ; i < Rn; i++)
  {
    int j = 0;
    for( j = 0; j < Cn; j++)
    {
      matrix[i][j] = img->data[i][j];
    }
  }
  img->cols = MAXCOLS;
  free_matrix(img->data,img->rows);
  img->data = matrix;
}

list* cut_captcha(int num_of_char, char* filename)
{
  int a = 1;
  int* cur = &a;
  int len = strlen(filename);
  char* buf_pgm = (char*)calloc(len+1, sizeof(char));
  
  int i = 0;
  for(i = 0; i < len - PNG_EXTENSION; i++)
  {
    buf_pgm[i] = filename[i];
  } 
  
  char* system_buf = (char*)calloc(10 + 2*len, sizeof(char));
  strcat(system_buf, "convert ");
  strcat(system_buf, filename);
  strcat(system_buf," ");
  strcat(system_buf, buf_pgm);
  strcat(system_buf,".pgm\0");
  system(system_buf);    
  free(system_buf);
  strcat(buf_pgm,".pgm\0");
  image* img = NULL;
  if (NULL == (img = img_open(buf_pgm)))
    return NULL;
  list* Ilist = create_imgL();
  for(i = 0; i < num_of_char; i++)
  {
    image* temp = recognize_horiz(img, cur);
    image* ch = recognize_upright(temp);  
    add_imgL(Ilist, ch);
  }
  free_img(img);
  for(i = 0 ; i < Ilist->len;i++)
  {
    if(Ilist->Aimg[i]->cols < 21)
      realloc_num(Ilist->Aimg[i]);

  }
  //realloc_num(Ilist->Aimg[4]);
  free(buf_pgm);
  
  return Ilist;
}
