#include "../inc/lexer.h"
#include "../inc/header.h"
#include "../inc/token.h"

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
	lexer->cunt_pp = 0;
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

void	collect_cmd(t_lexer *lexer, t_token *token)
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
	//free(s);
	ft_tokenadd_back(token, ft_newtoken(TOKEN_CMD, value));
}

void	get_next_token(t_lexer *lexer, t_token *token)
{
	while (lexer->c != '\0' && lexer->pos < ft_strlen(lexer->line))
	{

		if (lexer->c == ' ')
			lexer_skip_whitespaces(lexer);
		else if (lexer->c == '"')
			collect_string(lexer, token);
		else if(lexer->c == '\'')
			collect_string(lexer, token);
		else if (lexer->c == '<' )
		{
			lexer_advance(lexer);
			if(lexer->c == '<')
				ft_tokenadd_back(token, ft_newtoken(TOKEN_CMD, "<<"));
			else 
				ft_tokenadd_back(token, ft_newtoken(TOKEN_CMD, "<"));
		}
		else if (lexer->c == '>' )
		{
			lexer_advance(lexer);
			if(lexer->c == '>')
				ft_tokenadd_back(token, ft_newtoken(TOKEN_CMD, ">>"));
			else if(lexer->c != '>') 
				ft_tokenadd_back(token, ft_newtoken(TOKEN_CMD, ">"));
		}
		else if (lexer->c == '|')
		{
			ft_tokenadd_back(token, ft_newtoken(TOKEN_CMD, "|"));
			lexer_advance(lexer);
		}
		else
			collect_cmd(lexer, token);
	}
}

void	collect_string(t_lexer *lexer, t_token *token)
{
	char *value;
	char *s;
	t_token *p;

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
	ft_tokenadd_back(token, ft_newtoken(TOKEN_STR, value));
	p = ft_newtoken(TOKEN_STR, value);
	//printf("%s--\n");
}

char *get_char_as_string(t_lexer *lexer)
{
	char *str;

	str = malloc(2);
	str[0] = lexer->c;
	str[1] = '\0';
	return(str);
}

void	advance_token(t_lexer *lexer, t_token *token, t_token *tokens)
{
	lexer_advance(lexer);
	ft_tokenadd_back(token ,tokens);
}
