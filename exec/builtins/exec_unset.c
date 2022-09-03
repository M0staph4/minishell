/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-mhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 23:15:15 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/09/02 23:15:17 by cel-mhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void	delete_node(t_env_list **env, char *key)
{
	t_env_list	*temp;
	t_env_list	*current;

	current = *env;
	while (current->next)
	{
		if (!ft_strncmp(current->next->key, key, ft_strlen(key) + 1))
		{
			temp = current->next;
			if (current->next->next)
				current->next = current->next->next;
			else
			{
				current->next = NULL;
				free(temp->key);
				free(temp->content);
				free(temp);
				break ;
			}
			free(temp->key);
			free(temp->content);
			free(temp);
		}
		current = current->next;
	}
}

void	exec_unset(t_env_list **env, char **key)
{
	t_env_list	*temp;
	int			i;

	i = 1;
	while (key[i])
	{
		if (!key[i][0])
			print_error(": not a valid identifier\n", key[i], 1);
		else if (check_key(key[i], 1))
		{
			if (!ft_strncmp((*env)->key, key[i], ft_strlen(key[i])))
			{
				temp = (*env);
				(*env) = (*env)->next;
				temp->next = NULL;
				free(temp->key);
				free(temp->content);
				free(temp);
			}
			else
				delete_node(env, key[i]);
		}
		i++;
	}
}
