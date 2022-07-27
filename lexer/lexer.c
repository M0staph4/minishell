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
	while(line[i])
	{
		if(line[i] == '"' || line[i] == '\'')
		{
			if (find_second_one(line, i) == -1)
				return(0);
			else
				i = find_second_one(line, i);
		}
		i++;
	}
	return(1);
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

int ft_syntax_error(char *line)
{
	int i;

	i = 0;
	if(!check_quotes(line))
			return(0);
	if(!check_pipe(line))
		return(0);
	if(!check_red(line))
		return(0);
	else
		return(1);
}

int ft_count_pipe(char *line)
{
	int i;
	int x;
	i = -1;
	x = 1;
	while(line[++i])
		if(line[i] == '|')
			x++;
	return(x);
}

t_lexer *init_lexer(char *line)
{
	t_lexer *lexer;

	lexer = malloc(sizeof(t_lexer));
	add_history(line);
	lexer->line = line;
	lexer->pos = 0;
	lexer->cunt_arg = 0;
	lexer->nb_pipe = ft_count_pipe(lexer->line);
	lexer->nb_args = (int *)malloc(sizeof(int) * lexer->nb_pipe + 1);
	lexer->c = lexer->line[lexer->pos];
	lexer->x = 0;
	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0')
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
	}
	while(lexer->c == ' ')
		lexer_advance(lexer);
	return(init_token(TOKEN_STR, value));
}

t_token *collect_string_sngl(t_lexer *lexer)
{
	char *value;
	char *s;

	value = malloc(1);
	value[0] = '\0';
	if (lexer->c == '\'')
		lexer_advance(lexer);
	while (lexer->c != '\'' && lexer->c != '\0' && lexer->c != ' ')
	{
		s = get_char_as_string(lexer);
		value = ft_strjoin(value, s);
		lexer_advance(lexer);
		if(lexer->c == '"' && lexer->c == '\'' && lexer->c != '\0')
			lexer_advance(lexer);
		lexer->cunt_arg += 1;
	}
	lexer_advance(lexer);
	return(init_token(TOKEN_STR, value));
}

t_token *collect_red(t_lexer *lexer, int i)
{
	char *value;
	char *s;

	value = malloc(1);
	value[0] = '\0';
	while (lexer->c == ' ')
		lexer_advance(lexer);
	while (lexer->c != '\0' && lexer->c != ' ' && lexer->c != '<' && lexer->c != '>')
	{
		s = get_char_as_string(lexer);
		value = ft_strjoin(value, s);
		lexer_advance(lexer);
		if(lexer->c == '"' && lexer->c == '\'')
			lexer_advance(lexer);
	}
	while (lexer->c == ' ')
		lexer_advance(lexer); 
	return(init_token(i, value));
}

t_token *collect_apn_hrd(t_lexer *lexer, int i)
{
	char *value;
	char *s;

	value = malloc(1);
	value[0] = '\0';
	lexer_advance(lexer);
	while (lexer->c == ' ')
		lexer_advance(lexer);
	while (lexer->c != '\'' && lexer->c != '\0' && lexer->c != ' ' && lexer->c != '<' && lexer->c != '>')
	{
		s = get_char_as_string(lexer);
		value = ft_strjoin(value, s);
		lexer_advance(lexer);
		if(lexer->c == '"' && lexer->c == '\'')
			lexer_advance(lexer);
	}
	lexer_advance(lexer);
	return(init_token(i, value));
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
			return (collect_string_sngl(lexer));
		else if (lexer->c == '|')
		{
			lexer->x += 1; 
			return (advance_token(lexer, init_token(TOKEN_PIPE, get_char_as_string(lexer))));
		}
		else if (lexer->c == '<' )
		{
			lexer_advance(lexer);
			if(lexer->c == '<')
				return(collect_apn_hrd(lexer, TOKEN_HEREDOC));
			return (collect_red(lexer, TOKEN_REDIN));
		}
		else if (lexer->c == '>' )
		{
			lexer_advance(lexer);
			if(lexer->c == '>')
				return(collect_apn_hrd(lexer, TOKEN_APPEND));
			return (collect_red(lexer, TOKEN_REDOUT));
		}
		else
		{
			lexer->nb_args[lexer->x] += 1;
			return (collect_cmd(lexer));
		}
	}
	return (NULL);
}

t_token *collect_string(t_lexer *lexer)
{
	char *value;
	char *s;

	value = malloc(1);
	value[0] = '\0';
	if (lexer->c == '"')
		lexer_advance(lexer);
	while (lexer->c != '"' && lexer->c != '\0')
	{
		s = get_char_as_string(lexer);
		value = ft_strjoin(value, s);
		lexer_advance(lexer);
		if(lexer->c == '"' && lexer->c == '\'' && lexer->c == ' ' && lexer->c != '\0')
			lexer_advance(lexer);
		lexer->cunt_arg += 1;
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
