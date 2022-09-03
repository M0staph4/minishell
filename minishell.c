#include "inc/header.h"
#include "struct.h"

// void    handler()
// {
// 	exit_status = 130;
//     rl_replace_line("", 0);
//     ft_putchar_fd('\n', 1);
//     rl_on_new_line();
//     rl_redisplay();
//     return;
// }
// void hd_sg()
// {
// 	if (!signal(SIGQUIT, SIG_IGN))
// 		exit_status = 1;
// 	signal(SIGINT, handler);
// }

void	free_leaks(t_parser *parse)
{
	t_parser		*tmp;
	t_redirection	*tmp_red;

	while (parse)
	{
		if (parse->cmd)
			free(parse->cmd);
		if (parse->args)
			free_array(parse->args);
		if (parse->red)
		{
			while (parse->red)
			{
				if (parse->red->file)
					free(parse->red->file);
				tmp_red = parse->red;
				parse->red = parse->red->next;
				free(tmp_red);
			}
		}
		tmp = parse;
		parse = parse->next;
		free(tmp);
	}
}

void	minishell(char *line, t_env_list *env)
{
	t_token		token;
	t_parser	*parse;
	t_vr_tools	*tools;

	tools = NULL;
	if (ft_syntax_error(line))
		parse = lexing(line, &token, env, tools);
	else
		parse = NULL;
	add_history(line);
	if (parse)
	{
		heredoc(&parse);
		pipeline_execution(&parse, &env);
	}
	free(line);
	free_leaks(parse);
}

int	main(int ac, char **av, char **envp)
{
	t_env_list	*env;
	char		*line;

	env = env_builder(envp);
	(void) ac;
	(void) av;
	while ("everything is okey")
	{
		//hd_sg();
		line = readline("minishell: ");
		minishell(line, env);
	}
	return (0);
}
