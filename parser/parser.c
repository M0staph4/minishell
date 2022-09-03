/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <mmoutawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 01:18:42 by mmoutawa          #+#    #+#             */
/*   Updated: 2022/09/03 01:18:43 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void	free_array(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

t_parser	*add_parse(t_parser *parse, t_token *token, t_vr_tools *tools)
{
	t_parser	*tmp;

	if (token->type == TOKEN_STR)
	{
		if (!tools->cmd)
			tools->cmd = ft_strdup(token->content);
		tools->args = add_args_to_list(tools->args, token);
	}
	else if (token->type == TOKEN_PIPE)
	{
		tmp = new_parse(tools->cmd, tools->args, tools->red);
		parser_add_back(&parse, tmp);
		free(tools->cmd);
		free(token->content);
		tools->red = NULL;
		tools->cmd = NULL;
		tools->args = NULL;
	}
	return (parse);
}

t_redirection	*add_red_to_list(t_token *token, t_vr_tools *tools)
{
	t_redirection	*red;

	red = new_red(token->type, token->content);
	red_add_back(&tools->red, red);
	return (tools->red);
}

void	free_staff(char *cmd, t_vr_tools *tools, t_lexer *lexer)
{
	free(cmd);
	free(tools);
	free(lexer);
}

t_parser	*lexing(char *line, t_token *token,
			t_env_list *env, t_vr_tools *tools)
{
	t_lexer		*lexer;
	t_parser	*parse;
	int			x;

	parse = NULL;
	tools = init_tools();
	lexer = init_lexer(line);
	x = 0;
	if (lexer)
	{
		while (lexer->c)
		{
			token = get_next_token(lexer, env);
			if (token)
			{
				x = 1;
				parse = parse_value(parse, token, tools);
			}
		}
		if (x && !lexer->c)
			parser_add_back(&parse,
				new_parse(tools->cmd, tools->args, tools->red));
		free_staff(tools->cmd, tools, lexer);
	}
	return (parse);
}
