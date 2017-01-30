#ifndef _NET_
#define _NET_
typedef struct {       
  int nNeur;         
  double* Activation;    
  int* Output;        
  double* Error;
  double** Weight;        
} layer;

typedef struct {                     
  layer* InputLayer;    
  layer* OutputLayer;   
} NNet;

NNet* init_net(int nInput, int nOutput);
void feedForward(NNet* net);
void save(NNet* net);
NNet* load_net(FILE* file);
void SetInput(NNet* net, int** input, int rows, int cols);
int* GetOutput(NNet* net);
int* train(NNet* net, int** input, int Row, int Col, int* target, int training);
void NnetDestroy(NNet* net);
int recognizeCap(int* input, int size);
double RandomINT(int Low, int High);

#endif