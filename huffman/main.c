#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "huffman.h"

#define MAX_SIZE 256

int main(int argc, char *argv[])
{
  char option = 0;
  int command = -1;
  char buffer_file[MAX_SIZE] = {0};
  char buffer_key[MAX_SIZE] = {0};
  printf("Hello! Welcome to the Huffman archiver! Type 'e' to encode, 'd' to decode, 'h' to show options\n");
  scanf("%c", &option);

  switch(option)
  {
    case 'e':
      command = 0;  
      break;
    case 'h':
      printf("'e' to encode, 'd' to decode\n");
      return 0;
    case 'd':
      command = 1;
      break;
    default:
      printf("'e' to encode, 'd' to decode\n");
      return 0;  
  }
  
  if(!command)
  {
    printf("Enter source-file: ");
    scanf("%s", buffer_file);

    FILE* source = fopen(buffer_file, "rb");
    
    if(!source)
    {
      printf("Cant find file!");
      return 1;
    }
    
    FILE* dec = fopen("dec.haf", "wb");
    if(!dec)
    {
      printf("Cant create dec file!");
      fclose(source);
    }
    
    FILE* tree = fopen("key.txt", "w");
    if(!tree)
    {
      printf("Cant create key-file");
      fclose(dec);
      fclose(source);
    }
   
    unsigned char* buffer = (unsigned char*)calloc(MAX_SIZE, sizeof(unsigned char));
    code* table_code = (code*)calloc(MAX_SIZE, sizeof(code));
 
    Tlist* root = make_huf_tree(tree, source); 
    make_codes(root, buffer, 0, table_code);
  
    archiver(tree ,dec, source, table_code, root);
    printf("Your file completely decoded! We saved it in dec.haf and created a key-file (key.txt). Handle key with care and dont show to anyone!\n");

    free_all(table_code, root);

    fclose(source);
    fclose(dec);
    fclose(tree);
    free(buffer);
  }
  else if(command)
  {
    printf("Enter source-file: ");
    scanf("%s", buffer_file);
    printf("Enter key-file: ");
    scanf("%s", buffer_key);
    
    FILE* source = fopen(buffer_file, "rb");
    if(!source)
    {
      printf("Cant find source-file!\n");
      return 1;
    }
    
    FILE* tree = fopen(buffer_key, "r");
    if(!tree)
    {
      printf("Cant find key-file!\n");
      fclose(source);
      return 1;
    }
    
    FILE* out = fopen("enc.haf", "wb");
    if(!out)
    {
      printf("Cant create out file!");
      fclose(source);
      fclose(tree);
      return 1;
    }
    
    decoder(tree, source, out);
    printf("Your file completely encoded! We saved it in enc.haf\n");
    
    fclose(tree);
    fclose(source);
    fclose(out);
  }
}
