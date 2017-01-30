#ifndef FIBO
#define FIBO

typedef struct fheap_node {
    struct fheap_node* parent;
    struct fheap_node* left ;
    struct fheap_node* right;
    struct fheap_node* child;
    int degree; // number of children
    int marked; //is True if the node has lost a child since the node became a child of another node. 
    int value; 
    int number; // number of vertex
}fheap_node;


typedef struct fheap{
    struct fheap_node* min;
    int num_nodes;
}fheap;

void insert(fheap* cur,int value,int number);
fheap_node* remove_min(fheap* cur);
fheap_node* get_min(fheap* root);
void Decrease_key(fheap* cur,fheap_node* e,int newValue);
void Delete_node(fheap* cur,fheap_node* x);
fheap* init_heap();
void Delete_heap (fheap* cur);


#endif