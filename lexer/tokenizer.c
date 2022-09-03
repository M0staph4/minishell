/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <mmoutawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 01:18:27 by mmoutawa          #+#    #+#             */
/*   Updated: 2022/09/03 01:18:28 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

t_token	*init_token(int type, char *value)
{
	t_token	*token;

	token = malloc (sizeof(t_token));
	token->content = ft_strdup(value);
	token->type = type;
	free(value);
	return (token);
}
