/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-mhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 02:41:28 by cel-mhan          #+#    #+#             */
/*   Updated: 2021/11/19 02:28:44 by cel-mhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	firstone(char	*str, char	*set)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (set[i])
	{
		while (str[j] == set[i])
		{
			j++;
			i = 0;
		}
		i++;
	}
	return (j);
}

static int	lastone(char	*str, char	*set)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(str) - 1;
	while (set[i])
	{
		while (str[len] == set[i])
		{
			len--;
			i = 0;
		}
		i++;
	}
	return (len);
}

char	*ft_strtrim(char const	*s1, char const	*set)
{
	int		last;
	int		first;
	int		len;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	first = firstone((char *)s1, (char *)set);
	if ((size_t)first >= ft_strlen((char *)s1))
		return (ft_strdup(""));
	last = lastone((char *)s1, (char *)set);
	len = last - first + 1;
	return (ft_substr(s1, first, len));
}
