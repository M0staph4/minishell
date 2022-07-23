#ifndef LEXER_H
#define LEXER_H
#include "token.h"

typedef struct s_lexer{
    char			c;
    char			*line;
    unsigned int	pos;
    int             q_pos;
    int             cunt_pp;
} t_lexer;

typedef struct s_parse{
    char *cmd;
    char *arg;
    char *ops;
    char *pipe;
    char *red;
    struct s_parse *next;
}   t_parse;

t_lexer *init_lexer(char *line);
void	lexer_advance(t_lexer *lexer);
void	lexer_skip_whitespaces(t_lexer *lexer);
void    get_next_token(t_lexer *lexer, t_token *token);
void    collect_string(t_lexer *lexer, t_token *token);
char    *get_char_as_string(t_lexer *lexer);
void    advance_token(t_lexer *lexer, t_token *token, t_token *tokens);
void	collect_cmd(t_lexer *lexer, t_token *token);
void    collect_red(t_lexer *lexer, t_token *token);
void	lexing(char *line, t_token *token);

#endif