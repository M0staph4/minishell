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
	cnt_args = malloc(sizeof(int *) * (lexer->nb_pipe + 1));
	while (lexer->c)
	{
		token = get_next_token(lexer);
		if(token->type == TOKEN_STR)
			x++;
		if(token->type == TOKEN_PIPE)
		{
			cnt_args[i] = x;
			i++;
			x = 0;
		}
	}
	if(lexer->nb_pipe == 1 || !lexer->c)
		cnt_args[i++] = x;
	cnt_args[i] = 0;
	return(cnt_args);
}

void	add_parse(t_parser *parse, char **args, int cnt_args, t_token *token, int y, int p, char c)
{
	t_redirection *red;

	red = malloc(sizeof(t_redirection) * 100);
	if(token->type == TOKEN_REDIN || token->type == TOKEN_REDOUT || token->type == TOKEN_APPEND)
		red_add_back(&red, new_red(token->type, token->content));
	int x = 0;
	while(args[x] )
	{
		printf("----f---%s---\n",args[x]);
		x++;
	}
	if(token->type == TOKEN_PIPE)
	{
		args[y] = NULL;
		parser_add_back(&parse, new_parse(args, red));
		args = (char **)malloc(sizeof(char *) * (cnt_args + 1));
	}
	if(p == 1 || !c)
	{
		args[y] = NULL;
		parser_add_back(&parse, new_parse(args, red));
	}
}

void	lexing(char *line, t_token *token)
{
	t_lexer		*lexer;
	int x;
	int y;
	char **args;
	int *cnt_args;
	t_parser *parse;

	y = 0;
	lexer = init_lexer(line);
	parse = malloc (sizeof(t_parser));
	cnt_args = count_args(line, token);
	if(lexer)
	{
		x = 0;
		args = (char **)malloc(sizeof(char *) * (cnt_args[x] + 1));
		while(lexer->c)
		{
			token = get_next_token(lexer);
			if(token->type == TOKEN_STR)
			{
				args[y] = token->content;
				y++;	
			}
			if(token->type == TOKEN_PIPE)
			{
				add_parse(parse, args, cnt_args[x], token, y, lexer->nb_pipe, lexer->c);
				free_array(args);
				x++;
				y = 0;
			}
		}
		if(!lexer->c || lexer->nb_pipe == 1)
		{
			add_parse(parse, args, cnt_args[x], token, y, lexer->nb_pipe, lexer->c);
			if(lexer->nb_pipe == 1)
				free_array(args);
		}
	}
}
