/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-mhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 01:00:40 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/09/03 01:00:41 by cel-mhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include "../inc/execution.h"

void	close_heredoc_pipes(t_redirection *red)
{
	if (red)
	{
		while (red)
		{
			if (red->type == TOKEN_HEREDOC)
				close(red->end);
			red = red->next;
		}
	}
}

void	execute_last_cmd(t_parser **p, t_env_list **env, int fd_in, int *end)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (!(*p)->red && parent_builtins(*p) && (*p)->flag != 1)
		exec_builtins((*p), env);
	else if (fork() == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (fd_in != 0)
			dup_end(fd_in, STDIN_FILENO);
		if (end[WRITE] > 2)
			close(end[WRITE]);
		if (!redirections((*p)->red, (*p)->cmd, -3, -2) && (*p)->cmd)
		{
			if (check_builtin(*p))
				exec_builtins((*p), env);
			else
				execute(env, (*p));
		}
		exit(exit_status);
	}
}

void	wait_child(int i)
{
	int	status;

	while (waitpid(0, &status, 0) > 0)
	{
		if (WEXITSTATUS(status) && !i)
			exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (!i)
				exit_status = WIFSIGNALED(status) + 129;
			else
				exit_status = WIFSIGNALED(status);
		}
		i = 1;
	}
	if (!i)
		exit_status = 0;
}

void	launch_child(t_parser **parser, t_env_list **env, int fd_in, int *end)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (fork() == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (fd_in != 0)
			dup_end(fd_in, STDIN_FILENO);
		dup_end(end[WRITE], STDOUT_FILENO);
		close(end[READ]);
		if (!redirections((*parser)->red, (*parser)->cmd, -3, -2))
		{
			if (check_builtin((*parser)) && (*parser)->cmd)
				exec_builtins((*parser), env);
			else
				execute(env, (*parser));
		}
		exit(exit_status);
	}
}

void	pipeline_execution(t_parser **parse, t_env_list **env)
{
	int			fd_in;
	int			end[2];
	t_parser	*parser;

	parser = *parse;
	fd_in = 0;
	while (parser->next)
	{
		parser->flag = 1;
		pipe(end);
		launch_child(&parser, env, fd_in, end);
		close_pipe(end, fd_in);
		close_heredoc_pipes(parser->red);
		fd_in = end[READ];
		parser = parser->next;
		if (parser)
			parser->flag = 1;
	}
	execute_last_cmd(&parser, env, fd_in, end);
	close_heredoc_pipes(parser->red);
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	wait_child(0);
}
