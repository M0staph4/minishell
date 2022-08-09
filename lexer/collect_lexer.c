#include "../inc/lexer.h"
#include "../inc/header.h"
#include "../inc/token.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

t_token *collect_cmd(t_lexer *lexer)
{
	char *value;
	char *s;

	value = malloc(1);
	value[0] = '\0';
	while (lexer->c != ' ' && lexer->c != '\0' && lexer->c != '|' && lexer->c != '>' && lexer->c != '<')
	{
		s = get_char_as_string(lexer);
		value = ft_strjoin(value, s);
		lexer_advance(lexer);
		if(lexer->c == '"' || lexer->c == '\'')
			lexer_advance(lexer);
	}
	return(init_token(TOKEN_STR, value));
}

t_token *collect_string_sngl(t_lexer *lexer)
{
	char *value;
	char *s;

	value = malloc(1);
	value[0] = '\0';
	if (lexer->c == '\'')
		lexer_advance(lexer);
	while (lexer->c != '\'' && lexer->c != '\0' && lexer->c != ' ')
	{
		s = get_char_as_string(lexer);
		value = ft_strjoin(value, s);
		lexer_advance(lexer);
		if(lexer->c == '"' && lexer->c == '\'' && lexer->c != '\0')
			lexer_advance(lexer);
	}
	lexer_advance(lexer);
	return(init_token(TOKEN_STR, value));
}

t_token *collect_red(t_lexer *lexer, int i)
{
	char *value;
	char *s;

	value = malloc(1);
	value[0] = '\0';
	while (lexer->c == ' ')
		lexer_advance(lexer);
	while (lexer->c != '\0' && lexer->c != ' ' && lexer->c != '<' && lexer->c != '>')
	{
		s = get_char_as_string(lexer);
		value = ft_strjoin(value, s);
		lexer_advance(lexer);
		if(lexer->c == '"' && lexer->c == '\'')
			lexer_advance(lexer);
	}
	return(init_token(i, value));
}

t_token *collect_apn_hrd(t_lexer *lexer, int i)
{
	char *value;
	char *s;

	value = malloc(1);
	value[0] = '\0';
	lexer_advance(lexer);
	while (lexer->c == ' ')
		lexer_advance(lexer);
	while (lexer->c != '\'' && lexer->c != '\0' && lexer->c != ' ' && lexer->c != '<' && lexer->c != '>')
	{
		s = get_char_as_string(lexer);
		value = ft_strjoin(value, s);
		lexer_advance(lexer);
		if(lexer->c == '"' && lexer->c == '\'')
			lexer_advance(lexer);
	}
	lexer_advance(lexer);
	return(init_token(i, value));
}
t_token *collect_string(t_lexer *lexer)
{
	char *value;
	char *s;

	value = malloc(1);
	value[0] = '\0';
	while (lexer->c == '"')
		lexer_advance(lexer);
	while (lexer->c != '"' && lexer->c != '\0')
	{
		s = get_char_as_string(lexer);
		value = ft_strjoin(value, s);
		lexer_advance(lexer);
		while(lexer->c == '"' && lexer->c != '\0' && lexer->c == ' ')
			lexer_advance(lexer);
	}
	lexer_advance(lexer);
	return(init_token(TOKEN_STR, value));
}