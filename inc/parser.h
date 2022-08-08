#ifndef PARSER_H
#define PARSER_H

typedef struct s_parser
{
    char *cmd;
    char **args;
    struct s_redirection *red;
    struct s_parser *next;
} t_parser;

typedef struct s_redirection
{
    int    type;
    char    *file;
    struct s_redirection *next;
} t_redirection;

//redirections
t_redirection	*new_red(int type, char *file);
int             red_size(t_redirection *lst);
void	red_add_back(t_redirection **lst, t_redirection *new);
void	red_add_front(t_redirection **lst, t_redirection *new);
t_redirection	*red_last(t_redirection *lst);

//parse 
t_parser	*new_parse(char *cmd , char ** args );

int	parse_size(t_parser *lst);
void	parser_add_back(t_parser **lst, t_parser *new);
void	parser_add_front(t_parser **lst, t_parser *new);
t_parser	*parser_last(t_parser **lst);
void lexing(char *line, t_token *token);


#endif