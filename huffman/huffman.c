#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"


#define MAX_SIZE 256
#define MAX_BITS 8

static void delete_table(code* table_code)
{
  int i = 0;
 
  for (i = 0; i < MAX_SIZE; i++)
  {
    free(table_code[i].buffer);
  }
  
  free(table_code);
}

void free_all(code* table_code, Tlist* root)
{
  delete_table(table_code);
  delete_tree(root);
}  

void make_codes(Tlist* root, unsigned char* b_code, int count, code* table_code)
{

  if(-1 != root->value) 
  {
    unsigned char* code = (unsigned char*)calloc(count, sizeof(unsigned char));
    table_code[root->value].len = count; 
    
    //connect buffer to slot
    table_code[root->value].buffer = memcpy(code, b_code, count*sizeof(unsigned char));
  
    return;
  }
  
  if(root->rigth) // go right
  {
    b_code[count] = '1';
    make_codes(root->rigth, b_code, count + 1, table_code);
  }

  if(root->left) //go left
  {
    b_code[count] = '0';
    make_codes(root->left, b_code, count + 1, table_code);
  }
}

void decoder(FILE* tree, FILE* source, FILE* out)
{
  unsigned char bit = 0;
  unsigned char c = 0;
  unsigned char shift = 0x1 << 7;
  int i = 0;
  int size = 0;
  int pos = 0;
  
  fscanf(tree,"%d ", &size); // amount of symbols
  fscanf(tree,"%d", &pos); // amount of significant bits 
  
  Tlist* root = read_tree(tree);

  Tlist* cur = root;
  
  #ifdef _DEBUG_

  print_tree_to_stdin(root);
  
  #endif

  while(1 == fscanf(source, "%c", &c))
  {
    if(pos) // finding last symbol
    {
      if(1 == size) // if we have a part of a byte
      {
        for(i = 0; i < pos; i++)
        {
          bit = c & shift;
          c <<= 0x1;
          
          if(!bit) // 0 bit
          {
            cur = cur->left;
            if(-1 != cur->value)
            { 
              fputc(cur->value, out);
              cur = root;
            }
          }
          else
          {
            cur = cur->rigth;
              
            if(-1 != cur->value)
            { 
              fputc(cur->value, out);
              cur = root;
            }
          }
        }
        delete_tree(root);
        return;
      }
    }

    for (i = 0; i < MAX_BITS; i++)  //8 bits
    {
      
      bit = c & shift;  // 01001000     10010000 
      c <<= 0x1;        // &        --> &
                        // 10000000     10000000
      if(!bit)          
      {
        cur = cur->left;
        if(-1 != cur->value)
        { 
          fputc(cur->value, out);
          cur = root;
        }
      }
      else
      {
        cur = cur->rigth;
        
        if(-1 != cur->value)
        { 
          fputc(cur->value, out);
          cur = root;
        }
      }
    }
    size--;
  }
  delete_tree(root);
}



void archiver(FILE* tree, FILE* out, FILE* source, code* table_code, Tlist* root)
{
  unsigned char byte = 0;
  int current_bit = 0;
  int i = 0;
  unsigned char c = 0;
  long long int len = 0;
  long long int count = 0;

  while(1 == (fscanf(source, "%c", &c)))
  {
    unsigned char* temp = table_code[(int)c].buffer;
    len = table_code[(int)c].len;
    
    #ifdef _DEBUG_
    
    printf("%c",c);
    for(i = 0 ; i < len; i++)
      printf(" %c", temp[i]);
    putchar('\n');  
    
    #endif
    
    for(i = 0; i < len; i++)
    {
      byte <<= 0x1; 
      if('1' == temp[i]) 
         byte |= 0x1;
      
      current_bit++;       
      if(current_bit == MAX_BITS)
      {
        fwrite(&byte, sizeof(unsigned char), 1, out);
        count++;
        current_bit = 0;
        byte = 0x0;
      }
    }
  }
  
  if( current_bit > 0 )
  {
    byte <<= 8 - current_bit;
    count++;
    fwrite(&byte, 1, 1, out);
  }
  
  rewind(out);
  fprintf(tree, "%lld ", count);
  fprintf(tree, "%d", current_bit);
  print_tree_to_source(root, tree);

  #ifdef _DEBUG_

  print_tree_to_stdin(root);
  
  #endif

  rewind(tree);
}


