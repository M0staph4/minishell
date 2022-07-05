/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:02:39 by mmoutawa          #+#    #+#             */
/*   Updated: 2021/11/25 18:02:44 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	j;
	size_t	i;
	char	*p;

	if (s2 == NULL)
		return ((char *)s1);
	if (s1 == NULL && s2 != NULL)
		return ((char *)s2);
	i = ft_strlen (s1);
	j = ft_strlen (s2);
	p = malloc(i + j + 1);
	if (p == NULL)
		return (NULL);
	j = 0;
	i = 0;
	while (s1[i] != '\0')
		p[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		p[j++] = s2[i++];
	p[j] = '\0';
	return (p);
}
