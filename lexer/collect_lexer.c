#include "../inc/header.h"

char *add_dolar(t_lexer *lexer)
{
	char *value;
	char *s;

	value = ft_strdup("");
	lexer_advance(lexer);
		while ( (lexer->c != '\0') && (ft_isalpha(lexer->c) || lexer->c == '_' || ft_isalnum(lexer->c)))
		{
			s = get_char_as_string(lexer);
			value = ft_strjoin(value, s);
			lexer_advance(lexer);
		}
	return(value);
}

char *add_dolar_token(char *dolar, t_env_list *env)
{
	if(get_env(&env, dolar))
		return(get_env(&env, dolar));
	else if(!dolar[0])
		return(ft_strdup("$"));
	else if(dolar[0] == '?' && !dolar[1])
		return(ft_strdup("$?"));
	else
		return(NULL);
}

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
			if(add_dolar_token(join, env))
				value = ft_strjoin(value, add_dolar_token(join, env));
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

char *add_value(char *value)
{
	int i;
	int j;
	char *s;
	j = 0;
	i = 0;
	while(value[i])
	{
		if(value[i] >= 1 && value[i] <= 5)
			j++;
		i++;
	}
	s = malloc(i - j + 1);
	i = 0;
	j = 0;
	while(value[i])
	{
		if(value[i] >= 6)
			s[j++] = value[i];
		i++;
	}
	free(value);
	s[j] = '\0';
	return(s);
}



t_token *collect_cmd(t_lexer *lexer, t_env_list *env)
{
	char *value;
	char *s;
	char *join;
	int i;
	i = 0;

	join = ft_strdup("");
	value = ft_strdup("");
	while (lexer->c != ' ' && lexer->c != '\0' && lexer->c != '|' && lexer->c != '>' && lexer->c != '<')
	{
		if(lexer->c != '"' && lexer->c != '\'')
		{
			if(lexer->c == '$')
			{
				join = add_dolar(lexer);
				if(add_dolar_token(join, env))
					value = ft_strjoin(value, add_dolar_token(join, env));
				if(lexer->c == '"' || lexer->c == '\'' || lexer->c == '$')
					i = 1;
				free(join);
			}
			if(!i){
			s = get_char_as_string(lexer);
			value = ft_strjoin(value, s);}
		}
		if(!i)
			lexer_advance(lexer);
		i = 0;
		if(lexer->c == '"' || lexer->c == '\'')
		{
			join = ft_strjoin(join, join_to_join(lexer, lexer->c, env));
			value = ft_strjoin(value, join);
			free(join);
		}
	}
	if(value)
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
			join = ft_strjoin(join, join_to_join(lexer, lexer->c, NULL));
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
			join = ft_strjoin(join, join_to_join(lexer, lexer->c, NULL));
			value = ft_strjoin(value, join);
			free(join);
		}
		lexer_advance(lexer);
	}
	value = add_value(value);
	return(init_token(i, value));
}

char *add_dolar_and_after_q(t_lexer *lexer, t_env_list *env)
{
	char *value;
	char *join;
	char *s;

	join = ft_strdup("");
	value = ft_strdup("");

	while(lexer->c != '|' && lexer->c != '>' && lexer->c != '<' && lexer->c != '\0' && lexer->c != ' ')
	{
		if(lexer->c == '$')
		{
			join = add_dolar(lexer);
			if(add_dolar_token(join, env))
				value = ft_strjoin(value, add_dolar_token(join, env));
			free(join);
		}
		if(lexer->c != '"' && lexer->c != '\'')
		{
			s = get_char_as_string(lexer);
			value = ft_strjoin(value, s);
		}
		lexer_advance(lexer);
	}
	return(value);
}

t_token *collect_string(t_lexer *lexer, t_env_list *env)
{
	char *value;
	char *demo;
	char *join;

	join = ft_strdup("");
	value = ft_strdup("");
	demo = NULL;
	while (lexer->c != '|' && lexer->c != '>' && lexer->c != '<' && lexer->c != '\0' && lexer->c != ' ')
	{
		
		if((lexer->c == '$') || (lexer->c != '"' && lexer->c != '\''))
			demo = add_dolar_and_after_q(lexer, env);
		if(demo)
		{
			value = ft_strjoin(value, demo);
			free(demo);
		}
		if(lexer->c == '"' || lexer->c == '\'')
		{
			join = ft_strjoin(join, join_to_join(lexer, lexer->c, env));
			value = ft_strjoin(value, join);
			free(join);
		}
		lexer_advance(lexer);
	}
	if(value)
		value = add_value(value);
	return(init_token(TOKEN_STR, value));
}