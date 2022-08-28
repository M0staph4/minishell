  #include "../inc/header.h"

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
	if (!ft_strncmp(parser->cmd, "cd", 3) )
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

int parent_builtins(t_parser *parser)
{
	if (!ft_strncmp(parser->cmd, "cd", 3) && parser->flag != 1)
		return (1);
	else if (!ft_strncmp(parser->cmd, "exit", 6)
		|| !ft_strncmp(parser->cmd, "env", 4) || !ft_strncmp(parser->cmd, "export", 8)
		|| !ft_strncmp(parser->cmd, "unset", 6))
			return (1);
	return (0);
}
