#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>  
#include "image.h"
#include "net.h"

#define BIAS  1
#define LRATE 0.001
#define MAX(x,y) ((x)>(y) ? (x) : (y))
#define IMAGESIZE 21*27
#define MAXNUM 10
//Activation function
static double activFunc(double x) 
{
  if(x >= 0)
    return 1;
  else 
    return 0;
}

double RandomINT(int Low, int High)
{
  return rand() % (High-Low+1) + Low;
}

static double RandomDouble(double Low, double High)
{
  return ((double) rand() / RAND_MAX) * (High-Low) + Low; 
}
static void randomize_2D_array(double** Matrix, int Height, int Width)
{
  int i = 0;
  srand(4711);
  for(i = 0; i < Height; i++)
  {
    int j = 0;
    for(j = 0; j < Width; j++)
    {
      Matrix[i][j] = RandomDouble(-0.5, 0.5);
    }
  }
}

static double** init_2D_Matrix(int Height, int Width)
{
  double** Mnew = (double**)calloc(Height, sizeof(double*));
  
  if(NULL == Mnew)
  {
    printf("Cant create 2D matrix\n");
    return NULL;
  }
  
  int i = 0;
  for(i = 0 ; i < Height; i++)
    Mnew[i] = (double*)calloc(Width, sizeof(double));
  return Mnew;
}

NNet* init_net(int nInput, int nOutput)
{
  NNet* Net = (NNet*)calloc(1 ,sizeof(NNet));  

  Net->InputLayer = (layer*)calloc(1, sizeof(layer));
  Net->InputLayer->nNeur = nInput;
  Net->InputLayer->Output = (int*)calloc(nInput + 1, sizeof(int));
  Net->InputLayer->Output[0] = BIAS;

  Net->OutputLayer = (layer*)calloc(1, sizeof(layer));
  Net->OutputLayer->nNeur = nOutput;
  Net->OutputLayer->Activation = (double*)calloc(nOutput + 1, sizeof(double));
  Net->OutputLayer->Output = (int*)calloc(nOutput + 1, sizeof(int));
  Net->OutputLayer->Error = (double*)calloc(nOutput + 1, sizeof(double));
  Net->OutputLayer->Weight = init_2D_Matrix(nOutput + 1, nInput + 1);
  randomize_2D_array(Net->OutputLayer->Weight, nOutput + 1, nInput + 1);
  
  return Net;
}

void feedForward(NNet* net)
{
  int i = 0;
  double sum = 0;
  for(i = 1; i <= net->OutputLayer->nNeur; i++)
  {
    int j = 0;
    for(j = 0; j <= net->InputLayer->nNeur; j++)
    {
      sum += net->OutputLayer->Weight[i][j] * net->InputLayer->Output[j];
    }
    net->OutputLayer->Activation[i] = sum;
    net->OutputLayer->Output[i] = activFunc(sum);
  }
}

static void ComputeOutputError(NNet* net, int* target)
{
  double Err = 0;
  int i = 0;
  for (i = 1; i <= net->OutputLayer->nNeur; i++) 
  {
    Err = target[i-1] - net->OutputLayer->Activation[i];
    net->OutputLayer->Error[i] = Err;
  }
}

static void AdjustWeights(NNet* net)
{
  int i = 0;
  for (i = 1; i <= net->OutputLayer->nNeur; i++) 
  {
    int j = 0;
    for (j = 0; j <= net->InputLayer->nNeur; j++) 
    {
      net->OutputLayer->Weight[i][j] += LRATE * net->OutputLayer->Error[i] * net->InputLayer->Output[j];
    }
  }
}

void save(NNet* net)
{
  FILE* file = fopen("save.txt", "w");
  int i = 0;
  for (i = 1; i <= MAXNUM; i++) 
  {
    int j = 0;
    for (j = 0; j <= IMAGESIZE ; j++) 
    {
      fprintf(file,"%lf ",net->OutputLayer->Weight[i][j]);
    }
  }
  fclose(file);
}

NNet* load_net(FILE* file)
{
  double val = 0;
  NNet* net = init_net(IMAGESIZE, MAXNUM);
  int i = 0;
  for (i = 1; i <= MAXNUM; i++) 
  {
    int j = 0;
    for (j = 0; j <= IMAGESIZE ; j++) 
    {
      fscanf(file,"%lf ",&val);
      net->OutputLayer->Weight[i][j] = val;
    }
  }
  fclose(file);
  return net;
}
void SetInput(NNet* net, int** input, int rows, int cols)
{
  int i = 0;
  for(i = 0; i < rows; i++)
  {
    int j = 0;
    for(j = 0; j < cols; j++)
    {
      net->InputLayer->Output[j+cols*i] = input[i][j];
    }
  }
}

int* GetOutput(NNet* net)
{
  int i = 0;
  int* out = (int*)calloc(net->OutputLayer->nNeur, sizeof(int));
  
  for(i = 1; i <= net->OutputLayer->nNeur; i++) 
  {
    out[i-1] = net->OutputLayer->Output[i];
  }
  
  return out;
}

int* train(NNet* net, int** input, int Row, int Col, int* target, int training)
{
  SetInput(net, input, Row, Col);
  
  feedForward(net);
  
  if(training)
  {  
    ComputeOutputError(net, target);
    AdjustWeights(net);
  }
  return GetOutput(net);
}


static void MatDestroy(double** matrix, int Height)
{
  int i = 0;
  for(i = 0 ; i < Height; i++)
    free(matrix[i]);
  free(matrix);
}

void NnetDestroy(NNet* net)
{
  MatDestroy(net->OutputLayer->Weight,net->OutputLayer->nNeur + 1);
  free(net->InputLayer->Output);
  free(net->InputLayer);
  free(net->OutputLayer->Activation);
  free(net->OutputLayer->Output);
  free(net->OutputLayer->Error);
  free(net->OutputLayer);
  free(net);
}

int recognizeCap(int* input, int size)
{
  int i = 0;
  int winner = 0;
  int count = 0;
  for( i = 0 ; i < size; i++)
  {
    if(input[i] > winner)
    {
      winner = i;
      count++;
    }
  }
  if (1 == count)
    return winner;
  else
    return -1;
}


