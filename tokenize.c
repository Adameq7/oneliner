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
const char newline_string[] = "NEWLINE";

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

  if((word[0] == '\'') && (word[length - 1] == '\'')){new_token->type = _string; return 1;};

  if(!strcmp(name, op_add_string)){new_token->type = _operator; new_token->type_2.operator_type = _add; return 1;};
  if(!strcmp(name, op_sub_string)){new_token->type = _operator; new_token->type_2.operator_type = _sub; return 1;};
  if(!strcmp(name, op_mult_string)){new_token->type = _operator; new_token->type_2.operator_type = _mult; return 1;};
  if(!strcmp(name, op_div_string)){new_token->type = _operator; new_token->type_2.operator_type = _div; return 1;};
  if(!strcmp(name, op_and_string)){new_token->type = _operator; new_token->type_2.operator_type = _and; return 1;};
  if(!strcmp(name, op_or_string)){new_token->type = _operator; new_token->type_2.operator_type = _or; return 1;};
//  if(!strncmp(name, op_not_string, 3)){new_token->type = _operator; new_token->type_2.operator_type = _not; return 1;};
  if(!strcmp(name, op_equal_string)){new_token->type = _operator; new_token->type_2.operator_type = _equal; return 1;};
  if(!strcmp(name, op_less_string)){new_token->type = _operator; new_token->type_2.operator_type = _less; return 1;};
  if(!strcmp(name, op_greater_string)){new_token->type = _operator; new_token->type_2.operator_type = _greater; return 1;};

  if(!strcmp(name, func_string)){new_token->type = _keyword; new_token->type_2.keyword_type = _func; return 1;};
  if(!strcmp(name, begin_string)){new_token->type = _keyword; new_token->type_2.keyword_type = _begin; return 1;};
  if(!strcmp(name, end_string)){new_token->type = _keyword; new_token->type_2.keyword_type = _end; return 1;};
  if(!strcmp(name, while_string)){new_token->type = _keyword; new_token->type_2.keyword_type = _while; return 1;};
  if(!strcmp(name, if_string)){new_token->type = _keyword; new_token->type_2.keyword_type = _if; return 1;};
  if(!strcmp(name, else_string)){new_token->type = _keyword; new_token->type_2.keyword_type = _else; return 1;};
  if(!strcmp(name, var_string)){new_token->type = _keyword; new_token->type_2.keyword_type = _var; return 1;};
  if(!strcmp(name, set_string)){new_token->type = _keyword; new_token->type_2.keyword_type = _set; return 1;};
  if(!strcmp(name, print_string)){new_token->type = _keyword; new_token->type_2.keyword_type = _print; return 1;};
  if(!strcmp(name, return_string)){new_token->type = _keyword; new_token->type_2.keyword_type = _return; return 1;};
  if(!strcmp(name, fi_string)){new_token->type = _keyword; new_token->type_2.keyword_type = _fi; return 1;};
  if(!strcmp(name, done_string)){new_token->type = _keyword; new_token->type_2.keyword_type = _done; return 1;};
  if(!strcmp(name, do_string)){new_token->type = _keyword; new_token->type_2.keyword_type = _do; return 1;};
  if(!strcmp(name, program_begin_string)){new_token->type = _keyword; new_token->type_2.keyword_type = _program_begin; return 1;};
  if(!strcmp(name, program_end_string)){new_token->type = _keyword; new_token->type_2.keyword_type = _program_end; return 1;};
  if(!strcmp(name, newline_string)){new_token->type = _keyword; new_token->type_2.keyword_type = _newline; return 1;};

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
