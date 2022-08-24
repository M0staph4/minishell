#include "../inc/header.h"
#include "../inc/execution.h"

int		check_builtin(t_parser *parser)
{
	if (!ft_strncmp(parser->cmd, "cd", 3) || (!ft_strncmp(parser->cmd, "pwd", 4))
		|| !ft_strncmp(parser->cmd, "echo", 6) || !ft_strncmp(parser->cmd, "exit", 6)
		|| !ft_strncmp(parser->cmd, "env", 4) || !ft_strncmp(parser->cmd, "export", 8)
		|| !ft_strncmp(parser->cmd, "unset", 6))
			return (1);
	return (0);
}

void 	exec_builtins(t_parser *parser, t_env_list *env)
{
	if (!ft_strncmp(parser->cmd, "cd", 3))
		exec_cd(parser->args[1], env);
    else if (!ft_strncmp(parser->cmd, "pwd", 4) || !ft_strncmp(parser->cmd, "PWD", 4))
        exec_pwd(env);
	else if (!ft_strncmp(parser->cmd, "echo", 6) || !ft_strncmp(parser->cmd, "ECHO", 6))
        exec_echo(parser);
    else if (!ft_strncmp(parser->cmd, "exit", 6))
        exec_exit(parser);
    else if (!ft_strncmp(parser->cmd, "env", 4) || !ft_strncmp(parser->cmd, "ENV", 4))
        exec_env(parser, &env);
	else if (!ft_strncmp(parser->cmd, "export", 8))
        exec_export(parser, &env);
	else if (!ft_strncmp(parser->cmd, "unset", 6))
        exec_unset(&env, parser->args[1]);
}


void execute_last_cmd(t_parser *parser, t_env_list *env, int fd_in, int file, int *end)
{
	char	*path;
	char	**envp;
	int pid;

	envp = t_env_list_to_char(&env);
	path = search(envp, parser->cmd);
	pid = fork();
	if (pid == 0)
	{
		if (fd_in != 0)
		{
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		if (end[WRITE] > 2)
			close(end[WRITE]);
		redirections(parser->red, parser->cmd, file);
		if (parser->cmd)
		{
			if (check_builtin(parser) && parser->cmd)
			{
        		exec_builtins(parser, env);
				return ;
			}
			else if (execve(path, parser->args, envp) == -1)
			{
				ft_putstr_fd("command not found: ", 2);
				ft_putendl_fd(parser->cmd, 2);
				exit(127);
			}
		}
		
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		exit(0);
	}
}
void	launch_child(t_parser *parser, t_env_list *env, int fd_in, int *end, int file)
{
	char	*path;
	char	**envp;

	envp = t_env_list_to_char(&env);
	path = search(envp, parser->cmd);
	if (fd_in != 0)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	dup2(end[WRITE], STDOUT_FILENO);
	close(end[WRITE]);
	if (end[READ] > 2)
		close(end[READ]);
	if (end[WRITE] > 2)
			close(end[WRITE]);
	redirections(parser->red, parser->cmd, file);
	if (check_builtin(parser) && parser->cmd)
        exec_builtins(parser, env);	
	else if (parser->cmd && (execve(path, parser->args, envp) == -1))
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(parser->cmd, 2);
	}
	exit(0);
}

void    pipeline_execution(t_parser *parser, t_env_list **envp, int file)
{
	pid_t pid;
	t_env_list *env;
	int end[2];
	int	fd_in;
	int status;
	
	fd_in = 0;
	env = (*envp);
	while (parser->next)
	{
		pipe(end);
		pid = fork();
		if (pid == 0)
			launch_child(parser, env, fd_in, end, file);
		fd_in = end[READ];
		if (end[WRITE] > 2)
			close(end[WRITE]);
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		parser = parser->next;
	}
	execute_last_cmd(parser, env, fd_in, file, end);
	while(waitpid(-1, &status, 0) > 0);
}



