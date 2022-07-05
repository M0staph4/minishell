/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:05:51 by mmoutawa          #+#    #+#             */
/*   Updated: 2021/11/27 20:47:57 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_char(char c, char const *set)
{
	int		i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_str(char const *s1, char const *set)
{
	size_t	x;
	size_t	start;
	size_t	len;

	x = 0;
	len = ft_strlen(s1) - 1;
	while (ft_char(s1[x], set) != 0)
		x++;
	if (x == len + 1)
		return (ft_strdup (""));
	start = x;
	while (ft_char (s1[len], set) != 0)
		len--;
	return (ft_substr(s1, start, len - start + 1));
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*p;
	char	*j;

	if (!s1 || !set)
		return (NULL);
	j = (char *) set;
	p = ft_str(s1, set);
	return (p);
}
