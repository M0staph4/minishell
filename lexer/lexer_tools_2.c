#include "../inc/header.h"

char	*join_to_join(t_lexer *lexer, char c, t_env_list *env)
{
	char	*value;
	int		q;

	q = 0;
	value = ft_strdup("");
	lexer_advance(lexer);
	if (c == '"')
		q = 1;
	while (lexer->c != c && lexer->c != '\0')
	{
		if (lexer->c == '$' && q == 1)
			value = dolar_q(lexer, env, value);
		if (lexer->c != c)
			value = join_char(lexer, value);
	}
	return (value);
}

char	*add_all_in_value(char *old_value, char c,
		t_lexer *lexer, t_env_list *env)
{
	char	*value;
	char	*s;
	char	*join;

	value = ft_strdup("");
	if (c != '"' && c != '\'')
	{
		if (c == '$')
			value = dolar(lexer, env, value);
		if (!sp_c(lexer->c))
		{
			s = get_char_as_string(lexer);
			value = ft_strjoin(value, s);
			free(s);
		}
	}
	join = ft_strjoin(old_value, value);
	free(value);
	return (join);
}

char	*add_all(char *old_value, char c, t_lexer *lexer, t_env_list *env)
{
	char	*value;
	char	*demo;
	char	*v;

	v = NULL;
	value = ft_strdup("");
	demo = NULL;
	if ((c == '$') || (c != '"' && c != '\''))
			demo = add_dolar_and_after_q(lexer, env);
	if (demo)
	{
		value = ft_strjoin(value, demo);
		free(demo);
	}
	if (value)
	{
		v = ft_strjoin(old_value, value);
		free(value);
	}
	else
	{
		free(value);
		return (old_value);
	}
	return (v);
}
