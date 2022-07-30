#include "inc/header.h"
#include "inc/lexer.h"
#include "inc/parser.h"

int main(int ac, char **av, char **env)
{
	t_token		token;

	char *line;
	(void) ac;
	(void) av;
	(void) env;
	while ("everything is okey")
	{
		line = readline("minishell: ");
		if(ft_syntax_error(line))
			lexing(line, &token);
		else
			printf("SYNTAX ERROR\n");
	}
	return (0);
}
