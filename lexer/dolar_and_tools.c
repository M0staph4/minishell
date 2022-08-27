#include "../inc/header.h"

int sp_c(char c)
{
	char *p;
	int i;

	i = 0; 
	p = "|><\" \'$";
	if(!c)
		return(1);
	while(p[i])
	{
		if(p[i] == c)
			return(1);
		i++;
	}
	return(0);
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

char *add_dolar(t_lexer *lexer)
{
	char *value;
	char *s;

	value = ft_strdup("");
	lexer_advance(lexer);
	while ((lexer->c != '\0') && (ft_isalpha(lexer->c) || lexer->c == '_' || ft_isalnum(lexer->c)))
	{
		s = get_char_as_string(lexer);
		value = ft_strjoin(value, s);
		free(s);
		lexer_advance(lexer);
	}
	return(value);
}

char *add_dolar_token(char *dolar, t_env_list *env, char c)
{
	if(get_env(&env, dolar))
		return(get_env(&env, dolar));
	else if(!dolar[0] && c != '"')
	 	return(ft_strdup("$"));
	else if(dolar[0] == '?' && !dolar[1])
		return(ft_strdup("$?"));
	else
		return(NULL);
}

char *add_dolar_and_after_q(t_lexer *lexer, t_env_list *env)
{
	char *value;
	char *join;
	char *s;

	value = ft_strdup("");
	while(!sp_c(lexer->c) || lexer->c == '$')
	{
		if(lexer->c == '$')
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
			free(s);
			lexer_advance(lexer);
		}
	}
	return(value);
}