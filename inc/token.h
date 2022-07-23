#ifndef TOKEN_H
#define TOKEN_H
#include "lexer.h"


typedef struct s_token
{
    char *content;
    enum  {
    TOKEN_STR,
    TOKEN_CMD,
    TOKEN_PIPE,
    TOKEN_REDIN,
    TOKEN_REDOUT,
    TOKEN_HEREDOC,
    TOKEN_APPEND,
    TOKEN_OPN,
    }type;
    struct s_token *next;
}   t_token;

t_token	*ft_newtoken(int type, char *value);
int	ft_tokensize(t_token *lst);
void	ft_tokenadd_back(t_token *lst, t_token *new);
void	ft_tokenadd_front(t_token *lst, t_token *new);
t_token	*ft_tokenlast(t_token *lst);

#endif