#include "../inc/header.h"

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
		if(line[i] == '|')
		{
			if (line[i] == '|' && line[i + 1] == '|')
				return(0);
			if(check_second_pipe(line, i) == -1)
				return(0);
			else
				i = check_second_pipe(line, i);
		}
		if(line[i] == '\'' || line[i] == '"')
			i = find_second_one(line, i);
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

int check_after_red(char *line, int i)
{
	i++;
	while(line[i] == ' ')
		i++;
	if(line[i] == '>' || line[i] == '<' || line[i] == '|')
			return(-1);
	else if(!line[i])
		return(-1);
	while(!ft_isalpha(line[i]) && ft_isalnum(line[i]))
	{
		if(line[i] == '>' || line[i] == '<' || line[i] == '|')
			return(-1);
		i++;
	}
	return(i);
}

int check_red(char *line)
{
	int i;
	int y;
	y = 0;
	i = 0;
	while(line[i])
	{
		if (line[i] && (line[i] == '<' || line[i] == '>'))
		{
			if (line[i] == '>' && line[i + 1] == '>')
				i = check_after_red(line, i + 1);
			else if(line[i] == '<' && line[i + 1] == '<')
				i = check_after_red(line, i + 1);
			else if(line[i] == '<')
				i = check_after_red(line, i);
			else if(line[i] == '>')
				i = check_after_red(line, i);
			if(i == -1)
				return(0);
		}
		if(line[i] == '\'' || line[i] == '"')
			i = find_second_one(line, i);
		i++;
	}
	return(1);
}

int ft_syntax_error(char *line)
{
	if (!line)
	{
		write(1, "exit\n", 6);
		exit(0);
	}
	if(!check_quotes(line))
	{
		printf("Quotes: syntax error\n");
		return(0);
	}
	else if(!check_pipe(line))
	{
		printf("Pipe: syntax error\n");
		exit_code = 258;
		return(0);
	}
	else if(!check_red(line))
	{
		printf("syntax error\n");
		exit_code = 258;
		return(0);
	}
	else
		return(1);
}