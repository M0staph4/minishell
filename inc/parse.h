#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"
#include "token.h"

typedef struct t_red{
    char *file;
    int type;
}   s_red;

typedef struct t_parse{
    char **arg;
    s_red *red;
    struct s_parse *next;
}   s_parse;
#endif