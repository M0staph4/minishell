#include "../inc/header.h"

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
	new_args[i++] = ft_strdup(token->content);
	new_args[i] = NULL;
	free(token->content);
	return (new_args);
}

t_parser *add_parse(t_parser *parse, t_token *token, t_vr_tools *tools)
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
		tmp = new_parse(tools->cmd , tools->args, tools->red);
		parser_add_back(&parse, tmp);
		tools->red = NULL;
		tools->cmd = NULL;
		tools->args = NULL;
	}
	return(parse);
}

t_redirection *add_red_to_list(t_token *token, t_vr_tools *tools)
{
	t_redirection *red;
	red = new_red(token->type, token->content);
	red_add_back(&tools->red, red);
	return(tools->red);
}

t_vr_tools *init_tools()
{
	t_vr_tools *tools;
	tools = malloc(sizeof(t_vr_tools));
	tools->red = NULL;
	tools->cmd = NULL;
	tools->args = NULL;
	return(tools);
}

t_parser *lexing(char *line, t_token *token, t_env_list *env)
{
	t_lexer *lexer;
	t_parser *parse;
	t_vr_tools *tools;

	parse = NULL;
	tools = init_tools();
	lexer = init_lexer(line);
	int x = 0;
	if(lexer)
	{
		while (lexer->c)
		{
			token = get_next_token(lexer, env);
			if(token)
			{
				x = 1;
				if(token->type == TOKEN_REDIN || token->type == TOKEN_REDOUT || token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC)
					tools->red = add_red_to_list(token, tools);
				parse = add_parse(parse, token, tools);
				free(token);
			}
		}
		if(x && !lexer->c)
			parser_add_back(&parse, new_parse(tools->cmd, tools->args, tools->red));
		free(tools->cmd);
		free(tools);
		free(lexer);

	}
	return(parse);
}
