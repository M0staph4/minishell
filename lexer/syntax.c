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
	if(line[0] && line[ft_strlen(line) - 1] == '|')
			return(0);
	while(line[i] == ' ')
		i++;
	if(line[i] == '|')
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
		if ((line[i] == '<' || line[i] == '>') && (line[i - 1] != '\'' && line[i - 1] != '"'))
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