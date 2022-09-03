/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <mmoutawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 02:11:24 by mmoutawa          #+#    #+#             */
/*   Updated: 2022/09/03 02:11:25 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "header.h"
# include "struct.h"

t_redirection	*new_red(int type, char *file);
int				red_size(t_redirection *lst);
void			red_add_back(t_redirection **lst, t_redirection *new);
void			red_add_front(t_redirection **lst, t_redirection *new);
t_redirection	*red_last(t_redirection *lst);
t_parser		*new_parse(char *cmd, char **args, t_redirection *redirection);
int				parse_size(t_parser *lst);
void			parser_add_back(t_parser **lst, t_parser *new);
void			parser_add_front(t_parser **lst, t_parser *new);
t_parser		*parser_last(t_parser **lst);
t_parser		*lexing(char *line, t_token *token,
					t_env_list *env, t_vr_tools *tools);
void			free_array_parse(char **args);
char			**add_args_to_list(char **args, t_token *token);
int				red_type(int type);
t_parser		*parse_value(t_parser *parse,
					t_token *token, t_vr_tools *tools);
t_vr_tools		*init_tools(void);
t_redirection	*add_red_to_list(t_token *token, t_vr_tools *tools);
t_parser		*add_parse(t_parser *parse, t_token *token, t_vr_tools *tools);

#endif