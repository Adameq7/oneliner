#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <getopt.h>
#include "oneliner.h"

int main(int argc, char **argv)
{
  char tree_flag = 0;

  while(1)
  {
    static struct option long_options[] =
    {
      {"--tree", required_argument, 0, 't'},
      {0, 0, 0, 0}
    };

    int option_index = 0, c;

    c = getopt_long(argc, argv, "t", long_options, &option_index);

    if(c == -1)
      break;

    switch(c)
    {
      case 't':
        tree_flag = 1;
      break;
      case '?':
      break;
      default:
        abort();
    }
  }
  char *line;

  int ret_code = 0, 
      token_number = 0;

  func functions[MAX_FUNC_NUM];
  int func_num = 0;

  var variables[MAX_VAR_NUM];
  int var_num = 0;

  token tokens[1024];
  double memory[MEM_SIZE];
  void *pointers[1024];
  int pointer_num = 0;

  node *root; 
  double res;

  while(1)
  {
    for(int i = 0; i < MEM_SIZE; i++)
      memory[i] = 0;

    token_number = 0;
    func_num = 0;
    var_num = 0;
    pointer_num = 0;

//    printf("---\n");
    line = readline(NULL);

    if(line == NULL)
     break;

    printf("\n------------BEGIN PARSING:------------\n");
    parse_line(line, tokens, &token_number);
    printf("\n------------END PARSING.------------\n");

    printf("\n------------BEGIN BUILDING TREE:------------\n");
    root = build_tree(tokens, token_number, functions, &func_num, variables, &var_num, pointers, &pointer_num);
    printf("\n------------END BUILDING TREE.------------\n");

    if(tree_flag)
    {
      printf("\n------------BEGIN PRINTING TREE:------------\n");
      print_tree(root, 0);
      printf("\n------------END PRINTING TREE.------------\n");
    }

    var_num = 0;

    printf("\n------------BEGIN EXECUTION:------------\n");
    res = execute(is_function("main", functions, func_num)->func_decl_node->data.s_node_func_decl.body, functions, func_num, variables, &var_num, NULL, memory);
    printf("\n------------END EXECUTION.------------\n");

    for(int i = 0; i < token_number; i++)
      free(tokens[i].name);
    for(int i = pointer_num - 1; i >= 0; i--)
      free(pointers[i]);
    free(line);
  }

  return ret_code;
}
