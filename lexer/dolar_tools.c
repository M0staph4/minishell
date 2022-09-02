#include "../inc/header.h"

char	*dolar_q(t_lexer *lexer, t_env_list *env, char *value)
{
	char	*join;
	char	*dolar;

	while (lexer->c != '"')
	{
		if (lexer->c == '$')
		{
			lexer_advance(lexer);
			if (lexer->c == '"')
				join = ft_strdup("$");
			else
			{
				dolar = add_dolar(lexer);
				join = join_dolar(dolar, env);
				free(dolar);
			}
			if (join)
				value = ft_strjoin(value, join);
			free(join);
		}
		else
			value = join_char(lexer, value);
	}
	return (value);
}

char	*add_dolar(t_lexer *lexer)
{
	char	*value;

	value = ft_strdup("");
	if (lexer->c == '$')
		lexer_advance(lexer);
	if (lexer->c == '?')
	{
		free(value);
		lexer_advance(lexer);
		return (ft_strdup("?"));
	}
	if (lexer->c == '"' || lexer->c == '\'')
	{
		free(value);
		return (NULL);
	}
	while ((lexer->c != '\0') && (ft_isalpha(lexer->c)
			|| lexer->c == '_' || ft_isalnum(lexer->c)))
		value = join_char(lexer, value);
	return (value);
}
