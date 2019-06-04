#include <stdlib.h>
#include <stdio.h>
#include "oneliner.h"

extern const char operators[];

void print_tree(node *root, int n)
{
  node *current;

  switch(root->type)
  {
    case node_body:
      tabs(n);
      printf("body begin:\n");

      current = root->next;
      while(current != NULL)
      {
//        tabs(n + 1);
//        printf("something.\n");
        print_tree(current, n + 1);
        current = current->next;
      }

      tabs(n);
      printf("body end.\n");
    break;
    case node_func_decl:
      tabs(n);
      printf("function declaration:\tname: %s\targnum: %d\n", root->data.s_node_func_decl.func_name, 
                                                              root->data.s_node_func_decl.arg_num);
      print_tree(root->data.s_node_func_decl.body, n + 1);

      tabs(n);
      printf("function declaration end.\n");
    break;
    case node_while:
      tabs(n);
      printf("while:\tcondition: %s\tdo:\n", root->data.s_node_while.condition);
      print_tree(root->data.s_node_while.body, n + 1);

      tabs(n);
      printf("done.\n");
    break;
    case node_if:
      tabs(n);
      printf("if: condition: %s then:\n", root->data.s_node_while.condition);
      print_tree(root->data.s_node_if.lbody, n + 1);
      tabs(n);
      printf("else:\n");
      print_tree(root->data.s_node_if.rbody, n + 1);
      tabs(n);
      printf("fi.\n");
    break;
    case node_var_decl:
      tabs(n);
      printf("var declaration: name: %s\n", root->data.s_node_var_decl.var_name);
    break;
    case node_var_set:
      tabs(n);
      printf("var set: name: %s = ", root->data.s_node_var_set.var_name);
//      tabs(n);
      switch(root->data.s_node_var_set.type)
      {
        case 0:
          printf("function: name: %s argnum: %d args: ", root->data.s_node_var_set.body.func.name, 
                                                         root->data.s_node_var_set.body.func.arg_num);
          for(int i = 0; i < root->data.s_node_var_set.body.func.arg_num; i++)
          if(root->data.s_node_var_set.body.func.args[i].is_var)
            printf("%s ", root->data.s_node_var_set.body.func.args[i].data.name);
          else
            printf("%lf ", root->data.s_node_var_set.body.func.args[i].data.val);
          printf("\n");
        break;
        case 1:
          printf("operation: type: %c ", operators[root->data.s_node_var_set.body.operation.operation]); 
          if(root->data.s_node_var_set.body.operation.arg1.is_var)
            printf("var: %s ", root->data.s_node_var_set.body.operation.arg1.data.name);
          else
            printf("val: %lf ", root->data.s_node_var_set.body.operation.arg1.data.val);
          if(root->data.s_node_var_set.body.operation.arg2.is_var)
            printf("var: %s ", root->data.s_node_var_set.body.operation.arg2.data.name);
          else
            printf("val: %lf ", root->data.s_node_var_set.body.operation.arg2.data.val);
          printf("\n");
        break;
        case 2:
          printf("copy value:\t");
          if(root->data.s_node_var_set.body.copy.arg1.is_var)
            printf("var: %s\n", root->data.s_node_var_set.body.copy.arg1.data.name);
          else
            printf("val: %lf\n", root->data.s_node_var_set.body.copy.arg1.data.val);
        break;
      }
    break;
    case node_mem_op:
      tabs(n);
      printf("memory ");

      if(root->data.s_node_mem_op.is_read)
      {
        printf("read from index "); 
        
        if(root->data.s_node_mem_op.arg1.is_var)
          printf("%s ", root->data.s_node_mem_op.arg1.data.name);
        else
          printf("%d ", (int)root->data.s_node_mem_op.arg1.data.val);

        printf("into var %s\n", root->data.s_node_mem_op.arg2.data.name);
      }
      else
      {
        printf("write to index "); 
        
        if(root->data.s_node_mem_op.arg1.is_var)
          printf("%s ", root->data.s_node_mem_op.arg1.data.name);
        else
          printf("%d ", (int)root->data.s_node_mem_op.arg1.data.val);

        printf("from ");

        if(root->data.s_node_mem_op.arg2.is_var)        
          printf("var %s\n", root->data.s_node_mem_op.arg2.data.name);
        else
          printf("val %lf\n", root->data.s_node_mem_op.arg2.data.val);
      }
    break;
    case node_print:
      tabs(n);
      printf("print: ");
      if(root->data.s_node_print.is_arg)
      {
        if(root->data.s_node_print.arg1.is_var)
          printf("var: %s", root->data.s_node_print.arg1.data.name);
        else
          printf("val: %lf", root->data.s_node_print.arg1.data.val);
      }
      else
        printf("%s", root->data.s_node_print.message);

      if(root->data.s_node_print.newline)
        printf(" | newline");
      printf("\n"); 
//      printf("print something.\n");
    break;
    default:
      tabs(n);
      printf("something.\n");
    break;
  }
}

void print_out(node *root, var *variables, int var_num)
{
  double val;

//  printf("OUT:\t");

  if(root->data.s_node_print.is_arg)
  {
    if(root->data.s_node_print.arg1.is_var)
    {
      val = is_variable(root->data.s_node_print.arg1.data.name, variables, var_num)->val;
    }
    else
    {
      val = root->data.s_node_print.arg1.data.val;
    }
    
    printf("%lf ", val);
  }
  else
  {
    printf("%s ", root->data.s_node_print.message);
  }

  if(root->data.s_node_print.newline)
    printf("\n");
}
