#include "../inc/header.h"

char *join_to_join(t_lexer *lexer, char c, t_env_list *env)
{
	char *value;
	char *s;
	char *join;
	int q;

	q = 0;
	value = ft_strdup("");
	join = ft_strdup("");
	if(c == '"')
		q = 1;
	lexer_advance(lexer);
	while(lexer->c != c && lexer->c != '\0')
	{
		if(lexer->c == '$' && q == 1)
		{
			join = add_dolar(lexer);
			if(add_dolar_token(join, env, lexer->c))
				value = ft_strjoin(value, add_dolar_token(join, env, lexer->c));
			free(join);
		}
		if(lexer->c != c)
		{
			s = get_char_as_string(lexer);
			value = ft_strjoin(value, s);
			lexer_advance(lexer);
		}
	}
	return(value);
}

char *add_all_in_value(char *old_value, char c, t_lexer *lexer, t_env_list *env)
{
	char *value;
	char *s;
	char *join;

	join = ft_strdup("");
	value = ft_strdup("");
	if(c != '"' && c != '\'')
	{
		if(c == '$')
		{
			join = add_dolar(lexer);
			if(add_dolar_token(join, env, lexer->c))
				value = ft_strjoin(value, add_dolar_token(join, env, lexer->c));
			free(join);
		}
		if(!sp_c(lexer->c))
		{
			s = get_char_as_string(lexer);
			value = ft_strjoin(value, s);
		}
	}
	value = ft_strjoin(old_value, value);
	return (value);
}

t_token *collect_cmd(t_lexer *lexer, t_env_list *env)
{
	char *value;
	char *join;
	int i;
	i = 0;

	value = ft_strdup("");
	join = ft_strdup("");
	while (lexer->c != ' ' && lexer->c != '\0' && lexer->c != '|' && lexer->c != '>' && lexer->c != '<')
	{
 		value = add_all_in_value(value, lexer->c, lexer, env);
		if(!sp_c(lexer->c) || i)
			lexer_advance(lexer);
		if(lexer->c == '"' || lexer->c == '\'')
		{
			i = 1;
			join = join_to_join(lexer, lexer->c, env);
			value = ft_strjoin(value, join);
			free(join);
		}
	}
	if(value)
		value = add_value(value);
	return(init_token(TOKEN_STR, value));
}

t_token *collect_red(t_lexer *lexer, int i, t_env_list *env)
{
	char *value;
	char *join;
	int x;

	x = 0;
	join = ft_strdup("");
	value = ft_strdup("");
	while (lexer->c == ' ')
		lexer_advance(lexer);
	while (lexer->c != '\0' && lexer->c != ' ' && lexer->c != '<' && lexer->c != '>' && lexer->c != '|')
	{
 		value = add_all_in_value(value, lexer->c, lexer, env);
		if(!sp_c(lexer->c) || x)
			lexer_advance(lexer);
		if(lexer->c == '"' || lexer->c == '\'')
		{
			x = 1;
			join = join_to_join(lexer, lexer->c, env);
			value = ft_strjoin(value, join);
			free(join);
		}
	}
	value = add_value(value);
	return(init_token(i, value));
}

t_token *collect_apn_hrd(t_lexer *lexer, int i, t_env_list *env)
{
	char *value;
	char *s;
	char *join;

	join = ft_strdup("");
	value = ft_strdup("");
	lexer_advance(lexer);
	if(i == TOKEN_APPEND)
		return(collect_red(lexer, i, env));
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
			join = join_to_join(lexer, lexer->c, NULL);
			value = ft_strjoin(value, join);
			free(join);
		}
		lexer_advance(lexer);
	}
	value = add_value(value);
	return(init_token(i, value));
}

t_token *collect_string(t_lexer *lexer, t_env_list *env)
{
	char *value;
	char *join;
	int i;

	i = 0;
	join = ft_strdup("");
	value = ft_strdup("");
	while (lexer->c != '|' && lexer->c != '>' && lexer->c != '<' && lexer->c != '\0' && lexer->c != ' ')
	{
		value = add_all(value, lexer->c, lexer, env);
		if(lexer->c == '"' || lexer->c == '\'')
		{
			i = 1;
			join = join_to_join(lexer, lexer->c, env);
			if(join)
				value = ft_strjoin(value, join);
			free(join);
		}
		if(!sp_c(lexer->c) || i)
			lexer_advance(lexer);
		i = 0;
	}
	value = add_value(value);
	return(init_token(TOKEN_STR, value));
}
