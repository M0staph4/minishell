/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <mmoutawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 01:18:44 by mmoutawa          #+#    #+#             */
/*   Updated: 2022/09/03 01:18:45 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

t_redirection	*new_red(int type, char *file)
{
	t_redirection	*new;

	new = malloc(sizeof(t_redirection));
	if (!new)
		return (0);
	new->type = type;
	new->file = file;
	new->next = NULL;
	return (new);
}

int	red_size(t_redirection *lst)
{
	int	size;

	size = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

void	red_add_back(t_redirection **lst, t_redirection *new)
{
	t_redirection	*n;

	n = *lst;
	if (!new)
		return ;
	if (!*lst)
		(*lst) = new;
	else
	{
		while (n->next)
			n = n->next;
		n->next = new;
	}
}

void	red_add_front(t_redirection **lst, t_redirection *new)
{
	if (new)
		new->next = *lst;
	*lst = new;
}

t_redirection	*red_last(t_redirection *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
