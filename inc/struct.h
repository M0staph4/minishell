/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <mmoutawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 02:11:31 by mmoutawa          #+#    #+#             */
/*   Updated: 2022/09/03 02:11:32 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "header.h"

typedef struct s_env_list
{
	char				*key;
	char				*content;
	char				*separator;
	struct s_env_list	*next;
}	t_env_list;

typedef struct s_lexer{
	char			c;
	char			*line;
	unsigned int	pos;
	int				nb_pipe;
}	t_lexer;

typedef struct s_parser
{
	char					*cmd;
	char					**args;
	int						flag;
	struct s_redirection	*red;
	struct s_parser			*next;
}	t_parser;

typedef struct s_redirection
{
	int						type;
	char					*file;
	int						end;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_vr_tools
{
	char			*cmd;
	char			**args;
	t_redirection	*red;
}	t_vr_tools;

typedef struct s_token
{
	char	*content;
	enum	{
		TOKEN_STR,
		TOKEN_PIPE,
		TOKEN_REDIN,
		TOKEN_REDOUT,
		TOKEN_HEREDOC,
		TOKEN_APPEND,
		TOKEN_NULL,
		TOKEN_DLR,
	}	type;
}	t_token;

t_token	*init_token(int type, char *value);

#endif