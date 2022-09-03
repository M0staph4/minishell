/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-mhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 23:22:55 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/09/02 23:22:57 by cel-mhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void	dup_redirections(int input, int output, char *cmd)
{
	if (output != -3 && cmd)
	{
		dup2(output, STDOUT_FILENO);
		close(output);
	}
	if (input != -2 && cmd)
	{
		dup2(input, STDIN_FILENO);
		close(input);
	}
}

void	dup_end(int end, int dup_fd)
{
	dup2(end, dup_fd);
	close(end);
}

void	close_pipe(int *end, int fd_in)
{
	if (end[WRITE] > 2)
		close(end[WRITE]);
	if (fd_in != STDIN_FILENO)
		close(fd_in);
}

void	execute_execve(t_parser *parser, char *path, char **envp)
{
	if ((execve(path, parser->args, envp) == -1))
	{
		if (parser->next)
			print_error2(parser->cmd, "command not found: ", 0);
		else
		{
			print_error2(parser->cmd, "command not found: ", 127);
			exit(127);
		}
	}
}

void	execute(t_env_list **env, t_parser *parser)
{
	char	*path;
	char	**envp;

	envp = t_env_list_to_char(env);
	if (parser->cmd[0] == '.' || parser->cmd[0] == '/')
	{
		path = parser->cmd;
		if (access(path, X_OK))
		{
			print_error2(": Permission denied", path, 126);
			exit(126);
		}
	}
	else
		path = search(envp, parser->cmd, 0);
	execute_execve(parser, path, envp);
	free_array(envp);
	free(path);
}
