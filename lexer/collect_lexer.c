/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <mmoutawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 01:17:59 by mmoutawa          #+#    #+#             */
/*   Updated: 2022/09/03 01:18:01 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

t_token	*collect_cmd(t_lexer *lexer, t_env_list *env)
{
	char	*value;
	char	*join;
	int		i;

	i = 0;
	value = ft_strdup("");
	while (lexer->c != ' ' && lexer->c != '\0' && lexer->c != '|'
		&& lexer->c != '>' && lexer->c != '<')
	{
		value = add_all_in_value(value, lexer->c, lexer, env);
		if (!sp_c(lexer->c) || i)
			lexer_advance(lexer);
		if (lexer->c == '"' || lexer->c == '\'')
		{
			i = 1;
			join = join_to_join(lexer, lexer->c, env);
			value = ft_strjoin(value, join);
			free(join);
		}
	}
	return (init_token(TOKEN_STR, value));
}

char	*red_value(char *value, t_lexer *lexer, t_env_list *env)
{
	char	*join;

	join = join_to_join(lexer, lexer->c, env);
	value = ft_strjoin(value, join);
	free(join);
	return (value);
}

t_token	*collect_red(t_lexer *lexer, int i, t_env_list *env)
{
	char	*value;
	int		x;

	x = 0;
	value = ft_strdup("");
	if (lexer->c == '>')
		lexer_advance(lexer);
	while (lexer->c == ' ')
		lexer_advance(lexer);
	while (lexer->c != '\0' && lexer->c != ' ' && lexer->c != '<'
		&& lexer->c != '>' && lexer->c != '|')
	{
		value = add_all_in_value(value, lexer->c, lexer, env);
		if (!sp_c(lexer->c) || x)
			lexer_advance(lexer);
		if (lexer->c == '"' || lexer->c == '\'')
		{
			x = 1;
			value = red_value(value, lexer, env);
		}
	}
	return (init_token(i, value));
}

t_token	*collect_apn_hrd(t_lexer *lexer, int i)
{
	char	*value;
	char	*join;

	value = ft_strdup("");
	lexer_advance(lexer);
	while (lexer->c == ' ')
		lexer_advance(lexer);
	while (lexer->c != '\0' && lexer->c != ' ' && lexer->c != '<'
		&& lexer->c != '>' && lexer->c != '|')
	{
		if (lexer->c != '"' && lexer->c != '\'')
			value = join_char(lexer, value);
		if (lexer->c == '"' || lexer->c == '\'')
		{
			join = join_to_join(lexer, lexer->c, NULL);
			value = ft_strjoin(value, join);
			free(join);
		}
		lexer_advance(lexer);
	}
	return (init_token(i, value));
}

t_token	*collect_string(t_lexer *lexer, t_env_list *env)
{
	char	*value;
	char	*join;
	int		i;

	i = 0;
	value = ft_strdup("");
	while (lexer->c != '|' && lexer->c != '>' && lexer->c != '<'
		&& lexer->c != '\0' && lexer->c != ' ')
	{
		value = add_all(value, lexer->c, lexer, env);
		if (lexer->c == '"' || lexer->c == '\'')
		{
			i = 1;
			join = join_to_join(lexer, lexer->c, env);
			if (join)
				value = ft_strjoin(value, join);
			free(join);
		}
		if (!sp_c(lexer->c) || i)
			lexer_advance(lexer);
		i = 0;
	}
	return (init_token(TOKEN_STR, value));
}
