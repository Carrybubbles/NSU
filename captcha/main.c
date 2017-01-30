#include <stdio.h>
#include <stdlib.h>
#include "net.h"
#include "image.h"

#define MAXTEST 631
#define IMAGESIZE 21*27
#define MAXNUM 10
#define MAXNUMCAP 6
#define MAXROW 27
#define MAXCOL 21

void print( int** matrix, int row, int col)
{
  int i = 0;
  for(i = 0; i < row; i++)
  {
    int j = 0;
    for(j = 0 ; j < col; j++)
    {
      printf("%d", matrix[i][j]);
    }
    putchar('\n');
  } 
}

void loadBar(int x, int n, int r, int w)
{
  if ( x % (n/r) != 0 ) 
    return;
  float ratio = x /(float)n;
  int c = ratio * w;

  printf("\033[32mTraining\033[0m\033[J");
  printf("\033[32m%3d%%\033[0m \033[32m[\033[0m", (int)(ratio*100) );

  for( x = 0; x < c; x++)
    printf("\033[33m=\033[0m");

  for( x = c; x < w; x++)
    printf(" ");
  printf("\033[32m]\033[0m\n\033[F\033[J");
}

int main(int argc, char** argv)
{
  int training = 0;
  printf("Wellcome! If you want to train NNet print 0 else print another number ");
  scanf("%d", &training);
  
  NNet* net = NULL;
  if(!training)
  {
    FILE* file = fopen("train.txt","r");
    if(file == NULL)
    {
      printf("Cant open trainset!\n");
      return 1;
    } 
    list* Tlist = (list*)calloc(1 , sizeof(list));
    load_data_to_list(Tlist, file, MAXTEST);
    
    net = init_net(IMAGESIZE, MAXNUM);
    int j = 0;
    for(j = 0 ; j < 10; j++)
    { 
      printf("Stage %d\n of 10", j);
      int k = 0;
      for(k = 0; k < Tlist->len; k++)
      {
        int Row = Tlist->Aimg[k]->rows;
        int Col = Tlist->Aimg[k]->cols;
        int* temp = train(net, Tlist->Aimg[k]->data, Row, Col, Tlist->target[k], 1);
        loadBar(k, Tlist->len , 50, 50);
        free(temp);
      }
      int i = 0;
      for( i = 0; i < 50000 * Tlist->len; i++)
      {
        int n = RandomINT(0, MAXTEST - 1);
        int Row = Tlist->Aimg[n]->rows;
        int Col = Tlist->Aimg[n]->cols;
        int* temp = train(net, Tlist->Aimg[n]->data, Row, Col, Tlist->target[n], 1);
        loadBar(i, 50000 * Tlist->len , 50, 50);
        free(temp);
      }
    }
    printf("Training finished!Weights were save in file(saмe.txt)");
    save(net);
    free_list(Tlist,MAXTEST);
    fclose(file);
  }
  else
  {
    FILE* weig = fopen("save.txt","r");
    if(weig == NULL)
    {
      printf("Cant open weights!\n");
      return 1;
    } 
    net = load_net(weig);
    printf("Enter file name from: ");
    char captcha[256] = {0};
    scanf("%s", captcha);
  
    list* Ilist = cut_captcha(MAXNUMCAP, captcha);
    if(Ilist == NULL)
    {
      printf("Cant open captcha!\n");
      return 1;
    }
    int Row = MAXROW;
    int Col = MAXCOL;
    int i = 0;
    for( i = 0 ; i < MAXNUMCAP; i++)
    {
      int* in = train(net,Ilist->Aimg[i]->data, Row, Col, 0, 0);
      printf("%d",recognizeCap(in, MAXNUM));
      free(in);    
    }
    free_list(Ilist,0);
  } 
  putchar('\n');
  NnetDestroy(net);
}