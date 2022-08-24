#include "../inc/header.h"

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0')
	{
		lexer->pos++;
		lexer->c = lexer->line[lexer->pos];
	}
}

void	lexer_skip_whitespaces(t_lexer *lexer)
{
	while (lexer->c == ' ')
		lexer_advance(lexer);
}

char *get_char_as_string(t_lexer *lexer)
{
	char *str;
	str = malloc(2);
	str[0] = lexer->c;
	str[1] = '\0';
	return(str);
}

t_token *advance_token(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

char *add_all(char *old_value, char c, t_lexer *lexer, t_env_list *env)
{
	char *value;
	char *demo;
	char *join;

	join = ft_strdup("");
	value = ft_strdup("");
	demo = NULL;
	if((c == '$') || (c != '"' && c != '\''))
			demo = add_dolar_and_after_q(lexer, env);
	if(demo)
	{
		value = ft_strjoin(value, demo);
		free(demo);
	}
	if(value)
		value = ft_strjoin(old_value, value);
	else
		return(old_value);
	return(value);
}