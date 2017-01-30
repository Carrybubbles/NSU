#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "lib_graf.h"
#include "lib_dyn.h"
#include "fibo.h" 

#define MAP
#define MAX_Y 14
#define INFINITY 10000
#define BLOCK 100

static struct vertex* init_vertex(const int vertex)
{
  struct vertex* head = (struct vertex*)calloc(1, sizeof(struct vertex));
  
  head->id = vertex;
  head->visited = 0;
  head->x = 0;
  head->y = 0;
  head->block = 0;
  head->next = NULL;
  head->neighbours = init_array(1);
  head->neighbours_weight = init_array(1);
  
  return head;
}

static struct vertex* find_vertex(struct vertex* graf, const int id_of_vertex)  
{
  if(NULL != graf)
  {   
    while(NULL != graf)
    {
      if(id_of_vertex == graf->id)
      {
        return graf;
      }
        else
      {
        graf = graf->next;
      }
    }
  }
  else if(NULL == graf)
  {
    return NULL;
  }

  return NULL; 
} 

static void make_location(struct vertex* graf)
{
  struct vertex* cur = graf;
  int i = 0;
  int j = 0;

  while(NULL != cur)
  {
    cur->x = i++;
    cur->y = j;

    if(MAX_Y == i)
    {
      i = 0;
      j++;
    }

    cur = cur->next;
  }
}

static struct vertex* insert_sorted(struct vertex **head, struct vertex *file)
{
  struct vertex* p = *head;
  struct vertex* k = (*head)->next;
  
  //вставить перед головой
  if(file->id < (*head)->id) 
  {
    file->next = *head;
    *head = file;
    return *head ;
  }
  
  //вставка элемента в найденную позицию
  while(NULL != k && k->id < file->id) 
  {
    k = k->next;
    p = p->next;
  }
  
  p->next = file;
  file->next = k;
  return *head ;
}

static void make_edge(struct vertex** B, struct vertex** A, const int weight)
{
  int i = 0;
  
  assert(A);
  assert(B);
  
  if ((*A)->neighbours.real_size == 0)
  {
    (*A)->neighbours = add((*A)->neighbours,(*B)->id);
    (*A)->neighbours_weight = add((*A)->neighbours_weight,weight);
  }
  else
  { 
    for( i = 0; i < (*A)->neighbours.real_size;i++)
    {
      if((*A)->neighbours.buffer[i] == (*B)->id)
        return;
      else if( i  == (*A)->neighbours.real_size - 1)
      {       
        (*A)->neighbours = add((*A)->neighbours,(*B)->id);
        (*A)->neighbours_weight = add((*A)->neighbours_weight,weight);
      }
    }
  }
  return;
}

void delete(struct vertex* graf)
{
  assert(graf);

  struct vertex* cur = graf;
  
  while(NULL != graf)
  {
    cur = graf->next;
    free(graf->neighbours.buffer);
    free(graf->neighbours_weight.buffer);
    free(graf);
    graf = cur;
  }
  
  free(graf);

  return;
}



static struct vertex* add_vertex(struct vertex* graf,  int const vertex1, int const vertex2, int const weight)
{
  struct vertex* head1 = find_vertex(graf, vertex1);
  struct vertex* head2 = find_vertex(graf, vertex2);

  if(vertex1 == vertex2 && head1 == NULL && head2 == NULL) //if vertex is alone and point to itself
  {
    
    head1 = init_vertex(vertex1);

    if(graf == NULL)
      graf = head1;
    else
      insert_sorted(&graf, head1);
  }       
  else  
  { 
      
    if(NULL == head1)
    {
      head1 = init_vertex(vertex1);
  
      if(graf == NULL)
        graf = head1;
      else
        insert_sorted(&graf,head1);
    }

    if (NULL == head2)
    {
      head2 = init_vertex(vertex2);
    
      if(graf == NULL)
        graf = head2;
      else
        insert_sorted(&graf, head2);
    }
    
    make_edge(&head1, &head2, weight);
    make_edge(&head2, &head1, weight);        
    
    if(0 == weight)
      head1->block = 1;
  }

  return graf;
}

static struct vertex* read_map(struct vertex* graf, FILE* file)
{
  int i = 0;
  char c = 0;
  int j = 0;
  while(c != 'E')
  {
    fscanf(file, "%c", &c);
    
    if(j <= 181)
    {  
      if( (13 + 14*i) == j)
      {
        if('w' == c)
        {
          graf = add_vertex(graf, j, j + 14, 0);
          j++;
        }
        else if('A' == c)
        {
          graf = add_vertex(graf, j, j + 14, 1);
          j++;
        }        
        i++;
      }
      else
      {  
        if('w' == c)
        {
          graf = add_vertex(graf, j, j + 1, 0);
          graf = add_vertex(graf, j, j + 14, 0);
          j++;
        }
        else if('A' == c)
        {
          graf = add_vertex(graf, j, j + 1, 1);
          graf = add_vertex(graf, j, j + 14, 1);
          j++;
        }
        
      }
    }
    else 
    {  
      if('w' == c)
      {
        graf = add_vertex(graf, j, j + 1, 0);
        j++;
      }
      else if('A' == c)
      {
        graf = add_vertex(graf, j, j + 1, 1);
        j++;
      }
      
    }      
  }
  
  

  return graf;
}

struct vertex* init_graf(FILE* file)
{
  assert(file);
  
  
   
  struct vertex* graf = NULL;
  
  #ifndef MAP
  
  int weight = 0;
  int vertex1 = 0;
  int vertex2 = 0;
  
  while(3 == fscanf(file,"%d %d %d",&vertex1,&vertex2,&weight))
  {
    graf = add_vertex(graf,vertex1,vertex2,weight);
  }
  
  #endif
  
  graf = read_map(graf, file);
  make_location(graf);
  
  return graf;
}

void print_graf(struct vertex* graf)
{
  assert(graf);

  int i = 0;
  
  while (graf != NULL)
  {
    printf("ID = (%d, %d, %d,%d) ",graf->id, graf->block, graf->x, graf->y);

    for(i = 0; i < graf->neighbours.real_size;i++)
      printf("[%d/%d]",graf->neighbours.buffer[i], graf->neighbours_weight.buffer[i]);
  
    graf = graf->next;
    putchar('\n');
  }
}

static int count_vertex(struct vertex* graf)
{
  assert(graf);

  int count = 0;

  while(NULL != graf)
  {
    count++;
    graf = graf->next;
  }
  
  return count;
}

// Manhattan distance
static int manhattan(struct vertex* graf, const int A, const int B) 
{ 
  assert(graf);

  struct vertex* start = find_vertex(graf,A);
  struct vertex* end = find_vertex(graf,B);

  return ( abs(start->x - end->x) + abs(start->y - end->y) );
}
static int** init_Matrix(int Height,int Width)
{
  int i = 0;

  int **Matrix = (int**)calloc(Height,sizeof(int*));
  for (i = 0; i < Height; i++)
  {
    Matrix[i] = (int*)calloc(Width,sizeof(int));
  }

  return Matrix;

}

void show(int** Matrix,int Height, int Width) // show field
{
  int i = 0;
  for (i = 0; i < Height; i++)
  {
    int j = 0;
    for (j = 0; j < Width; j++)
    {
      if(1 == Matrix[i][j])
        printf("\033[31m\033[1m%d\033[1m\033[31m",Matrix[i][j]);
      else
        printf("\033[37m\033[0m%d\033[0m\033[37m",Matrix[i][j]);
    }
    putchar('\n');
  }
  putchar('\n');
  printf("\033[0m\033[0m");

}

static void Clean_that_table(int** Matrix,int Height)// free Matrix
{
  int w = 0;

  for (w = 0; w < Height; w++)
    free(Matrix[w]);

  free(Matrix);
}

void path(int* came_from, int start, int goal)
{
  int current = goal;
  int i = 0;
  int x = 0;
  int y = 0;

  dyn_array temp = init_array(1);
  temp = add(temp,current);
  
  while(current != start)
  {
    current = came_from[current];
    temp = add(temp,current);
  }

  int** Matrix = init_Matrix(14,14);
  
  for( i = temp.real_size - 1; i >= 0; i--)
  {
    y = temp.buffer[i] / 14;
    x = temp.buffer[i] - y*14  ;
    Matrix[y][x] = 1;
  }
  
  show(Matrix,14,14);
  Clean_that_table(Matrix,14);
  
  for(i = temp.real_size - 1; i >= 0; i--)
    printf("%d->", temp.buffer[i]);

  free(temp.buffer);

}


void A_star(struct vertex* graf, const int A, const int B)
{
  assert(graf);

  int i = 0;
  int priority = 0;
  fheap* open = init_heap();
  int new_cost = 0;
  int size = count_vertex(graf);
  fheap_node* temp = NULL;

  // keep track of the total movement cost from the start location. 
  int* distance = (int*)calloc(size, sizeof(int)); 
  
  //array of flags 
  int* visited = (int*)calloc(size, sizeof(int));  
  
  //keep track of movements
  int* came_from = (int*)calloc(size, sizeof(int));  
    
  for( i = 0; i < size; i++)
  {
    distance[i] = INFINITY;
  }    
  
  insert(open,0,A);
  distance[A] = 0;
  came_from[A] = 0;
  
  while(get_min(open))
  {       
    temp = remove_min(open);
    visited[temp->number] = 1;

    if(temp->number == B)
    {
      break;                      
    }

    struct vertex* current_node = find_vertex(graf, temp->number);
    
    if(current_node->block)
    {
      visited[current_node->id] = 1;
      continue;
    }
      
    for(i = 0; i < current_node->neighbours.real_size; i++)
    {

      assert(distance[current_node->id] + current_node->neighbours_weight.buffer[i] < INT_MAX);
      new_cost = distance[current_node->id] + current_node->neighbours_weight.buffer[i]; 
        
      // if not visited
      if(!visited[current_node->neighbours.buffer[i]] || new_cost < distance[current_node->neighbours.buffer[i]])
      {
        distance[current_node->neighbours.buffer[i]] = new_cost ;
        priority = new_cost /*+ manhattan(graf,current_node->neighbours.buffer[i],B)*/;
        came_from[current_node->neighbours.buffer[i]] = current_node->id;
        insert(open,priority,current_node->neighbours.buffer[i]);
      }
      //Delete_node(open,temp);
    }
  }
  //Delete_node(open,open->min);
  
  if(temp->number != B)
  {
    printf("Cannot find path, because of walls!!");
  }
  else
  {
    path(came_from,A,B);
  }
  
  //free(temp);
  free(distance);
  free(visited);
  free(came_from);
  Delete_heap(open);
}


