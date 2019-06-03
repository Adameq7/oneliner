#include <stdlib.h>
#include <stdio.h>
#include "oneliner.h"

node *build_tree_sub(token *tokens, int token_number, 
                     int s_index1, int *s_index2,
                     func *functions, int *s_func_num,
                     var *variables, int *s_var_num)
{
  int index1 = s_index1,
      index2;
  node *new_node = (node*)malloc(sizeof(node)),
       *current, *body;

  int func_num = *s_func_num;
  int var_num = *s_var_num, old_var_num;

  new_node->next = NULL;

  switch(tokens[index1].type)
  {
    case _keyword:
      switch(tokens[index1].type_2.keyword_type)
      {
        case _func:
          new_node->type = node_func_decl;
          new_node->data.s_node_func_decl.arg_num = 0;

          index1++;
          
          if(tokens[index1].type != _identifier)
            error("Function declaration missing function name.", index1);

          new_node->data.s_node_func_decl.func_name = tokens[index1].name;

          create_func(functions, s_func_num, new_node->data.s_node_func_decl.func_name, new_node);
          func_num = *s_func_num;

          index1++;

          while(tokens[index1].type != _keyword || tokens[index1].type_2.keyword_type != _begin)
          {
            new_node->data.s_node_func_decl.arg_num++;            

            index1++;

            if(index1 == token_number)
              error("EOF reached while looking for function BEGIN.", index1);
          }

          new_node->data.s_node_func_decl.arg_name = (char**)malloc(new_node->data.s_node_func_decl.arg_num * sizeof(char*));

          for(int i = s_index1 + 2; i < index1; i++)
          {
            create_var(variables, &var_num, tokens[i].name);
            new_node->data.s_node_func_decl.arg_name[i - s_index1 - 2] = tokens[i].name;
          }

          index1++;
//          index2 = index1;
          body = (node*)malloc(sizeof(node));
          body->type = node_body;
          body->next = NULL;
          new_node->data.s_node_func_decl.body = body;
          current = body;

          while(tokens[index1].type != _keyword || tokens[index1].type_2.keyword_type != _return)
          {
            old_var_num = var_num;

            current->next = build_tree_sub(tokens, token_number, index1, &index2, functions, &func_num, variables, &var_num);
            current = current->next;

            if(current->type != node_var_decl) var_num = old_var_num;

            index1 = index2;

            if(index1 == token_number)
              error("EOF reached while looking for function RETURN.", index1);
          }

          while(tokens[index1].type != _keyword || tokens[index1].type_2.keyword_type != _end)
          {
            if(index1 == token_number)
              error("EOF reached while looking for function END.", index1);
            index1++;
          }

          if(tokens[index1 - 1].type == _keyword && tokens[index1 - 1].type_2.keyword_type == _return)
          {
            new_node->data.s_node_func_decl.ret_val = NULL;
          }
          else
          {
            if(tokens[index1 - 2].type == _keyword && tokens[index1 - 2].type_2.keyword_type == _return)
            {
              if(tokens[index1 - 1].type == _identifier)
              {
                new_node->data.s_node_func_decl.ret_val = tokens[index1 - 1].name; 
              }
              else
              {
                error("return must return a single variable or nothing.", index1 - 1);
              }
            }
            else
            {
              error("no return at end of function.", index1 - 1);
            }
          }
        break;
        case _while:
          new_node->type = node_while;

          index1++;

          if(tokens[index1].type != _identifier)
            error("while condition must be a variable.", index1);

          new_node->data.s_node_while.condition = tokens[index1].name;

          index1++;
 
          if(tokens[index1].type != _keyword || tokens[index1].type_2.keyword_type != _do)
            error("while missing do.", index1);

          index1++;
          body = (node*)malloc(sizeof(node));
          body->type = node_body;
          body->next = NULL;
          new_node->data.s_node_while.body = body;
          current = body;

          while(tokens[index1].type != _keyword || tokens[index1].type_2.keyword_type != _done)
          {
            old_var_num = var_num;

            current->next = build_tree_sub(tokens, token_number, index1, &index2, functions, &func_num, variables, &var_num);
            current = current->next;

            if(current->type != node_var_decl) var_num = old_var_num;

            index1 = index2;

            if(index1 == token_number)
              error("EOF reached while looking for while done.", index1);
          }
        break;
        case _if:
          new_node->type = node_if;

          index1++;

          if(tokens[index1].type != _identifier)
            error("if condition must be a variable.", index1);

          new_node->data.s_node_if.condition = tokens[index1].name;

          index1++;
          body = (node*)malloc(sizeof(node));
          body->type = node_body;
          body->next = NULL;
          new_node->data.s_node_if.lbody = body;
          current = body;

          while(tokens[index1].type != _keyword || (tokens[index1].type_2.keyword_type != _else && tokens[index1].type_2.keyword_type != _fi))
          {
            old_var_num = var_num;

            current->next = build_tree_sub(tokens, token_number, index1, &index2, functions, &func_num, variables, &var_num);
            current = current->next;

            if(current->type != node_var_decl) var_num = old_var_num;

            index1 = index2;

            if(index1 == token_number)
              error("EOF reached while looking for if else.", index1);
          }
          
          if(tokens[index1].type_2.keyword_type == _else)
          {
            index1++;
            body = (node*)malloc(sizeof(node));
            body->type = node_body;
            body->next = NULL;
            new_node->data.s_node_if.rbody = body;
            current = body;

            while(tokens[index1].type != _keyword || tokens[index1].type_2.keyword_type != _fi)
            {
              old_var_num = var_num;

              current->next = build_tree_sub(tokens, token_number, index1, &index2, functions, &func_num, variables, &var_num);
              current = current->next;

              if(current->type != node_var_decl) var_num = old_var_num;

              index1 = index2;

              if(index1 == token_number)
                error("EOF reached while looking for if fi.", index1);
            }
          }
          else
          {
            index1++;
            new_node->data.s_node_if.rbody = NULL;
          }
        break;
        case _var:
          new_node->type = node_var_decl;

          index1++;
 
          if(tokens[index1].type != _identifier)
            error("variable name must be given.", index1);

          new_node->data.s_node_var_decl.var_name = tokens[index1].name;

          create_var(variables, s_var_num, tokens[index1].name);
        break;
        case _set:
          new_node->type = node_var_set;

          index1++;

          if(tokens[index1].type != _identifier)
            error("variable name missing.", index1);

          new_node->data.s_node_var_set.var_name = tokens[index1].name;

          index1++;

          if(tokens[index1].type != _identifier && tokens[index1].type != _number && tokens[index1].type != _operator)
            error("incorrect set syntax.", index1);

          if(is_variable(tokens[index1].name, variables, var_num))
          {
            new_node->data.s_node_var_set.type = 2;
            new_node->data.s_node_var_set.body.copy.arg1.is_var = 1;
            new_node->data.s_node_var_set.body.copy.arg1.data.name = tokens[index1].name;
          }
          else if(is_function(tokens[index1].name, functions, func_num))
          {
            func *f = is_function(tokens[index1].name, functions, func_num);

            new_node->data.s_node_var_set.type = 0;
            new_node->data.s_node_var_set.body.func.name = f->name;
            new_node->data.s_node_var_set.body.func.arg_num = f->func_decl_node->data.s_node_func_decl.arg_num;
            new_node->data.s_node_var_set.body.func.args = (arg*)malloc((f->func_decl_node->data.s_node_func_decl.arg_num) * sizeof(arg));

            for(int i = 0; i < f->func_decl_node->data.s_node_func_decl.arg_num; i++)
            {
              index1++;

              if(is_variable(tokens[index1].name, variables, var_num))
              {
                new_node->data.s_node_var_set.body.func.args[i].is_var = 1;
                new_node->data.s_node_var_set.body.func.args[i].data.name = tokens[index1].name;
              }
              else if(tokens[index1].type == _number)
              {
                new_node->data.s_node_var_set.body.func.args[i].is_var = 0;
                new_node->data.s_node_var_set.body.func.args[i].data.val = strtod(tokens[index1].name, NULL);
              }
              else
                error("argument must be a number or a variable.", index1);
            }
          }
          else if(tokens[index1].type == _number)
          {
            new_node->data.s_node_var_set.type = 2;
            new_node->data.s_node_var_set.body.copy.arg1.is_var = 0;
            new_node->data.s_node_var_set.body.copy.arg1.data.val = strtod(tokens[index1].name, NULL);
          }
          else if(tokens[index1].type == _operator)
          {
            new_node->data.s_node_var_set.type = 1;
            new_node->data.s_node_var_set.body.operation.operation = tokens[index1].type_2.operator_type;           
 
            index1++;
           
            if(is_variable(tokens[index1].name, variables, var_num))
            {
              new_node->data.s_node_var_set.body.operation.arg1.is_var = 1;
              new_node->data.s_node_var_set.body.operation.arg1.data.name = tokens[index1].name;
            }
            else if(tokens[index1].type == _number)
            {
              new_node->data.s_node_var_set.body.operation.arg1.is_var = 0;
              new_node->data.s_node_var_set.body.operation.arg1.data.val = strtod(tokens[index1].name, NULL);
            }
            else
              error("argument must be a number or a variable.", index1);
             
            index1++;
           
            if(is_variable(tokens[index1].name, variables, var_num))
            {
              new_node->data.s_node_var_set.body.operation.arg2.is_var = 1;
              new_node->data.s_node_var_set.body.operation.arg2.data.name = tokens[index1].name;
            }
            else if(tokens[index1].type == _number)
            {
              new_node->data.s_node_var_set.body.operation.arg2.is_var = 0;
              new_node->data.s_node_var_set.body.operation.arg2.data.val = strtod(tokens[index1].name, NULL);
            }
            else
              error("argument must be a number or a variable.", index1);
          }
          else
            error("incorrect set syntax.", index1);

        break;
        case _print:
          new_node->type = node_print;

          index1++;
 
          if(tokens[index1].type == _identifier)
          {
            new_node->data.s_node_print.is_arg = 1;
            new_node->data.s_node_print.arg1.is_var = 1;
            new_node->data.s_node_print.arg1.data.name = tokens[index1].name;
          }
          else if(tokens[index1].type == _number)
          {
            new_node->data.s_node_print.is_arg = 1;
            new_node->data.s_node_print.arg1.is_var = 0;
            new_node->data.s_node_print.arg1.data.val = strtod(tokens[index1].name, NULL);
          }
          else if(tokens[index1].type == _string)
          {
            new_node->data.s_node_print.is_arg = 0;
            new_node->data.s_node_print.message = tokens[index1].name;
          }
          else
            error("value to print must be a variable, number or string.", index1);
  
          index1++;

          if((tokens[index1].type == _keyword) && (tokens[index1].type_2.keyword_type == _newline))
          {
            new_node->data.s_node_print.newline = 1;
          }
          else
          {
            new_node->data.s_node_print.newline = 0;
            index1--;
          }
        
       break;
      }
    break;
    default:
      error("syntax error.", index1);
  }

  index1++;
  *s_index2 = index1;
  return new_node;
}

node *build_tree(token *tokens, int token_number,
                 func *functions, int *func_num,
                 var *variables, int *var_num)
{
  int index1 = 1,
      index2 = 2;

  if(tokens[0].type != _keyword || tokens[0].type_2.keyword_type != _program_begin)
  {printf("program doesn't start with PROGRAMBEGIN\n"); exit(-1);};
  if(tokens[token_number - 1].type != _keyword || tokens[token_number - 1].type_2.keyword_type != _program_end)
  {printf("program doesn't end with PROGRAMEND\n"); exit(-1);};

  node *root = (node*)(malloc(sizeof(node)));

  node *current;
  current = root;
  current->next = current;

  index2 = 1;

  while(index2 < token_number - 1)
  {
    current->next = build_tree_sub(tokens, token_number, index2, &index2, functions, func_num, variables, var_num);
    current = current->next;
    current->next = NULL;
  }

  root->type = node_body;
//  root->data.s_node_body

  return root;
}
