/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-mhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 23:23:13 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/09/02 23:23:15 by cel-mhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int	ft_isalnumdash(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || (c == '_') || (c == '='))
		return (1);
	return (0);
}

size_t	ft_strnchr(const char *s, int c)
{
	size_t	i;
	char	*s1;
	size_t	len;

	s1 = (char *)s;
	len = ft_strlen(s1) + 1;
	i = 0;
	while (i < len)
	{
		if (*s1 == (char)c)
			return (i);
		s1++;
		i++;
	}
	return (0);
}

int	check_doube(t_env_list **env, char *key)
{
	char	**tmp;

	tmp = ft_split(key, '=');
	if (tmp[0])
	{
		if (search_env(env, tmp[0]))
		{
			free_array(tmp);
			return (1);
		}
		else if (ft_strnchr(tmp[0], '+') == ft_strlen(tmp[0]) - 1)
		{
			free(tmp[0]);
			tmp[0] = ft_substr(tmp[0], 0, ft_strlen(tmp[0]) - 1);
			if (search_env(env, tmp[0]))
			{
				free_array(tmp);
				return (2);
			}
		}
	}
	free_array(tmp);
	return (0);
}

int	check_key(char *key, int i)
{
	char	**keys;

	keys = ft_split(key, '=');
	if (ft_isalpha(keys[0][0]) || keys[0][0] == '_')
	{
		while (keys[0][i])
		{
			if (!ft_isalnumdash(keys[0][i]) || keys[0][0] == '\0')
			{
				print_error(": not a valid identifier\n", keys[0], 1);
				free_array(keys);
				return (0);
			}
			i++;
		}
	}
	else
	{
		print_error(": event not found\n", key, 0);
		free_array(keys);
		return (0);
	}
	free_array(keys);
	return (1);
}

t_env_list	*env_last(t_env_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
