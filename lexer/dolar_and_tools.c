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

char *dolar(t_lexer *lexer ,t_env_list *env, char *value)
{
	char *join;
	char *dolar;

	dolar = add_dolar(lexer);
	join = join_dolar(dolar, env);
	if(join)
		value = ft_strjoin(value, join);
	free(join);
	free(dolar);
	return (value);
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
	s[j] = '\0';
	free(value);
	return(s);
}

char *add_dolar(t_lexer *lexer)
{
	char *value;

	value = ft_strdup("");
	if(lexer->c == '$')
		lexer_advance(lexer);
	if(lexer->c  == '?')
	{
		free(value);
		lexer_advance(lexer);
		return(ft_strdup("?"));
	}
	if(lexer->c == '"' || lexer->c == '\'')
	{
		free(value);
		return(NULL);
	}
	while ((lexer->c != '\0') && (ft_isalpha(lexer->c) || lexer->c == '_' || ft_isalnum(lexer->c)))
		value = join_char(lexer, value);
	return(value);
}

char *join_dolar(char *dolar, t_env_list *env)
{
	printf("%d-----\n",exit_status);
	if(!dolar)
		return(NULL);
	if(get_env(&env, dolar))
		return(ft_strdup(get_env(&env, dolar)));
	else if(!dolar[0])
	 	return(ft_strdup("$"));
	else if(dolar[0] == '?' && !dolar[1])
		return(ft_itoa(exit_status));
	return(NULL);
}

char *add_dolar_and_after_q(t_lexer *lexer, t_env_list *env)
{
	char *value;

	value = ft_strdup("");
	while(!sp_c(lexer->c) || lexer->c == '$')
	{
		if(lexer->c == '$')
			value = dolar(lexer, env, value);
		if(!sp_c(lexer->c))
			value = join_char(lexer, value);
	}
	return(value);
}