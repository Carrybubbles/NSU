#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>

#define PLUS -11
#define MINUS -22
#define DELIT -33
#define UMNOZHIT -44
#define OS -55
#define CS -66



void print_array(int* buffer,int len);

typedef struct list{
  int value;
  struct list* next;
} stack;

stack* push(stack* head, int value)
{
  stack* ptr = calloc(sizeof(*ptr),1);
  if(NULL == head)
  {
    ptr->next = NULL;
    ptr->value = value;
    return ptr;
  }
  else
  {   
    ptr->value = value;
    ptr->next = head;
    head = ptr;
    return ptr;
  }
}

int pop(stack** head)
{
  stack* ptr = NULL;
  int k = 0;
  
  if (NULL == (*head))
  {
    return 0;
  }
  else
  {
    k = (*head)->value;
    ptr = (*head)->next;
    free(*head);
    *head = ptr;
  }   
  return k;
}

int check_OS_CS(int* str, int len) 
{
  int i = 0;
  int j = 0;
  int k = 0;
  int count = 0;
  int* buffer = (int*)calloc(len, sizeof(int));
  int* result = (int*)calloc(len, sizeof(int));
  
  for ( i = 0 ; i < len; i++)
  {
    if (str[i] != OS && str[i] != CS)
      buffer[j++] = str[i];
    else if(str[i] == OS)
    {
      count++;
      if (count >= 0)
      {
        buffer[j++] = OS;
      }
      else
      {
        free(buffer);
        free(result);   
        return 1;
      }
    }
    else if(str[i] == CS)
    {
      count--;
      if (count >= 0)
      {
        buffer[j++] = CS;
      }
      else
      {
        free(buffer);
        free(result);   
        return 1;
      }
    }   
  }
  
  count = 0;
  
  for (i = j-1; i >= 0; i--)
  {
    if (buffer[i] != OS && buffer[i] != CS)
      result[k++] = buffer[i];
    else if (buffer[i] == OS)
    {
      count--;
      if(count >= 0)
        result[k++] = OS;
      else
      {
        free(buffer);
        free(result);   
        return 1;
      }
    }
    else if (buffer[i] == CS)
    {   
      count++;
      if(count >= 0)
        result[k++] = CS;
      else
      {
        free(buffer);
        free(result);
        return 1;               
      }
    }
  }

  free(buffer);
  free(result);

  return 0;
}


void print_array(int* buffer, int len)
{
  int i = 0;

  for (i = 0; i < len; i++)
  {
  if (PLUS == buffer[i])
    printf("+");
  else if (MINUS == buffer[i])
    printf("-");
  else if (UMNOZHIT == buffer[i])
    printf("*");
  else if (DELIT == buffer[i])
    printf("/");
  else if (CS == buffer[i])
    printf(")");
  else if (OS == buffer[i])
    printf("(");
  else 
    printf("%d",buffer[i]);
  }
}

int check(int c)
{
  if ( (DELIT == c) || (UMNOZHIT  == c) )
    return 2;
  else if ( (PLUS == c) || (MINUS == c) )
    return 1;
  else  if ( (OS == c) || (CS == c) ) 
    return 0; 
}


int** convert(char* buffer, int len)
{
  int** arrays = (int**)calloc(2, sizeof(int*));   
  arrays[0] = (int*)calloc(len, sizeof(int));
  arrays[1] = (int*)calloc(1, sizeof(int));
  int count = 0;
  int j = 0;
  int i = 0;

  for ( i = 0; i < len;i++)
  {
    if (buffer[i] >= '0' && buffer[i] <= '9')
    {
        char* temp = calloc(sizeof(char),len);
        while(isdigit(buffer[i]))
        {
         temp[j++] = buffer[i++];
        }
  
        j = atoi(temp);
        arrays[0][count++] = j;
        i--;
        j = 0;
        free(temp);
      }
      else if ('+' == buffer[i])
      {
        arrays[0][count++] = PLUS;
      }
      else if ('-' == buffer[i])
      {
        arrays[0][count++] = MINUS;
      }
      else if ('/' == buffer[i])
      {
        arrays[0][count++] = DELIT;
      }
      else if ('*' == buffer[i])
      {
        arrays[0][count++] = UMNOZHIT;
      }
      else if (')' == buffer[i])
      {
        arrays[0][count++] = CS;
      }
      else if ('(' == buffer[i])
      {
        arrays[0][count++] = OS;
    }
  }

  arrays[1][0] = count;
  
  return arrays;
}

int count_skobki(int* buffer, int len)
{
  int i = 0;
  int count = 0;
  for ( i = 0; i < len;i++)
  {
    if( OS == buffer[i] || CS == buffer[i])
      count++;
    else
      continue;
  }
  
  return count;
}

int* from2to1(int** temp)
{
  int len2 = temp[1][0];
  int* result = (int*)calloc(len2, sizeof(int));
  int i = 0;
  for(i = 0; i < len2 ; i++)
  {  
    result[i] = temp[0][i];
  }
  
  free(temp[0]);
  free(temp[1]);
  free(temp);
  
  return result;
}

int* OPS(int* buffer, int len, int len2)
{
  int* result =(int*)calloc(sizeof(int), len2 );
  int pr = 0;
  int pr_trash = 0;
  int i = 0;
  int j = 0;
  stack* trash = NULL;

  for (i = 0; i < len; i++)
  {
    if (buffer[i] >= 0)
    {
      result[j++] = buffer[i];
    }
    else if ( (MINUS == buffer[i]) || (UMNOZHIT == buffer[i]) || (DELIT == buffer[i]) || (PLUS == buffer[i]))
    {
      while(1)
      {
        if (NULL == trash)
        {
          trash = push(trash,buffer[i]);
          break;
        }
        else
        {
          pr = check(buffer[i]);
          pr_trash = check(trash->value);
          if (pr <= pr_trash)
          {   
            result[j++] = pop(&trash);
          }
          else if (pr > pr_trash)
          {
            trash = push(trash, buffer[i]);
            break;
          }
        }
      }   
    }       
    else if( OS == buffer[i])
    {
      trash = push(trash,buffer[i]);
    }
    else if( CS == buffer[i])
    {
      while( OS != trash->value )
      {
        result[j++] = pop(&trash);
      }
      pop(&trash);
    }
  }

  if (len == i)
  {   
    while(NULL != trash)    
    {   
      result[j++] = pop(&trash);
    }
  }
  
  free(buffer);
  
  return result;
}

int check_symbols(int* buffer, int len)
{
  int i = 0;

  for( i = 0; i < len - 1;i++)
  {
    
    if(buffer[i] < 0  && buffer[i+1] < 0 && buffer[i] != OS && buffer[i+1] != OS && buffer[i+1] != CS && buffer[i] != CS )
      return 1;
    if(buffer[0] < 0 && buffer[0] != CS && buffer[0] != OS)
      return 1;
    if(buffer[i] == OS && buffer[i+1] < 0 && buffer[i+1] != CS && buffer[i+1] != OS)
      return 1;
  }
  
  return 0;
}

int show_result(int* buffer, int len) 
{
  stack* trash = NULL;
  int n1 = 0;
  int n2 = 0;
  int res = 0;
  int i = 0;
    
  for(i = 0; i < len; i++)
  {
    if( buffer[i] >= 0)
    {   
     trash = push(trash,buffer[i]);
    }
    else 
    {
      n2 = pop(&trash); 
      n1 = pop(&trash);
      switch(buffer[i]) 
      {
      case PLUS: 
        res = n1 + n2; 
        break;
      case MINUS: 
        res = n1 - n2; 
        break;
      case UMNOZHIT: 
        res = n1 * n2; 
        break;
      case DELIT: 
        if(0 == n2)
        {      
          printf("DIV 0 or unknown symbol. Are u mad?\n");
          return -1;
        }
        res = n1 / n2; 
        break;
      }
      trash = push(trash,res);
    }
  }
    
  return pop(&trash);
}

int main(int argc, char** argv)
{
  char* buffer = (char*)calloc(256, sizeof(char));
  int j = 0;
  int i = 0;
  scanf("%s", buffer);
  
  int len = strlen(buffer);
  int** string = convert(buffer, len);
  int len2 = string[1][0];
  int* temp = from2to1(string);
  free(buffer);
 

  if(1 == check_OS_CS(temp, len2))
  {
    printf("Bad input(skobki)\n");
    free(temp);
    return 1;
  }
  if(1 == check_symbols(temp, len2))
  {
    printf("Bad input(znaki) or there are some letters \n");
    free(temp);
    return 1;
  }

  j = count_skobki(temp, len2);
  int* result = OPS(temp, len2, len2 - j);
  
  if(-1 == show_result(result, len2 - j))
  {
    free(result);
    return 1;
  }
  else
  {
    printf(" result = %d\n", show_result(result, len2-j));
    print_array(result, len2 - j);
  
    free(result);
  }
}

