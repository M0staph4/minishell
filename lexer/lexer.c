#include "../inc/lexer.h"
#include "../inc/header.h"
#include "../inc/token.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int find_second_one(char *line, int pos)
{
	if(line[pos] == '\'')
	{
		pos++;
		while(line[pos])
		{
			if (line[pos] == '\'')
				return (pos);
			pos++;
		}
	}
	if(line[pos] == '"')
	{
		pos++;
		while(line[pos])
		{
			if (line[pos] == '"')
				return(pos);
			pos++;
		}
	}
	return(-1);
}

int check_second_pipe(char *line, int pos)
{
	pos++;
	while(line[pos] <= 32 && line[pos] <= 127 && line[pos])
		pos++;
	if(line[pos] == '|')
		return(-1);
	if(!line[pos])
		return(-1);
	return(pos);
}

int check_pipe(char *line)
{
	int i; 
	i = 0;
	if(line[0] == '|')
		return(0);
	if(line[ft_strlen(line)-1] == '|')
			return(0);
	while(line[i])
	{
		if (line[i] == '|' && line[i + 1] == '|')
			return(0);
		if(line[i] == '|')
		{
			if(check_second_pipe(line, i) == -1)
				return(0);
			else
				i = check_second_pipe(line, i);
		}
		i++;
	}
	return(1);
}

int	check_quotes(char *line)
{
	int i = 0;
	int x = 0;
	while(line[i])
	{
		if(line[i] == '"' || line[i] == '\'')
		{
			if (find_second_one(line, i) == -1)
				return(-1);
			else
			{
				i = find_second_one(line, i);
				x = i;
			}
		}
		i++;
	}
	return(x);
}

int check_red(char *line)
{
	int i;
	i = 0;
	while(line[i])
	{
		if (line[i] == '<' || line[i] == '>')
		{
			i++;
			if(!line[i] || !line[i + 1])
				return(0); 
			if((line[i] == '<' && line[i + 1] == '<'))
				return(0);
			if(line[i] == '>' && line[i + 1] == '>')
				return(0);
		}
		i++;
	}
	return(1);
}

int ft_syntax_error(char *line, t_lexer *lexer)
{
	int i;

	i = 0;
	if(check_quotes(line) == -1)
			return(0);
	lexer->q_pos = check_quotes(line);
	if(!check_pipe(line))
		return(0);
	if(!check_red(line))
		return(0);
	else
		return(1);
}

t_lexer *init_lexer(char *line)
{
	t_lexer *lexer;

	lexer = malloc(sizeof(t_lexer));
	add_history(line);
	lexer->line = line;
	lexer->pos = 0;
	lexer->cunt_arg = 0;
	if(!ft_syntax_error(lexer->line, lexer))
	{
		printf("SYNTAX ERROR\n");
		return(NULL);
	}
	lexer->c = lexer->line[lexer->pos];
	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer->pos < ft_strlen(lexer->line))
	{
		lexer->pos++;
		lexer->c = lexer->line[lexer->pos];
	}
}

void	lexer_skip_whitespaces(t_lexer *lexer)
{
	while (lexer->c == ' ')
		lexer_advance(lexer);
}

t_token *collect_cmd(t_lexer *lexer)
{
	char *value;
	char *s;

	value = malloc(1);
	value[0] = '\0';
	while (lexer->c != ' ' && lexer->c != '\0' && lexer->c != '|' && lexer->c != '>' && lexer->c != '<')
	{
		if(lexer->c == '"' || lexer->c == '\'')
			lexer_advance(lexer);
		s = get_char_as_string(lexer);  
		value = ft_strjoin(value, s);
		lexer_advance(lexer);
		lexer->cunt_arg += 1;
	}
	//free(s);
	return(init_token(TOKEN_CMD, value));
}

t_token *collect_opn(t_lexer *lexer)
{
	char *value;
	char *s;

	value = malloc(1);
	value[0] = '\0';
	s = get_char_as_string(lexer);
	value = ft_strjoin(value, s);
	//free(s);
	lexer_advance(lexer);
	while ((lexer->c >= 'a' && lexer->c <= 'z') || (lexer->c >= 'A' && lexer->c <= 'Z'))
	{
		s = get_char_as_string(lexer);
		value = ft_strjoin(value, s);
		lexer_advance(lexer);
	}
	if((lexer->c < 'a' && lexer->c > 'z') || (lexer->c < 'A' && lexer->c > 'Z'))
		return(NULL);
	lexer_advance(lexer);
	//free(s);
	return(init_token(TOKEN_OPN, value));
}

t_token *get_next_token(t_lexer *lexer)
{

	while (lexer->c != '\0' && lexer->pos < ft_strlen(lexer->line))
	{
		if (lexer->c == ' ')
			lexer_skip_whitespaces(lexer);
		else if (lexer->c == '"')
			return (collect_string(lexer));
		else if(lexer->c == '\'')
			return (collect_string(lexer));
		else if (lexer->c == '<' )
		{
			lexer_advance(lexer);
			if(lexer->c == '<')
				return (advance_token(lexer, init_token(TOKEN_HEREDOC, "<<")));
			else 
				return (advance_token(lexer, init_token(TOKEN_REDOUT, "<")));
		}
		else if (lexer->c == '>' )
		{
			lexer_advance(lexer);
			if(lexer->c == '>')
				return (advance_token(lexer, init_token(TOKEN_APPEND, ">>")));
			else 
				return (advance_token(lexer, init_token(TOKEN_REDIN, ">")));
		}
		else if (lexer->c == '|')
			return (advance_token(lexer, init_token(TOKEN_PIPE, get_char_as_string(lexer))));
		else if(lexer->c == '-')
			return(collect_opn(lexer));
		else
			return (collect_cmd(lexer));
	}
	return (NULL);
}

t_token *collect_string(t_lexer *lexer)
{
	char *value;
	char *s;

	value = malloc(1);
	value[0] = '\0';
	if (lexer->c == '"' || lexer->c == '\'')
		lexer_advance(lexer);
	while (lexer->c != '"' && lexer->c != '\'' && lexer->c != '\0')
	{
		while(lexer->c == '"' || lexer->c == '\'')
			lexer_advance(lexer);
		if(lexer->c != '"' && lexer->c != '\'')
		{
			s = get_char_as_string(lexer);
			value = ft_strjoin(value, s);
			lexer_advance(lexer);
		}
		while(lexer->c == '"' || lexer->c == '\'')
			lexer_advance(lexer);
	}
	lexer_advance(lexer);
	//free(s);
	return(init_token(TOKEN_STR, value));
}



char *get_char_as_string(t_lexer *lexer)
{
	char *str;

	str = malloc(2);
	str[0] = lexer->c;
	str[1] = '\0';
	return(str);
}

t_token *advance_token(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

int main(int ac, char **av)
{
	t_token *token;
	t_lexer *lexer;
	char *line;
	(void) ac;
	(void) av;
	while ("everything is okey")
	{
		line = readline("minishell: ");
		lexer = init_lexer(line);
		if(lexer)
		{
			while(lexer->c != '\0')
			{
				token = get_next_token(lexer);
				if(token)
					printf("TOKEN(%d, %s)----%d\n", token->type, token->content, lexer->q_pos);
				//ft_parse(lexer, token);
			}
		}
		//free(line);
		//free(lexer);
	}
	return (0);

}