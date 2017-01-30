#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

#define MAX_SIZE 256

Tlist* init_Tlist()
{
  Tlist* root = (Tlist*)calloc(1, sizeof(Tlist));

  root->value = -1;
  root->freq = 0;
  root->left = NULL;
  root->rigth = NULL;

  return root;
}

void delete_tree(Tlist* root)
{
  if(!root) 
    return;

  if(root->left)
    delete_tree(root->left);
  if(root->rigth)
    delete_tree(root->rigth);

  free(root);
}
  
static int compare_freq(const void* a, const void* b)
{
  return (*(Tlist**)a)->freq < (*(Tlist**)b)->freq;
}

static int compare(const void* a, const void* b)
{
  return *(int*)a < *(int*)b;
}

static Tlist* build_tree(Tlist* leaves[MAX_SIZE], int len)
{

  if(1 == len) // if we have 1 symbol
  {
    int i = 0;
    
    while(1)
    {
      if(leaves[i])
        break;
      i++;
    }

    Tlist* root = init_Tlist();
    Tlist* cur = init_Tlist();
    
    cur->value = i;
    root->rigth = cur;

    free(leaves[i]);
    
    return root;
  }
  else
  {
    // sorting in decreasing order
    qsort(leaves, MAX_SIZE, sizeof(*leaves), compare); 
    
    while(1 < len)
    {
      // sort in decreasing order
      qsort(leaves, len, sizeof(*leaves), compare_freq);
      Tlist* cur = init_Tlist();
      cur->rigth = leaves[len-2];
      cur->left = leaves[len-1];
      cur->freq = leaves[len-1]->freq + leaves[len-2]->freq;
      
      leaves[len-2] = cur;

      len--;
    }
    
    return leaves[0];
  }
}

void print_tree_to_source(Tlist* root, FILE* out)
{
  if (!root) 
  {
    fprintf(out, "#");// if end
    return;
  }

  fprintf(out, "[");  

  if(-1 != root->value)
    fprintf(out, "!%c", root->value); // if symbol 
  else
    fprintf(out, "%c", root->value); // if node
  
  print_tree_to_source(root->left, out);
  print_tree_to_source(root->rigth, out);
  
  fprintf(out, "]");  

}

void print_tree_to_stdin(Tlist* root)
{
  
  if (!root) 
  {
    printf("#");
    return;
  }

  printf("[");  

  printf("%c", root->value);
  
  print_tree_to_stdin(root->left);
  print_tree_to_stdin(root->rigth);

  printf("]");  
  
}

Tlist* read_tree(FILE* source)
{
  unsigned char c = 0;
  
  Tlist* root = NULL;
  c = fgetc(source);
  
  if('#'== c)
  {
    return NULL;
  }
  
  c = fgetc(source); // '['
  
  if('!' == c) // if we have symbol 
  {
    c = fgetc(source);
    root = init_Tlist();
    root->value = c;
  }
  else
  {
    root = init_Tlist(); // if node
  }

  root->left = read_tree(source);
  root->rigth = read_tree(source);
  
  c = fgetc(source); // ']'
  
  return root;
}

Tlist* make_huf_tree(FILE* tree, FILE* source)
{

  Tlist* leaves[MAX_SIZE];
  int i = 0;
  for(i = 0; i < MAX_SIZE; i++)
    leaves[i] = NULL;

  int len = 0;
  unsigned char c = 0;

  while(1 == (fscanf(source, "%c", &c)))
  {
    if (!leaves[(int)c])
    {
      leaves[(int)c] = init_Tlist();
      leaves[(int)c]->value = c;
      leaves[(int)c]->left = NULL;
      leaves[(int)c]->rigth = NULL;
      len++;
    }

    leaves[(int)c]->freq++;
  }
  
  Tlist* root = build_tree(leaves, len);

  rewind(source);
  
  return root;
}
