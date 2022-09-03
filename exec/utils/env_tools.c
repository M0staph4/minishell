/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-mhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 23:23:00 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/09/02 23:23:02 by cel-mhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

char	*get_env(t_env_list **env, char *key)
{
	t_env_list	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, (ft_strlen(key) + 1)))
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

int	search_env(t_env_list **env, char *key)
{
	t_env_list	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, (ft_strlen(key) + 1)))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	env_size(t_env_list **env)
{
	int			size;
	t_env_list	*lst;

	lst = (*env);
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

t_env_list	*new_env(char *key, char *content, char *separator)
{
	t_env_list	*new;

	new = malloc(sizeof(t_env_list) * 1);
	if (!new)
		return (0);
	new->key = ft_strdup(key);
	new->content = ft_strdup(content);
	new->separator = separator;
	new->next = NULL;
	return (new);
}

void	env_add_back(t_env_list **lst, t_env_list *new)
{
	t_env_list	*n;

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
