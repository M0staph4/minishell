#include "../inc/header.h"
#include "../inc/execution.h"

// void	exec_builtins(t_parser **parse, env_list *env)
// {
//     if (!ft_strncmp((*parse)->cmd, "cd", 3))
//         exec_cd((*parse)->args[1]);
//     else if (!ft_strncmp((*parse)->cmd, "pwd", 4))
//         exec_pwd();
//     else if (!ft_strncmp((*parse)->cmd, "export", 7))
//         exec_export(env, (*parse)->args);
//     else if (!ft_strncmp((*parse)->cmd, "unset", 6))
//         exec_unset(env, parse);
//     else if (!ft_strncmp((*parse)->cmd, "env", 3))
//         exec_env(env, envp);
// }

// execute_last_cmd()
// {

// }

// execute_pipeline(t_parser *parse)
// {
//         while (parse->cmd)
//         {
//             launch_child(parse);

//         }
//         execute_last_cmd(parse);
// }

// char    **ft_get_env(env_list *env)
// {
//     printf("ddddd\n");
//     while(env)
//     {
//         printf("%s <\n", env->content);
//         env = env->next;
//     }
//     return (NULL);
// }


void	launch_child(env_list *env)
{
    printf("ddd\n");
	// char	*path;
	// int		fd;
    env = 0;
	// path = search(parser->cmd, env);
	// if (execve(path, parser->cmd, env) == -1)
	// {
	// 	ft_putstr_fd("command not found:", 2);
	// 	ft_putstr_fd(cmd[0], 2);
	// }
}

// void    execute(t_parser **parser)
// {
//     if (fork() == 0)
//         launch_child(parser);
// }