#include <stdlib.h>
#include <stdio.h>
#include "oneliner.h"

void parse_line(char *line, token *tokens, int *token_number)
{
  int index1 = 0,
      index2 = 1;

  while(1)
  {
    if(DEBUG)
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

  if(DEBUG)
    for(int i = 0; i < *token_number; i++)
      printf(" - %s %d %d\n", tokens[i].name, tokens[i].type, tokens[i].type_2.keyword_type); 

  return;
}

