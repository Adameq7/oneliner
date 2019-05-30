#include <stdlib.h>
#include "oneliner.h"

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
