/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:04:48 by mmoutawa          #+#    #+#             */
/*   Updated: 2021/11/25 18:04:51 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[i] == '\0' || haystack == needle)
		return ((char *)haystack);
	if (len == 0)
		return (0);
	while (haystack[j] != '\0' && len + 1 >= j)
	{
		if (haystack[j + i] == needle[i])
			i++;
		else
		{
			i = 0;
			j++;
			len--;
		}
		if (i == ft_strlen(needle))
			return (&((char *)haystack)[j]);
	}
	return (NULL);
}
