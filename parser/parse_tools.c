/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <mmoutawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 01:18:35 by mmoutawa          #+#    #+#             */
/*   Updated: 2022/09/03 01:18:36 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int	count_args(char **args)
{
	int	i;

	i = 0;
	if (args)
	{
		while (args[i])
			i++;
	}
	return (i);
}

char	**add_args_to_list(char **args, t_token *token)
{
	char	**new_args;
	int		i;
	int		count;

	count = count_args(args);
	i = -1;
	new_args = malloc (sizeof(char *) * (count + 2));
	while (++i < count)
		new_args[i] = args[i];
	if (count)
		free(args);
	new_args[i++] = ft_strdup(token->content);
	new_args[i] = NULL;
	free(token->content);
	return (new_args);
}

t_vr_tools	*init_tools(void)
{
	t_vr_tools	*tools;

	tools = malloc (sizeof(t_vr_tools));
	tools->red = NULL;
	tools->cmd = NULL;
	tools->args = NULL;
	return (tools);
}

int	red_type(int type)
{
	if (type == TOKEN_REDIN || type == TOKEN_REDOUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

t_parser	*parse_value(t_parser *parse, t_token *token, t_vr_tools *tools)
{
	if (red_type(token->type))
	tools->red = add_red_to_list(token, tools);
	parse = add_parse(parse, token, tools);
	free(token);
	return (parse);
}
