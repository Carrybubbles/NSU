#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "fibo.h"

fheap* init_heap()
{
    fheap* cur = (fheap*)calloc(1,sizeof(fheap));

    cur->min = NULL;
    cur->num_nodes = 0;

    return cur;
}
fheap_node* init_heap_node(int value,int number)
{
    fheap_node* node = (fheap_node*)calloc(1,sizeof(fheap_node));

    node->parent = NULL;
    node->left = node;
    node->right = node;
    node->number = number;
    node->child = NULL;
    node->degree = 0;
    node->marked = 0;
    node->value = value;

    return node;
}


void insert(fheap* cur,int key,int number)
{
    fheap_node* NewNode = init_heap_node(key,number);
    
    assert(NewNode);

    if(cur->min != NULL )
    {
	cur->min->right->left = NewNode;  // insert into heap list
	NewNode->right = cur->min->right;	
	cur->min->right = NewNode;
	NewNode->left = cur->min;
	
	if(cur->min->value > NewNode->value)
	{
	    cur->min = NewNode;
	}
    }
    else
    {
	cur->min = NewNode;
    }
    cur->num_nodes++;

}

/*fheap* union_heaps(fheap* cur, fheap* other)
{
	fheap_node* other_left = NULL;

	if(NULL == other->min)
		return cur;
	
	if(NULL == cur->min)
	{	
		cur->min = other->min;
		return cur;
	}

	other_left = other->min->left;
	other->min->left = cur->min->left;
	cur->min->left = other_left;
	cur->min->left->right = cur->min;
	other->min->left->right = other->min;

	if(other->min->value < cur->min->value)
		cur->min = other->min;
	
	cur->num_nodes += other->num_nodes;
	
	return cur;
}
*/
static void link(fheap* cur,fheap_node* y , fheap_node* x)
{
    y->left->right = y->right;  //remove form heap list
    y->right->left = y->left;

    
    if(NULL == x->child)
    {
	x->child = y; // if alone 
	y->right = y; 
	y->left = y;
    }	
    else
    {
	y->left = x->child;   // connect into child list 
	 y->right = x->child->right;
	x->child->right = y;
	y->right->left = y;
    }
    y->parent = x;
    
    x->degree++;
    y->marked = 0;
}

static void consolidate(fheap* cur)
{
    fheap_node** list = (fheap_node**)calloc(cur->num_nodes + 1,sizeof(fheap_node*));
    fheap_node* y = NULL;
    fheap_node* x = cur->min;
    
    int d = 0;
    int i = 0;
    int num_roots = 0;

    for(i = 0; i < cur->num_nodes + 1; i++)
	    list[i] = NULL;
    if (x != NULL) // count a amount of roots
    {
	num_roots++;
	x = x->right;
	while(x != cur->min)
	{
	    num_roots++;
	    x = x->right;
	}
    }

    while(num_roots > 0)
    {
	d = x->degree;
	fheap_node* next = x->right; // for every root

	for(;;)
	{
	    y = list[d];
	    if( y == NULL)
		break;
	    if(x->value > y->value)
	    {
		fheap_node* temp = y; //swap
		y = x;
		x = temp;
	    }
	    link(cur,y,x); //make y child a child of x  
	    list[d] = NULL;
	    d++;
	}
	
	list[d] = x;
	x = next;
	num_roots--;
    }	
    
    cur->min = NULL;

    for(i = 0 ; i < cur->num_nodes + 1;i++)
    {
	fheap_node* y = list[i];
	if( y == NULL)
	    continue;
	
	if( cur->min != NULL)
	{
	    y->left->right = y->right; //remove
	    y->right->left = y->left;
		
	    y->left = cur->min; // add to list 
	    y->right = cur->min->right;
	    cur->min->right = y;
	    y->right->left = y;
	
	    if(y->value < cur->min->value)
	    {
		cur->min = y;
	    }
	}
	else
	{
	    cur->min = y;
	}
    }
    free(list);
}

fheap_node* remove_min(fheap* cur)
{
    fheap_node* z = cur->min;
    fheap_node* x = NULL;
    fheap_node* temp = NULL;

    if(z->child != NULL)
    {
	x = z->child;
	temp = x;
	while(temp != x)
	{ 	
	    temp->parent = NULL;
	    temp = temp->right;
	}
	cur->min->left->right = x->right; //add children to heap list 
	x->right->left = cur->min->left;
	cur->min->left = x;
	x->right = cur->min;
    }

    z->left->right = z->right; //remove z from heap list
    z->right->left = z->left;

    if(z == z->right) // chech if heap not empty
    {
	cur->min = NULL;
    }
    else
    {
	cur->min = z->right;
	consolidate(cur);
    }
    cur->num_nodes--;

    return z;
}

fheap_node* get_min(fheap* root)
{
    return root->min;
}

static void cut(fheap* cur, fheap_node* x, fheap_node* y)
{
    if(x->right == x)
    {
	y->child = NULL;
    }
    else
    {
	y->child = x->right;
    }

    x->left->right = x->right; // remove 
    x->right->left = x->left;

    y->degree--; 
	
    cur->min->right->left = x; //add x to heap list
    x->right = cur->min->right;
    cur->min->right = x;
    x->left = cur->min;


    x->parent = NULL;
    x->marked = 0;
}

static void Cascading_cut(fheap* cur,fheap_node* y)
{
    fheap_node* z = y->parent;
    
    if(z != NULL)
    {
	if(y->marked == 0)
	{
	    y->marked = 1;
	}
	else
	{
	    cut(cur,y,z);
	    Cascading_cut(cur,z);
	}
    }
}

void Decrease_key(fheap* cur,fheap_node* x,int newValue)
{
    fheap_node* y = x->parent;
    
    if(y != NULL && y->value > x->value)
    {
	cut(cur,x,y);
	Cascading_cut(cur,y);
    }

    if(x->value < cur->min->value)
    {
	cur->min = x;
    }
}

void Delete_node(fheap* cur,fheap_node* x)
{
    Decrease_key(cur,x,-1000);
    fheap_node* temp = remove_min(cur);
    free(temp);
}

void Delete_heap (fheap* cur)
{
    while(NULL != get_min(cur))
    {
	Delete_node(cur, cur->min);  
    }
    
    free(cur);
}


