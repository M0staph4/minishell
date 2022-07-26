#include "../inc/header.h"
#include "../inc/parser.h"

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

int *arg_in_pipe(t_lexer *lexer, t_token *token)
{
	int *args_in_pipe;
	int i;
	int x;

	i = 0;
	x = 0;
	args_in_pipe = malloc(sizeof(int) * lexer->nb_pipe);
	while(lexer->c)
	{
		token = get_next_token(lexer);
		i++;
		if(token->type == TOKEN_REDIN || token->type == TOKEN_REDOUT
			|| token->type == TOKEN_HEREDOC || token->type == TOKEN_APPEND)
			i -= 2;
		if (lexer->nb_pipe == 1)
			args_in_pipe[x] = i;
		if(token->type == TOKEN_PIPE || lexer->c == '\0') 
		{
			if (token->type == TOKEN_PIPE)
				i--;
			args_in_pipe[x] = i;
			i = 0;
			x++;
		}
	}
	return (args_in_pipe);
}

void	lexing(char *line, t_token *token)
{
	t_lexer		*lexer;
	t_lexer		*lexers;
	int i;
	int x;
	int y;
	char **args;
	int *args_in_pipe;

	x = 0;
	i = 0;
	y = 0;
	lexer = init_lexer(line);
	lexers = init_lexer(line);
	if(lexer)
	{
		
		args_in_pipe = arg_in_pipe(lexer, token);
		x = 0;
		i = 0;
		i = args_in_pipe[x];
		printf("ddddddd%d\n", i);
		args = (char **)malloc(sizeof(char *) * i + 1);
		while(lexers->c)
		{
			token = get_next_token(lexers);
			i = args_in_pipe[x];
			if(token->type == TOKEN_PIPE)
			{
				x++;
				i = args_in_pipe[x];
				args[y] = NULL;
				free_array(args);
				y = 0;
				args = (char **)malloc(sizeof(char *) * i + 1);
			}
			if(token->type == TOKEN_STR)
			{
				args[y] = token->content;
				y++;
			}
		}
		args[y] = NULL;
		y = 0;
		while(args[y])
		{
			printf("%s\n", args[y]);
			y++;
		}
	}
}

