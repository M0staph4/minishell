#include "../inc/lexer.h"
#include "../inc/header.h"
#include "../inc/token.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

t_lexer *init_lexer(char *line)
{
	t_lexer *lexer;

	lexer = malloc(sizeof(t_lexer));
	lexer->line = line;
	lexer->pos = 0;
	lexer->nb_pipe = 1;
	lexer->c = lexer->line[lexer->pos];
	return (lexer);
}

t_token *get_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0')
	{
		if (lexer->c == ' ')
			lexer_skip_whitespaces(lexer);
		else if (lexer->c == '"')
			return (collect_string(lexer));
		else if(lexer->c == '\'')
			return (collect_string(lexer));
		else if (lexer->c == '|')
		{
			lexer->nb_pipe += 1;
			return (advance_token(lexer, init_token(TOKEN_PIPE, get_char_as_string(lexer))));
		}
		else if (lexer->c == '<')
		{
			lexer_advance(lexer);
			if(lexer->c == '<')
				return(collect_apn_hrd(lexer, TOKEN_HEREDOC));
			return (collect_red(lexer, TOKEN_REDIN));
		}
		else if (lexer->c == '>')
		{
			lexer_advance(lexer);
			if(lexer->c == '>')
				return(collect_apn_hrd(lexer, TOKEN_APPEND));
			return (collect_red(lexer, TOKEN_REDOUT));
		}
		else
			return (collect_cmd(lexer));
	}
	return(NULL);
}

