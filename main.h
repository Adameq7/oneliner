#define MAX_FUNC_NUM 128
#define MAX_VAR_NUM 1024
#define MAX_FUNC_ARG_NUM 16

typedef enum
{
  _EOF,
  _identifier,
  _keyword,
  _operator,
  _number,
  _string
} _token_type;

typedef struct
{
  char is_var;
  union
  {
    char *name;
    double val;
  } data;
} arg;

typedef enum
{
  _program_begin,
  _program_end,
  _func,
  _begin,
  _end,
  _while,
  _do,
  _done,
  _if,
  _else,
  _fi,
  _var,
  _set,
  _print,
  _return,
} _keyword_type;

typedef enum
{
  _add,
  _sub,
  _mult,
  _div,
  _and,
  _or,
  _not,
  _equal,
  _less,
  _greater
} _operator_type;

typedef struct
{
  _token_type type;

  union _type_2 
  {
    _keyword_type keyword_type;
    _operator_type operator_type;
  } type_2;

  char *name;
} token;

typedef struct node node;

struct node
{
  enum
  {
    node_body,        //_*
    node_func_decl,   //**
    node_while,       //**
    node_if,          //**
    node_var_decl,    //**
    node_var_set,     //*
    node_print        //*
  } type;

  union
  {
    struct
    {
      char *func_name;
      int arg_num;
      char **arg_name;
      node *body;
      char *ret_val;
    } s_node_func_decl;
    struct
    {
      char *condition;
      node *body;
    } s_node_while;
    struct
    {
      char *var_name;
      char type;
      union 
      {
        struct
        {
          char *name;
          arg *args;
          int arg_num;
        } func;
        struct
        {
          arg arg1;
          arg arg2;
          char operation;
        } operation;
        struct
        {
          arg arg1;
        } copy;
      } body;
    } s_node_var_set;
    struct
    { 
      char *var_name;
    } s_node_var_decl;
    struct
    {
      char is_arg;
      arg arg1;
      char *message;
    } s_node_print;
    struct
    {
      char *condition;
      node *lbody;
      node *rbody;
    } s_node_if;
  } data;

  node *next;
};

typedef struct
{
  char *name;
  node *func_decl_node;
} func;

typedef struct
{
  char *name;
  double val;
} var;
