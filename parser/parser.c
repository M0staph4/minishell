#include "../inc/header.h"
#include "../inc/parser.h"

// void start_parse(t_token *token, t_lexer *lexer)
// {
// 	char **args;
// 	int x = 0;
// 	int i = 0;
// 	args = malloc(sizeof(char *) * lexer->nb_pipe + 1);
// 		if (token->type == TOKEN_STR)
// 			args[x][i++] = token->content;
	
// }

void	lexing(char *line, t_token *token)
{
	t_lexer		*lexer;
	int i;
	int x;
	char **args;

	x = 0;
	i = 0;
	lexer = init_lexer(line);
	args = (char **)malloc(sizeof(char *) * lexer->nb_pipe + 1);
	if(lexer)
	{
		while(lexer->c)
		{
			token = get_next_token(lexer);
			printf("%s    %d\n", token->content, token->type);
			i++;
			if(token->type == TOKEN_REDIN || token->type == TOKEN_REDOUT
				|| token->type == TOKEN_HEREDOC || token->type == TOKEN_APPEND)
				i -= 2;
			if (lexer->nb_pipe == 1)
				count_pipe[x] = i;
			if(token->type == TOKEN_PIPE)
			{
				count_pipe[x] = i;
				i = -1;
				x++;
			}
		}
		i = 0;
		x = 0;
		while(x < lexer->nb_pipe)
		{
			printf("%s\n", args[x]);
			x++;
		}
		// lexer_advance(lexer);
		// x = 0;
		// while(lexers->c)
		// {
		// 	token = get_next_token(lexers);
		// 	while(count_pipe[x]){
		// 	printf("%d----\n",count_pipe[x]);x++;}
		// }
	}
}

