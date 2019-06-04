#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "oneliner.h"

var *create_var(var* variables, int *var_num, char *name)
{
  variables[*var_num].name = name;
  variables[*var_num].val = 0;
  (*var_num)++;
  return variables + (*var_num - 1);
}

void create_func(func* functions, int *func_num, char *name, node *func_decl_node)
{
  functions[*func_num].name = name;
  functions[*func_num].func_decl_node = func_decl_node;
  (*func_num)++;
  
  return;
}

func* is_function(char* name, func* functions, int func_num)
{
  for(int i = func_num - 1; i >= 0; i--)
    if(!strcmp(name, functions[i].name))
      return functions + i;

  return NULL;
}

var* is_variable(char* name, var* variables, int var_num)
{
  for(int i = var_num - 1; i >= 0; i--)
    if(!strcmp(name, variables[i].name))
      return variables + i;

  return NULL;
}

char is_forbidden(char c)
{
  return ((c >= 9) && (c <= 13));
}

char is_number(char *word, int length)
{
  for(int i = 0; i < length; i++)
  {
    if(word[i] < '0' || word[i] > '9')
      return 0;
  }

  return 1;
}

char is_lowercase(char c)
{
  return (c >= 97) && (c <= 122);
}

char is_uppercase(char c)
{
  return (c >= 65) && (c <= 90);
}

void error(char *msg, int index1)
{
  printf("'%s' at %d\n", msg, index1);
  exit(-1);
}

void tabs(int n)
{
  for(int i = 0; i < n; i++) printf("  ");
  return;
}

void add_ptr(void *ptr, void **pointers, int *pointer_num)
{
  pointers[*pointer_num] = ptr;

  *pointer_num++;

  return;
}
