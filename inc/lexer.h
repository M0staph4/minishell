#ifndef LEXER_H
#define LEXER_H
#include "header.h"
#include "struct.h"


t_lexer *init_lexer(char *line);
void	lexer_advance(t_lexer *lexer);
void	lexer_skip_whitespaces(t_lexer *lexer);
t_token *get_next_token(t_lexer *lexer, t_env_list *env);
t_token *collect_string(t_lexer *lexer, t_env_list *env);
char    *get_char_as_string(t_lexer *lexer);
t_token *advance_token(t_lexer *lexer, t_token *token);
t_token *collect_cmd(t_lexer *lexer, t_env_list *env);
t_token *collect_red(t_lexer *lexer, int i);
int ft_syntax_error(char *line);
int find_second_one(char *line, int pos);
t_token *collect_apn_hrd(t_lexer *lexer, int i);
#endif