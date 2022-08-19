#include "../inc/lexer.h"
#include "../inc/header.h"
#include "../inc/token.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

char *join_to_join(t_lexer *lexer, char c)
{
	char *value;
	char *s;

	value = ft_strdup("");
	lexer_advance(lexer);
	while(lexer->c != c && lexer->c != '\0')
	{
		s = get_char_as_string(lexer);
		value = ft_strjoin(value, s);
		
		lexer_advance(lexer);
	}
	return(value);
}

char *add_value(char *value)
{
	int i;
	int j;
	char *s;
	j = 0;
	i = 0;
	while(value[i])
	{
		if(value[i] == 2)
			j++;
		i++;
	}
	s = malloc(i - j + 1);
	i = 0;
	j = 0;
	while(value[i])
	{
		if(value[i] != 2)
			s[j++] = value[i];
		i++;
	}
	free(value);
	s[j] = '\0';
	return(s);
}

t_token *collect_cmd(t_lexer *lexer)
{
	char *value;
	char *s;
	char *join;

	join = ft_strdup("");
	value = ft_strdup("");
	while (lexer->c != ' ' && lexer->c != '\0' && lexer->c != '|' && lexer->c != '>' && lexer->c != '<')
	{
		if(lexer->c != '"' && lexer->c != '\'')
		{
			s = get_char_as_string(lexer);
			value = ft_strjoin(value, s);
		}
		lexer_advance(lexer);
		if(lexer->c == '"' || lexer->c == '\'')
		{
			join = ft_strjoin(join, join_to_join(lexer, lexer->c));
			value = ft_strjoin(value, join);
		}
		free(join);
	}
	value = add_value(value);
	return(init_token(TOKEN_STR, value));
}

t_token *collect_red(t_lexer *lexer, int i)
{
	char *value;
	char *s;
	char *join;

	join = ft_strdup("");
	value = ft_strdup("");
	while (lexer->c == ' ')
		lexer_advance(lexer);
	while (lexer->c != '\0' && lexer->c != ' ' && lexer->c != '<' && lexer->c != '>' && lexer->c != '|')
	{
		if(lexer->c != '"' && lexer->c != '\'')
		{
			s = get_char_as_string(lexer);
			value = ft_strjoin(value, s);
		}
		if(lexer->c == '"' || lexer->c == '\'')
		{
			join = ft_strjoin(join, join_to_join(lexer, lexer->c));
			value = ft_strjoin(value, join);
			free(join);
		}
		lexer_advance(lexer);
	}
	value = add_value(value);
	return(init_token(i, value));
}

t_token *collect_apn_hrd(t_lexer *lexer, int i)
{
	char *value;
	char *s;
	char *join;

	join = ft_strdup("");
	value = ft_strdup("");
	lexer_advance(lexer);
	while (lexer->c == ' ')
		lexer_advance(lexer);
	while (lexer->c != '\0' && lexer->c != ' ' && lexer->c != '<' && lexer->c != '>' && lexer->c != '|')
	{
		if(lexer->c != '"' && lexer->c != '\'')
		{
			s = get_char_as_string(lexer);
			value = ft_strjoin(value, s);
		}
		if(lexer->c == '"' || lexer->c == '\'')
		{
			join = ft_strjoin(join, join_to_join(lexer, lexer->c));
			value = ft_strjoin(value, join);
			free(join);
		}
		lexer_advance(lexer);
	}
	value = add_value(value);
	return(init_token(i, value));
}

t_token *collect_string(t_lexer *lexer)
{
	char *value;
	char *join;
	char *s;

	join = ft_strdup("");
	value = ft_strdup("");
	while (lexer->c != '|' && lexer->c != '>' && lexer->c != '<' && lexer->c != '\0' && lexer->c != ' ')
	{
		if(lexer->c != '"' && lexer->c != '\'')
		{
			s = get_char_as_string(lexer);
			value = ft_strjoin(value, s);
		}
		if(lexer->c == '"' || lexer->c == '\'')
		{
			join = ft_strjoin(join, join_to_join(lexer, lexer->c));
			value = ft_strjoin(value, join);
			free(join);
		}
		lexer_advance(lexer);
	}
	value = add_value(value);
	return(init_token(TOKEN_STR, value));
}