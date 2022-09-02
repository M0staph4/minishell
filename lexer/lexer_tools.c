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

char	*get_char_as_string(t_lexer *lexer)
{
	char	*str;

	str = malloc(2);
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}

t_token	*advance_token(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

char	*join_char(t_lexer *lexer, char *value)
{
	char	*s;

	s = get_char_as_string(lexer);
	value = ft_strjoin(value, s);
	free(s);
	lexer_advance(lexer);
	return (value);
}
