/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-mhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 00:21:59 by cel-mhan          #+#    #+#             */
/*   Updated: 2021/11/18 00:22:01 by cel-mhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*new;

	node = lst;
	while (node)
	{
		new = ft_lstnew(f(node->content));
		if (!new)
		{
			ft_lstclear(new->content, del);
			return (0);
		}
		ft_lstadd_back(&new, new);
		node = node->next;
	}
	return (new);
}

