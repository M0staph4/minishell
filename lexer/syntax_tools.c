/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <mmoutawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 01:18:22 by mmoutawa          #+#    #+#             */
/*   Updated: 2022/09/03 01:18:23 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int	find_second_one(char *line, int pos)
{
	if (line[pos] == '\'')
	{
		pos++;
		while (line[pos])
		{
			if (line[pos] == '\'')
				return (pos);
			pos++;
		}
	}
	if (line[pos] == '"')
	{
		pos++;
		while (line[pos])
		{
			if (line[pos] == '"')
				return (pos);
			pos++;
		}
	}
	return (-1);
}

int	check_second_pipe(char *line, int pos)
{
	pos++;
	while (line[pos] <= 32 && line[pos] <= 127 && line[pos])
		pos++;
	if (line[pos] == '|')
		return (-1);
	if (!line[pos])
		return (-1);
	return (pos);
}
