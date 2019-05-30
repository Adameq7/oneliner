#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "oneliner.h"

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
//const char op_not_string[] = "NOT";
const char op_equal_string[] = "EQUAL";
const char op_less_string[] = "LESS";
const char op_greater_string[] = "GREATER";

const char operators[]="+-*/&|=<>";

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
//  if(!strncmp(name, op_not_string, 3)){new_token->type = _operator; new_token->type_2.operator_type = _not; return 1;};
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
