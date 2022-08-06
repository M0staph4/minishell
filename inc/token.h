#ifndef TOKEN_H
#define TOKEN_H
#include "lexer.h"

typedef struct s_token
{
    char *content;
    enum  {
    TOKEN_STR,
    TOKEN_PIPE,
    TOKEN_REDIN,
    TOKEN_REDOUT,
    TOKEN_HEREDOC,
    TOKEN_APPEND,
    TOKEN_NULL,
    }type;
}   t_token;

t_token *init_token(int type, char *value);

#endif