#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "oneliner.h"

#define DEBUG 1

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
