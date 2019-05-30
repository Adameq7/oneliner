#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "main.h"

#define DEBUG 1

const char program_begin_string[] = "PROGRAMBEGIN";
const char program_end_string[] = "PROGRAMEND";
const char func_string[] = "FUNC";
const char begin_string[] = "BEGIN";
const char end_string[] = "END";
const char while_string[] = "WHILE";
const char do_string[] = "DO";
const char done_string[] = "DONE";
const char if_string[] = "IF";
const char else_string[] = "ELSE";
const char fi_string[] = "FI";
const char var_string[] = "VAR";
const char set_string[] = "SET";
const char print_string[] = "PRINT";
const char return_string[] = "RETURN";

const char op_add_string[] = "ADD";
const char op_sub_string[] = "SUB";
const char op_mult_string[] = "MULT";
const char op_div_string[] = "DIV";
const char op_and_string[] = "AND";
const char op_or_string[] = "OR";
const char op_not_string[] = "NOT";
const char op_equal_string[] = "EQUAL";
const char op_less_string[] = "LESS";
const char op_greater_string[] = "GREATER";


const char operators[]="+-*/&|!=<>";

/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/

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

char tokenize(char *word, int length, token *new_token)
{
  char *name = (char*)malloc(length + 1);

  memcpy(name, word, length);
  name[length] = 0;
  
  new_token->name = name;

  if(!strncmp(name, op_add_string, 3)){new_token->type = _operator; new_token->type_2.operator_type = _add; return 1;};
  if(!strncmp(name, op_sub_string, 3)){new_token->type = _operator; new_token->type_2.operator_type = _sub; return 1;};
  if(!strncmp(name, op_mult_string, 4)){new_token->type = _operator; new_token->type_2.operator_type = _mult; return 1;};
  if(!strncmp(name, op_div_string, 3)){new_token->type = _operator; new_token->type_2.operator_type = _div; return 1;};
  if(!strncmp(name, op_and_string, 3)){new_token->type = _operator; new_token->type_2.operator_type = _and; return 1;};
  if(!strncmp(name, op_or_string, 2)){new_token->type = _operator; new_token->type_2.operator_type = _or; return 1;};
  if(!strncmp(name, op_not_string, 3)){new_token->type = _operator; new_token->type_2.operator_type = _not; return 1;};
  if(!strncmp(name, op_equal_string, 5)){new_token->type = _operator; new_token->type_2.operator_type = _equal; return 1;};
  if(!strncmp(name, op_less_string, 4)){new_token->type = _operator; new_token->type_2.operator_type = _less; return 1;};
  if(!strncmp(name, op_greater_string, 7)){new_token->type = _operator; new_token->type_2.operator_type = _greater; return 1;};

  if(!strncmp(name, func_string, 4)){new_token->type = _keyword; new_token->type_2.keyword_type = _func; return 1;};
  if(!strncmp(name, begin_string, 5)){new_token->type = _keyword; new_token->type_2.keyword_type = _begin; return 1;};
  if(!strncmp(name, end_string, 3)){new_token->type = _keyword; new_token->type_2.keyword_type = _end; return 1;};
  if(!strncmp(name, while_string, 5)){new_token->type = _keyword; new_token->type_2.keyword_type = _while; return 1;};
  if(!strncmp(name, if_string, 2)){new_token->type = _keyword; new_token->type_2.keyword_type = _if; return 1;};
  if(!strncmp(name, else_string, 4)){new_token->type = _keyword; new_token->type_2.keyword_type = _else; return 1;};
  if(!strncmp(name, var_string, 3)){new_token->type = _keyword; new_token->type_2.keyword_type = _var; return 1;};
  if(!strncmp(name, set_string, 3)){new_token->type = _keyword; new_token->type_2.keyword_type = _set; return 1;};
  if(!strncmp(name, print_string, 5)){new_token->type = _keyword; new_token->type_2.keyword_type = _print; return 1;};
  if(!strncmp(name, return_string, 6)){new_token->type = _keyword; new_token->type_2.keyword_type = _return; return 1;};
  if(!strncmp(name, fi_string, 2)){new_token->type = _keyword; new_token->type_2.keyword_type = _fi; return 1;};
  if(!strncmp(name, done_string, 4)){new_token->type = _keyword; new_token->type_2.keyword_type = _done; return 1;};
  if(!strncmp(name, do_string, 2)){new_token->type = _keyword; new_token->type_2.keyword_type = _do; return 1;};
  if(!strncmp(name, program_begin_string, 12)){new_token->type = _keyword; new_token->type_2.keyword_type = _program_begin; return 1;};
  if(!strncmp(name, program_end_string, 10)){new_token->type = _keyword; new_token->type_2.keyword_type = _program_end; return 1;};

  if(is_number(word, length)){new_token->type = _number; return 1;};

  char lc = 0, uc = 0;

  for(int i = 0; i < length; i++)
  {
    if(is_lowercase(word[i]))
      lc = 1;
    if(is_uppercase(word[i]))
      uc = 1;
  }

  if((!lc && !uc) || (lc && uc))
  {
    printf("syntax error\n");
    exit(-1);
  }

  if(lc && !uc){new_token->type = _identifier; return 1;};

  return 0;
}

void parse_line(char *line, token *tokens, int *token_number)
{
  int index1 = 0,
      index2 = 1;

  while(1)
  {
    printf("%d %d\n", index1, index2);

    if(is_forbidden(line[index2]))
    {
      printf("forbidden char detected at %d\n", index2);
      exit(-1);
    }

    if(line[index2] == 32 || line[index2] == 0)
    {
      if(tokenize(line + index1, index2 - index1, &tokens[*token_number]))
      {
        (*token_number)++;

        if(line[index2] == 0)
        {
          break;
        }

        index1 = index2 + 1;
        index2 += 2;
      }
      else
      {
        index2++;
      }
    }
    else
    {
      index2++;
    }
  }

  for(int i = 0; i < *token_number; i++)
    printf(" - %s %d %d\n", tokens[i].name, tokens[i].type, tokens[i].type_2.keyword_type); 

  return;
}

void error(char *msg, int index1)
{
  printf("'%s' at %d\n", msg, index1);
  exit(-1);
}

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

          while(tokens[index1].type != _keyword || tokens[index1].type_2.keyword_type != _else)
          {
            old_var_num = var_num;

            current->next = build_tree_sub(tokens, token_number, index1, &index2, functions, &func_num, variables, &var_num);
            current = current->next;

            if(current->type != node_var_decl) var_num = old_var_num;

            index1 = index2;

            if(index1 == token_number)
              error("EOF reached while looking for if else.", index1);
          }

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
          
       break;
      }
    break; 
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

void tabs(int n)
{
  for(int i = 0; i < n; i++) printf("  ");
  return;
}

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
    case node_print:
      tabs(n);
      printf("print: ");
      if(root->data.s_node_print.is_arg)
      {
        if(root->data.s_node_print.arg1.is_var)
          printf("var: %s ", root->data.s_node_print.arg1.data.name);
        else
          printf("val: %lf ", root->data.s_node_print.arg1.data.val);
      }
      else
        printf("%s", root->data.s_node_print.message);
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

  printf("OUT:\t");

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
  }
  else
  {
  }

  printf("%lf\n", val);
}

double execute(node *root, func *functions, int func_num, var *variables, int *var_num, char* ret_var)
{
  if(root == NULL)
    return 0;

  double arg_vals[MAX_FUNC_ARG_NUM];
  int new_var_num = *var_num;
  double ret_val = 0, val1, val2;
  var *var1, *var2;
  func *function;
  node *current;

  switch(root->type)
  {
    case node_body:
      current = root->next;

      while(current != NULL)
      {
        execute(current, functions, func_num, variables, &new_var_num, NULL);

        current = current->next;
      }

    if(ret_var != NULL)
    {
      ret_val = is_variable(ret_var, variables, new_var_num)->val;
    }

    break;
    case node_while:
      var1 = is_variable(root->data.s_node_while.condition, variables, new_var_num);

      while((int)var1->val)
      {
        execute(root->data.s_node_while.body, functions, func_num, variables, &new_var_num, NULL);
      }
    break;
    case node_if:
      var1 = is_variable(root->data.s_node_if.condition, variables, new_var_num);

      if((int)var1->val)
      {
        execute(root->data.s_node_if.lbody, functions, func_num, variables, &new_var_num, NULL);
      }
      else
      {
        execute(root->data.s_node_if.rbody, functions, func_num, variables, &new_var_num, NULL);
      }
    break;
    case node_var_decl:
      create_var(variables, var_num, root->data.s_node_var_decl.var_name);
    break;
    case node_var_set:
      var1 = is_variable(root->data.s_node_var_set.var_name, variables, new_var_num); 

      switch(root->data.s_node_var_set.type)
      {
        case 0:
          function = is_function(root->data.s_node_var_set.body.func.name, functions, func_num);

          for(int i = 0; i < function->func_decl_node->data.s_node_func_decl.arg_num; i++)
            if(root->data.s_node_var_set.body.func.args[i].is_var)
              arg_vals[i] = is_variable(root->data.s_node_var_set.body.func.args[i].data.name, variables, new_var_num)->val;
            else
              arg_vals[i] = root->data.s_node_var_set.body.func.args[i].data.val;
 
          for(int i = 0; i < function->func_decl_node->data.s_node_func_decl.arg_num; i++)
            create_var(variables, &new_var_num, function->func_decl_node->data.s_node_func_decl.arg_name[i])->val = arg_vals[i];

          ret_val = execute(function->func_decl_node->data.s_node_func_decl.body, functions, func_num, variables, &new_var_num, function->func_decl_node->data.s_node_func_decl.ret_val);
          var1->val = ret_val;
        break;
        case 1:
          val1 = root->data.s_node_var_set.body.operation.arg1.is_var ?
                 is_variable(root->data.s_node_var_set.body.operation.arg1.data.name, variables, new_var_num)->val :
                 root->data.s_node_var_set.body.operation.arg1.data.val;
          val2 = root->data.s_node_var_set.body.operation.arg2.is_var ?
                 is_variable(root->data.s_node_var_set.body.operation.arg2.data.name, variables, new_var_num)->val :
                 root->data.s_node_var_set.body.operation.arg2.data.val;

          switch(root->data.s_node_var_set.body.operation.operation)
          {
            case 0:
              var1->val = val1 + val2;
            break;
            case 1:
              var1->val = val1 - val2;
            break;
            case 2:
              var1->val = val1 * val2;
            break;
            case 3:
              var1->val = val1 / val2;
            break;
            case 4:
              var1->val = (int)val1 && (int)val2;
            break;
            case 5:
              var1->val = (int)val1 || (int)val2;
            break;
            case 6:
//              var1->val = val1 / val2;
            break;
            case 7:
              var1->val = (int)val1 == (int)val2;
            break;
            case 8:
              var1->val = (int)val1 < (int)val2;
            break;
            case 9:
              var1->val = (int)val1 > (int)val2;
            break;
          }
        break;
        case 2:
          var1-> val = root->data.s_node_var_set.body.copy.arg1.is_var ?
                       is_variable(root->data.s_node_var_set.body.copy.arg1.data.name, variables, new_var_num)->val :
                       root->data.s_node_var_set.body.copy.arg1.data.val;
        break;
      }
    break;
    case node_print:
      print_out(root, variables, new_var_num);
    break;

    default:
      error("unknown node type.", -1);
  }

  return ret_val;
}

/*----------------------------------------------------------------------------*/

int main(int argc, char **argv)
{
  char *line;

  int ret_code = 0, 
      token_number = 0;

  func functions[MAX_FUNC_NUM];
  int func_num = 0;

  var variables[MAX_VAR_NUM];
  int var_num = 0;
  token tokens[1024];
  node *root; 
  double res;

  while(1)
  {
    token_number = 0;

    printf("---\n");
    line = readline(NULL);

    if(line == NULL)
     break;

    parse_line(line, tokens, &token_number);
    root = build_tree(tokens, token_number, functions, &func_num, variables, &var_num);
    print_tree(root, 0);

    var_num = 0;
    res = execute(is_function("main", functions, func_num)->func_decl_node->data.s_node_func_decl.body, functions, func_num, variables, &var_num, NULL);
    printf("program ended with return %lf\n", res);

    free(line);
  }

  return ret_code;
}
