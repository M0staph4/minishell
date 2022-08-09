#include "../inc/lexer.h"
#include "../inc/header.h"
#include "../inc/token.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

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