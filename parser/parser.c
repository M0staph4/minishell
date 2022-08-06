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
	i = 0;
	new_args = malloc(sizeof(char *) * (count + 2));
	while(i < count)
	{
		new_args[i] = args[i];
		i++;
	}
	free(args);
	new_args[i++] = token->content;
	new_args[i] = NULL;
	return (new_args);
}

void add_parse(t_token *token, t_parser **parse)
{
	if(token->type == TOKEN_STR)
	{
		if(!(*parse)->cmd)
			(*parse)->cmd = ft_strdup(token->content);
		(*parse)->args = add_args_to_list((*parse)->args, token);
	}
	if(token->type == TOKEN_PIPE)
	{
		parser_add_back(parse, new_parse());
		(*parse) = (*parse)->next;
	}
	
}

void lexing(char *line, t_token *token)
{
	t_lexer *lexer;
	t_parser *parse;
	parse = new_parse();
	
	lexer = init_lexer(line);
	if(lexer)
	{
		while (lexer->c)
		{
			token = get_next_token(lexer);
			add_parse(token, &parse);
		}
	}
}
