/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-mhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 01:00:15 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/09/03 01:00:21 by cel-mhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int	isdir(char *file_name)
{
	struct stat	path_stat;

	stat(file_name, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

int	redirection_in_from(t_redirection *red)
{
	if (red->type == TOKEN_HEREDOC)
		return (red->end);
	else if (access(red->file, F_OK) == 0)
		return (open(red->file, O_RDONLY, 0777));
	else
		return (-1);
}

int	check_file(char *file)
{
	if (!isdir(file))
	{
		print_error(": Is a directory\n", file, 1);
		return (-1);
	}
	else if (access(file, W_OK) != 0)
	{
		print_error(": Permission denied\n", file, 1);
		return (-1);
	}
	return (0);
}

int	redirection_out_to(t_redirection *red)
{
	int	output;

	output = 0;
	if (!red->file)
	{
		perror("File");
		return (-1);
	}
	if (red->file)
	{
		if (red->type == TOKEN_REDOUT)
			output = open(red->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		else if (red->type == TOKEN_APPEND)
			output = open(red->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (check_file(red->file))
			return (-1);
		return (output);
	}
	return (-1);
}

int	redirections(t_redirection *red, char *cmd, int output, int input)
{
	if (!red)
		return (0);
	while (red)
	{
		if (red->type == TOKEN_REDIN || red->type == TOKEN_HEREDOC)
		{
			input = redirection_in_from(red);
			if (input == -1)
			{
				print_error2(": No such file or directory", red->file, 1);
				return (-1);
			}
		}
		else if (red->type == TOKEN_APPEND || red->type == TOKEN_REDOUT)
		{
			output = redirection_out_to(red);
			if (output == -1)
				return (-1);
		}
		red = red->next;
	}
	dup_redirections(input, output, cmd);
	return (0);
}
