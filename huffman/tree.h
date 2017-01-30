#ifndef _TREE_
#define _TREE_

typedef struct node{
  int value;
  long long int freq;
  struct node* left;
  struct node* rigth;
} Tlist;

Tlist* init_Tlist();
Tlist* read_tree(FILE* source);
Tlist* make_huf_tree(FILE* tree, FILE* source);
void print_tree_to_stdin(Tlist* root);
void print_tree_to_source(Tlist* root, FILE* out);
void delete_tree(Tlist* root);


#endif