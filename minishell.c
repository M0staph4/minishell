#include "inc/header.h"
#include "inc/lexer.h"
int main(int ac, char **av, char **env)
{
	t_token	token;

	char *line;
	(void) ac;
	(void) av;
	(void) env;
	while ("everything is okey")
	{
		line = readline("minishell: ");
		lexing(line, &token);
	}
	return (0);
}
