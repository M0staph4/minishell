#include "../inc/header.h"
#include "../inc/parser.h"
#include "../inc/token.h"

void free_array(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

int *count_args(char *line, t_token *token)
{
	t_lexer *lexer;
	int x;
	int i;
	int *cnt_args;

	i = 0;
	x = 0;
	lexer = init_lexer(line);
	cnt_args = malloc(sizeof(int) * (lexer->nb_pipe + 1));
	while (lexer->c)
	{
		token = get_next_token(lexer);
		if(token->type == TOKEN_STR)
			x++;
		if(token->type == TOKEN_PIPE)
		{
			cnt_args[i] = x;
			x = 0;
			i++;
		}
	}
	if(x){
	cnt_args[i] = x;i++;}
	cnt_args[i] = '\0';
	return(cnt_args);
}

void	add_parse(t_parser *parse, char **args, int cnt_args, t_token *token, int y)
{
	t_redirection *red;
	// t_parser *tmp;

	red = malloc(sizeof(t_redirection) * 100);
	if(token->type == TOKEN_PIPE)
	{
		args[y] = NULL;
		parser_add_back(parse, new_parse(args[0], args, red));
		free_array(args);
		args = (char **)malloc(sizeof(char *) * (cnt_args + 1));
	}
	else if(token->type == TOKEN_STR)
	{
		args[y] = NULL;
		parser_add_back(parse, new_parse(args[0], args, red));
		free_array(args);
	}
	if(token->type == TOKEN_REDIN || token->type == TOKEN_REDOUT || token->type == TOKEN_APPEND)
		red_add_back(&red, new_red(token->type, token->content));
}

void	lexing(char *line, t_token *token)
{
	t_lexer		*lexer;
	int x;
	int y;
	char **args;
	int *cnt_args;
	t_parser parse;

	y = 0;
	lexer = init_lexer(line);
	cnt_args = count_args(line, token);
	if(lexer)
	{
		x = 0;
		args = (char **)malloc(sizeof(char *) * (cnt_args[x] + 1));
		while(lexer->c)
		{
			token = get_next_token(lexer);
			if(token->type == TOKEN_PIPE)
			{
				add_parse(&parse, args, cnt_args[x], token, y);
				printf("---- %s\n", parse.next->args[1]);
				x++;
				y = 0;
			}
			if(token->type == TOKEN_STR)
				args[y++] = token->content;
		}
		add_parse(&parse, args, cnt_args[x], token, y);
	}
}
