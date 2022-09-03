/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-mhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 23:14:39 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/09/02 23:14:41 by cel-mhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int	compare(char *arg)
{
	int	i;

	i = 1;
	if (arg[1] == '\0')
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	check_echo(char *args)
{
	if (args[0] == '-' && compare(args))
		return (1);
	return (0);
}

void	print_args(char **args)
{
	int	i;

	i = 2;
	while (args[i])
	{
		if (!check_echo(args[i]))
		{
			printf("%s", args[i]);
			if (args[i + 1] != NULL)
				printf(" ");
		}
		i++;
	}
}

void	print_without_option(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	printf("\n");
}

void	exec_echo(t_parser *parser)
{
	if (!parser->args[1])
		printf("\n");
	else if (check_echo(parser->args[1]))
		print_args(parser->args);
	else
		print_without_option(parser->args);
	exit(exit_status);
}
