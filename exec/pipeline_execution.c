#include "../inc/header.h"
#include "../inc/execution.h"

int		check_builtin(t_parser *parser)
{
	if (!ft_strncmp(parser->cmd, "cd", 3))
		return (1);
	else if (!ft_strncmp(parser->cmd, "pwd", 4))
		return (1);
	else if (!ft_strncmp(parser->cmd, "echo", 6))
		return (1);
	else if (!ft_strncmp(parser->cmd, "exit", 6))
		return (1);
	return (0);
}

void	exec_builtins(t_parser **parse,  t_env_list **env)
{
    if (!ft_strncmp((*parse)->cmd, "cd", 3))
		exec_cd((*parse)->args[1], *env);
    else if (!ft_strncmp((*parse)->cmd, "pwd", 4))
        exec_pwd();
	else if (!ft_strncmp((*parse)->cmd, "echo", 6))
        exec_echo((*parse));
    else if (!ft_strncmp((*parse)->cmd, "exit", 6))
        exec_exit(*parse);
    if (!ft_strncmp((*parse)->cmd, "env", 4))
        exec_env((*parse), env);
}

void 	execute(t_parser *parser, char *path, char **envp, t_env_list *env)
{
	if (check_builtin(parser))
        exec_builtins(&parser, &env);
	else if (!ft_strncmp(parser->cmd, "export", 8))
	{
        exec_export(parser, &env);
		return ;
	}
	else if (!ft_strncmp(parser->cmd, "unset", 6))
        exec_unset(&env, parser->args[1]);
	else if (execve(path, parser->args, envp) == -1)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(parser->cmd, 2);
		exit(127);
	}
}

void execute_last_cmd(t_parser *parser, t_env_list *env, int write_in, int file)
{
	char	*path;
	char	**envp;
	int pid;
	int status;

	envp = t_env_list_to_char(&env);
	path = search(envp, parser->cmd);
	pid = fork();
	waitpid(pid, &status, 0);
	if (pid == 0)
	{
		if (write_in != 0)
		{
			dup2(write_in, STDIN_FILENO);
			close(write_in);
		}
		redirections(parser->red, parser->cmd, file);
		if (parser->cmd)
			execute(parser, path, envp, env);
		exit(0);
	}
}
void	launch_child(t_parser *parser, t_env_list *env, int write_in, int *end, int file)
{
	char	*path;
	char	**envp;
	envp = t_env_list_to_char(&env);
	path = search(envp, parser->cmd);
	if (write_in != 0)
	{
		dup2(write_in, STDIN_FILENO);
		close(write_in);
	}
	dup2(end[WRITE], STDOUT_FILENO);
	close(end[WRITE]);
	redirections(parser->red, parser->cmd, file);
	if (parser->cmd)
		execute(parser, path, envp, env);
	exit(0);

}

void    pipeline_execution(t_parser *parser, t_env_list **envp, int file)
{
	pid_t pid;
	t_env_list *env;
	int end[2];
	int	write_in;
	int status;
	
	write_in = 0;
	env = (*envp);
	while (parser->next)
	{
		pipe(end);
		pid = fork();
		if (pid == 0)
			launch_child(parser, env, write_in, end, file);
		write_in = end[READ];
		close(end[WRITE]);
		parser = parser->next;
	}
	execute_last_cmd(parser, env, write_in, file);
	while(waitpid(-1, &status, 0) > 0);
}



