#include "../inc/header.h"


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

t_token *red_token(t_lexer *lexer, t_env_list *env)
{
	char c;

	c = lexer->c;
	lexer_advance(lexer);
	if(lexer->c == '<')
		return(collect_apn_hrd(lexer, TOKEN_HEREDOC));
	else if(lexer->c == '>')
		return(collect_red(lexer, TOKEN_APPEND, env));
	else if(c == '>')
		return (collect_red(lexer, TOKEN_REDOUT, env));
	else if(c == '<')
		return (collect_red(lexer, TOKEN_REDIN, env));
	return(NULL);
}

t_token *get_next_token(t_lexer *lexer, t_env_list *env)
{
	while (lexer->c != '\0')
	{
		if (lexer->c == ' ')
			lexer_skip_whitespaces(lexer);
		else if (lexer->c == '"' || lexer->c == '\'')
			return (collect_string(lexer, env));
		else if (lexer->c == '|')
			return (advance_token(lexer, init_token(TOKEN_PIPE, get_char_as_string(lexer))));
		else if (lexer->c == '<' || lexer->c == '>')
			return(red_token(lexer, env));
		else
			return (collect_cmd(lexer, env));
	}
	return(NULL);
}

