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
t_token *collect_red(t_lexer *lexer, int i, t_env_list *env);
int ft_syntax_error(char *line);
int find_second_one(char *line, int pos);
t_token *collect_apn_hrd(t_lexer *lexer, int i);
char *add_value(char *value);
char *add_all(char *old_value, char c, t_lexer *lexer, t_env_list *env);
int sp_c(char c);
char *add_dolar(t_lexer *lexer);
char *add_dolar_token(char *dolar, t_env_list *env, char c);
char *add_dolar_and_after_q(t_lexer *lexer, t_env_list *env);
#endif