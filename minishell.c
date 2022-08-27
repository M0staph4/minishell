#include "inc/header.h"
#include "struct.h"

// void    handler()
// {
//     rl_replace_line("", 0);
//     ft_putchar_fd('\n', 1);
//     rl_on_new_line();
//     rl_redisplay();
//     return;
// }
// void hd_sg()
// {
// 	signal(SIGQUIT, SIG_IGN);
// 	signal(SIGINT, handler);
// }
		// while(parse)
		// {
		// 	if(parse->cmd)
		// 		printf("cmd : %s\n",parse->cmd);
		// 	if(parse->args)
		// 	{
		// 		while(parse->args[++i])
		// 			printf("args : %s\n",parse->args[i]);
		// 	}
		// 	i = -1;
		// 	parse = parse->next;
		// }
int main(int ac, char **av, char **envp)
{
	t_token		token;
	t_parser	*parse;
	t_env_list	*env;
	//int i = -1;
	// (void) envp;
	// env = NULL;
	env = env_builder(envp);
	char *line;
	(void) ac;
	(void) av;
	while ("everything is okey")
	{
		// hd_sg();
		line = readline("minishell: ");
		if(ft_syntax_error(line))
			parse = lexing(line, &token, env);
		else
			parse = NULL;

		add_history(line);
		if(parse)
		{
			heredoc(&parse);
		
			pipeline_execution(parse, &env);
		}
		free(line);
		free(parse);
	}
	return (0);
}

