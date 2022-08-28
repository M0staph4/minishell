#include "../inc/header.h"
#include "../inc/execution.h"

void execute(t_env_list *env, t_parser *parser)
{
	char	*path;
	char	**envp;

	envp = t_env_list_to_char(&env);
	if (parser->cmd[0] == '.' || parser->cmd[0] == '/')
	{
		path = parser->cmd;
		if (access(path, X_OK))
			print_error2(": Permission denied", path, 126);
	}
	else
		path = search(envp, parser->cmd);
	if ((execve(path, parser->args, envp) == -1))
	{
		if (parser->next)
			print_error2(parser->cmd, "command not found: ", 0);
		else
			print_error2(parser->cmd, "command not found: ", 127);
	}
	else
		exit_status = 0;
	free_array(envp);
	free(path);
}

void execute_last_cmd(t_parser *parser, t_env_list *env, int fd_in, int *end)
{
	if (!parser->red && parent_builtins(parser) &&  parser->flag != 1)
        exec_builtins(parser, env);
	else if (fork() == 0)
	{
		if (fd_in != 0)
			dup_end(fd_in, STDIN_FILENO);
		if (end[WRITE] > 2)
			close(end[WRITE]);
		if (!redirections(parser->red, parser->cmd) && parser->cmd)
		{
				if (check_builtin(parser))
        			exec_builtins(parser, env);
				else
					execute(env, parser);
		}
		exit(exit_status);
	}
}

void	launch_child(t_parser *parser, t_env_list *env, int fd_in, int *end)
{
	if (fork() == 0)
	{
		if (fd_in != 0)
			dup_end(fd_in, STDIN_FILENO);
		dup_end(end[WRITE], STDOUT_FILENO);
		close(end[READ]);
		if (!redirections(parser->red, parser->cmd))
		{
			if (check_builtin(parser) && parser->cmd)
    		    exec_builtins(parser, env);	
			else
				execute(env, parser);
		}
		exit(exit_status);
	}
}

void	wait_child(void)
{
	int status;

	while(waitpid(-1, &status, 0) > 0)
	{
		if(WEXITSTATUS(status))
			exit_status = WEXITSTATUS(status);
	}
}

void    pipeline_execution(t_parser **parse, t_env_list **envp)
{
	int fd_in;
	t_env_list *env;
	int end[2];
	t_parser *parser;
	
	parser = *parse;
	fd_in = 0;
	env = (*envp);
	while (parser->next)
	{
		parser->flag = 1;
		pipe(end);
		launch_child(parser, env, fd_in, end);
		close_pipe(end, fd_in);
		fd_in = end[READ];
		parser = parser->next;
		if (parser)
			parser->flag = 1;
	}
	execute_last_cmd(parser, env, fd_in, end);
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	wait_child();
}



