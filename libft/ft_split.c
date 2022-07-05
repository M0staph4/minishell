/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 20:39:37 by mmoutawa          #+#    #+#             */
/*   Updated: 2021/11/27 20:40:34 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strw(char ch, char const *ss)
{
	size_t		x;
	size_t		i;

	i = 0;
	x = 0;
	while (ss[i] != '\0')
	{
		while (ss[i] == ch)
			i++;
		if (ss[i] != '\0')
			x++;
		while (ss[i] != ch && ss[i] != '\0')
			i++;
	}
	return (x);
}

char	**ft_split(char const *s, char c)
{
	size_t		j;
	size_t		y;
	size_t		x;
	char		**p;

	if (s == 0)
		return (NULL);
	j = 0;
	y = 0;
	p = malloc (sizeof (char *) * (ft_strw (c, s) + 1));
	if (p == NULL)
		return (NULL);
	while (j < ft_strw (c, s))
	{
		while (s[y] == c)
			y++;
		x = y;
		while (s[y] != c && s[y] != '\0')
			y++;
		p[j++] = ft_substr (s, x, y - x);
	}
		p[j] = NULL;
	return (p);
}
