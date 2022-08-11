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

int count_args(char **args)
{
	int i;
	i = 0;

	if(args)
	{
		while(args[i])
			i++;
	}
	return(i);
}

char **add_args_to_list(char **args, t_token *token)
{
	char **new_args;
	int i;
	int count;

	count = count_args(args);
	i = -1;
	new_args = malloc(sizeof(char *) * (count + 2));
	while(++i < count)
		new_args[i] = args[i];
	free(args);
	new_args[i++] = token->content;
	new_args[i] = NULL;
	return (new_args);
}

t_parser *add_parse(t_parser *parse, t_token *token, t_vr_tools *tools, t_redirection *redirection)
{
	t_parser *tmp;
	if(token->type == TOKEN_STR)
	{
		if(!tools->cmd)
			tools->cmd = ft_strdup(token->content);
		tools->args = add_args_to_list(tools->args , token);
	}
	else if(token->type == TOKEN_PIPE)
	{
		tmp = new_parse(tools->cmd , tools->args, redirection);
		parser_add_back(&parse, tmp);
		tools->cmd = NULL;
		tools->args = NULL;
	}
	return(parse);
}

t_redirection *add_red_to_list(t_token *token, t_redirection *redirection)
{
	t_redirection *red;
	red = new_red(token->type, token->content);
	red_add_back(&redirection, red);
	return(redirection);
}

t_parser *lexing(char *line, t_token *token)
{
	t_lexer *lexer;
	t_parser *parse;
	t_vr_tools tools;
	t_redirection *redirection;

	parse = NULL;
	redirection = NULL;
	tools.cmd = NULL;
	tools.args = NULL;
	lexer = init_lexer(line);
	int x = 0;
	if(lexer)
	{
		while (lexer->c)
		{
			token = get_next_token(lexer);
			if(token)
			{
				x++;
				if(token->type == TOKEN_REDIN || token->type == TOKEN_REDOUT || token->type == TOKEN_APPEND)
					redirection = add_red_to_list(token, redirection);
				parse = add_parse(parse, token, &tools, redirection);
			}
		}
		if(x && !lexer->c)
			parser_add_back(&parse, new_parse(tools.cmd, tools.args, redirection));
	}
	int i;
	while(parse)
	{
		i = -1;
		if(parse->cmd)
			printf("cmd : %s\n", parse->cmd);
		while(parse->args[++i])
			printf("args : %s\n", parse->args[i]);
		while(parse->red)
		{
			printf("red : %s\n", parse->red->file);
			parse->red = parse->red->next;
		}
		parse = parse->next;
	}
	return(parse);
}
