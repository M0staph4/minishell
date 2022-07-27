#include "../inc/header.h"
#include "../inc/parser.h"
#include "../inc/token.h"

// int *count_args_pipe(char *line, int y)
// {
// 	int *args_in_pipe;
// 	int i;
// 	int x;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	x = 1;
// 	args_in_pipe = malloc(sizeof(int) * y + 1);
// 	while(line[j])
// 	{
// 		if(line[j] == ' ')
// 		{
// 			while(line[j] == ' ')
// 				j++;
// 			//x += 1;
// 		}
// 		else if(line[j] == '<' && line[j + 1] == '<')
// 			x += 1;
// 		else if(line[j] == '>' && line[j + 1] == '>')
// 			x += 1;
// 		else if(line[j] == '<')
// 			x += 1;
// 		else if(line[j] == '>')
// 			x += 1;
// 		else if (line[j] == '|')
// 		{
// 			printf("%d-----\n", x);
// 			args_in_pipe[i] = x;
// 			x = 0;
// 			i++;
// 		}
// 		j++;
// 	}
// 	args_in_pipe[i] = x;
// 	return (args_in_pipe);
// }

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


void	lexing(char *line, t_token *token)
{
	//t_lexer		*lexer;
	t_lexer		*lexers;
	int i;
	int x;
	int y;
	char **args;

	x = 0;
	i = 0;
	y = 0;
	lexers = init_lexer(line);
	if(lexers)
	{
		x = 0;
		i = lexers->nb_args[x];
		args = (char **)malloc(sizeof(char *) * i + 1);
		while(lexers->c)
		{
			token = get_next_token(lexers);
			i = lexers->nb_args[x];
			if(token->type == TOKEN_PIPE)
			{
				x++;
				i = lexers->nb_args[x];
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
			if(token->type == TOKEN_REDIN || token->type == TOKEN_REDOUT || token->type == TOKEN_APPEND)
				printf("type = %d, content = %s\n", token->type, token->content);
			}
		args[y] = NULL;
	}
}

