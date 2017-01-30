#ifndef _HUFFMAN_
#define _HUFFMAN_

#include "tree.h"

typedef struct table{
  int len;
  unsigned char* buffer;
} code;

void free_all(code* table_code, Tlist* root);
void make_codes(Tlist* root, unsigned char* b_code, int count, code* table_code);
void decoder(FILE* tree, FILE* source, FILE* out);
void archiver(FILE* tree, FILE* out, FILE* source, code* table_code, Tlist* root);

#endif