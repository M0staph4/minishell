#include "../inc/header.h"

t_token *init_token(int type, char *value)
{
    t_token *token;
    token = malloc(sizeof(t_token));
    token->content = value;
    token->type = type;
    return (token);
}
